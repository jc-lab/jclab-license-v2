#pragma once

#include <stdint.h>

#include "../crypto_provider.h"

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
};

}  // namespace mbedtls
}  // namespace crypto
}  // namespace jclab_license