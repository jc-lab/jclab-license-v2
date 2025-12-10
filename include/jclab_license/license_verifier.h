#pragma once

#include <string_view>
#include <memory>

#include "license_info.h"

namespace jclab_license {

class LicenseVerifier {
 public:
  static LicenseVerifier *getInstance();

  struct VerifyResult {
    bool verified;
    std::shared_ptr<LicensePack> pack;
    uint8_t hash_sha256[32];
  };

  virtual VerifyResult verifyB64(const std::string_view& input) = 0;
  virtual VerifyResult verifyDER(const std::string_view& der) = 0;
  virtual VerifyResult verifyB64(const char* input, int len) = 0;
  virtual VerifyResult verifyDER(const uint8_t* der, int len) = 0;

 protected:
  LicenseVerifier() {}
};

}  // namespace jclab_license