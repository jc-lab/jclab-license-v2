#pragma once

#include <stdint.h>

#include "../../../include/jclab_license/crypto/provider.h"

namespace jclab_license {
namespace crypto {
namespace mbedtls {

class MbedtlsProvider : public Provider {
 public:
  bool hashSha256(uint8_t* output, const std::string_view& data) const override;

  VerifyResult verify(
    const std::string_view& der,
    const std::string_view& ca_cert,
    const std::string_view& cert_key_usage,
    const std::string_view& content_type_oid
  ) const override;

  int aesGcmDecrypt(
      std::string_view key,
      std::string_view iv,
      std::string_view aad,
      std::string_view ciphertext_with_tag,
      std::vector<uint8_t>& plaintext_out) const override;
};

}  // namespace mbedtls
}  // namespace crypto
}  // namespace jclab_license