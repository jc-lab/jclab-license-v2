#include <vector>
#include <string>
#include <string.h>

#include "mbedtls_provider.h"

#include <mbedtls/md.h>
#include <mbedtls/x509_crt.h>
#include <pkcs7_ex.h>

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

}  // namespace mbedtls
}  // namespace crypto
}  // namespace jclab_license