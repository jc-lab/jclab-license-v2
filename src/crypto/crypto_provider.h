#pragma once

#include <string_view>
#include <vector>

namespace jclab_license {
namespace crypto {

class Provider {
 public:
  struct VerifyResult {
    bool success;
    std::vector<uint8_t> data;
  };

  virtual ~Provider() = default;

  virtual VerifyResult verify(
    const std::string_view& der,
    const std::string_view& ca_cert,
    const std::string_view& cert_key_usage,
    const std::string_view& content_type_oid
  ) const = 0;

  virtual bool hashSha256(uint8_t* output, const std::string_view& data) const = 0;
};

}  // namespace crypto
}  // namespace jclab_license