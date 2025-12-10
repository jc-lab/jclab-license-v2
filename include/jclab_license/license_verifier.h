#pragma once

#include <string_view>
#include <memory>

#include "license_info.h"
#include "timecense.h"

namespace jclab_license {

class LicenseVerifier {
 public:
  static LicenseVerifier *getInstance();

  struct VerifyResult {
    bool verified;
    std::shared_ptr<LicensePack> pack;
    uint8_t hash_sha256[32];
  };

  virtual const TimecenseUtil* getTimecenseUtil() const = 0;

  virtual VerifyResult verifyB64(const std::string_view& input) const = 0;
  virtual VerifyResult verifyDER(const std::string_view& der) const = 0;
  virtual VerifyResult verifyB64(const char* input, int len) const = 0;
  virtual VerifyResult verifyDER(const uint8_t* der, int len) const = 0;

 protected:
  LicenseVerifier() {}
};

}  // namespace jclab_license