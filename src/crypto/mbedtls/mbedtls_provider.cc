#include <vector>
#include <string>
#include <string.h>

#include "mbedtls_provider.h"

#include <mbedtls/md.h>
#include <mbedtls/x509_crt.h>
#include <psa/crypto.h>
#include <pkcs7_ex.h>

#define GCM_TAG_LENGTH 16

namespace jclab_license {
namespace crypto {
namespace mbedtls {

class mbedtls_pkcs7_view_wrapper {
public:
  mbedtls_pkcs7_view data;
  mbedtls_pkcs7_view_wrapper() {
    memset(&data, 0, sizeof(data));
  }
  ~mbedtls_pkcs7_view_wrapper() {
    mbedtls_pkcs7_view_free(&data);
  }
  mbedtls_pkcs7_view* operator &() {
    return &data;
  }
  mbedtls_pkcs7_view* operator ->() {
    return &data;
  }
};


bool MbedtlsProvider::hashSha256(uint8_t* output, const std::string_view& data) const {
  mbedtls_md_context_t md_ctx;
  mbedtls_md_init(&md_ctx);
  mbedtls_md_setup(&md_ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 0);
  mbedtls_md_starts(&md_ctx);
  mbedtls_md_update(&md_ctx, (const uint8_t*) data.data(), data.length());
  mbedtls_md_finish(&md_ctx, output);
  mbedtls_md_free(&md_ctx);
  return true;
}

Provider::VerifyResult MbedtlsProvider::verify(
  const std::string_view& der,
  const std::string_view& ca_cert_der,
  const std::string_view& cert_key_usage,
  const std::string_view& content_type_oid
) const {
  mbedtls_pkcs7_view_wrapper view;
  int ret = mbedtls_pkcs7_parse_verify_attached(
      reinterpret_cast<const unsigned char*>(der.data()), der.length(), &view);

  if (ret != 0) {
    return { false, {} };
  }

  mbedtls_x509_crt ca_cert;
  mbedtls_x509_crt_init(&ca_cert);
  ret = mbedtls_x509_crt_parse_der(&ca_cert, (const uint8_t*) ca_cert_der.data(), ca_cert_der.length());
  if (ret != 0) {
    mbedtls_x509_crt_free(&view->signer_cert);
    mbedtls_x509_crt_free(&ca_cert);
    return { false, {} };
  }

  uint32_t flags = 0;
  ret = mbedtls_x509_crt_verify(&view->signer_cert, &ca_cert, nullptr, nullptr, &flags, nullptr, nullptr);
  if (ret != 0 || flags != 0) {
    mbedtls_x509_crt_free(&view->signer_cert);
    mbedtls_x509_crt_free(&ca_cert);
    return { false, {} };
  }

  // Check key usage
  bool key_usage_found = false;
  if (view->signer_cert.ext_key_usage.buf.p != nullptr) {
      mbedtls_asn1_sequence *current = &view->signer_cert.ext_key_usage;
      while(current) {
          if (current->buf.len == cert_key_usage.size() &&
              memcmp(current->buf.p, cert_key_usage.data(), cert_key_usage.size()) == 0) {
              key_usage_found = true;
              break;
          }
          current = current->next;
      }
  }

  mbedtls_x509_crt_free(&view->signer_cert);
  mbedtls_x509_crt_free(&ca_cert);

  if (!key_usage_found) {
      return { false, {} };
  }

  if (view->signing_time_valid != 1) {
    return { false, {} };
  }

  if (
    view->econtent_type.len != content_type_oid.length() ||
    memcmp(view->econtent_type.p, content_type_oid.data(), content_type_oid.length())
  ) {
    return { false, {} };
  }

  std::vector<uint8_t> data(view->content, view->content + view->content_len);
  return { true, std::move(data) };
}

int MbedtlsProvider::aesGcmDecrypt(
    std::string_view key,
    std::string_view iv,
    std::string_view aad,
    std::string_view ciphertext_with_tag,
    std::vector<uint8_t>& plaintext_out
) const {
    psa_status_t status = PSA_SUCCESS;

    // PSA Crypto 초기화 (전역적으로 한 번만 해도 됨)
    status = psa_crypto_init();
    if (status != PSA_SUCCESS) {
        fprintf(stderr, "psa_crypto_init failed: %d\n", status);
        return status;
    }

    const uint8_t* ciphertext = reinterpret_cast<const uint8_t*>(ciphertext_with_tag.data());

    // 키 설정
    psa_key_attributes_t key_attr = PSA_KEY_ATTRIBUTES_INIT;
    psa_set_key_usage_flags(&key_attr, PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&key_attr, PSA_ALG_GCM);
    psa_set_key_type(&key_attr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&key_attr, key.size() * 8);

    psa_key_id_t key_id;
    status = psa_import_key(&key_attr,
                            reinterpret_cast<const uint8_t*>(key.data()),
                            key.size(),
                            &key_id);
    if (status != PSA_SUCCESS) {
        fprintf(stderr, "psa_import_key failed: %d\n", status);
        return status;
    }

    // 출력 버퍼 준비
    plaintext_out.resize(plaintext_out.size());

    // 복호화 수행
    size_t plaintext_len = 0;
    status = psa_aead_decrypt(
        key_id,
        PSA_ALG_GCM,
        reinterpret_cast<const uint8_t*>(iv.data()), iv.size(),
        reinterpret_cast<const uint8_t*>(aad.data()), aad.size(),
        reinterpret_cast<const uint8_t*>(ciphertext_with_tag.data()), ciphertext_with_tag.size(),
        plaintext_out.data(), plaintext_out.size(),
        &plaintext_len
    );

    // 키 삭제
    psa_destroy_key(key_id);

    if (status != PSA_SUCCESS) {
        fprintf(stderr, "psa_aead_decrypt failed: %d\n", status);
        plaintext_out.clear();
        return status;
    }

    plaintext_out.resize(plaintext_len);
    return PSA_SUCCESS;
}

}  // namespace mbedtls
}  // namespace crypto
}  // namespace jclab_license