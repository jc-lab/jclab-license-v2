#pragma once

#include <string_view>

#include "jclab_license/generated/jclab-license.h"

namespace jclab_license {

using LicensePack = ::kr::jclab::license::proto::LicensePack<
 256, // name
 256, // email
 16, // product rep
 256, // product
 256, // timecense_key_REP
 256, // module
 256, // id
 256, // key
 256, // attribute_REP
 256, // key
 8192 // value
>;

class LicenseVerifier {
 public:
  static LicenseVerifier *getInstance();

  struct VerifyResult {
    bool verified;
    LicensePack pack;
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