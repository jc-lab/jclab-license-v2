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

  virtual int aesGcmDecrypt(
      std::string_view key,
      std::string_view iv,
      std::string_view aad,
      std::string_view ciphertext_with_tag,
      std::vector<uint8_t>& plaintext_out) const = 0;
};

}  // namespace crypto
}  // namespace jclab_license