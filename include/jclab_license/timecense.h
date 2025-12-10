#pragma once

#include "crypto/provider.h"
#include "license_info.h"

namespace jclab_license {

class TimecenseUtil {
 private:
  crypto::Provider* crypto_provider_;

public:
  TimecenseUtil(crypto::Provider* crypto_provider)
    : crypto_provider_(crypto_provider)
  {}

  static void deriveWithLoop(const uint8_t *input, size_t input_len, int iteration, uint8_t *output);

  std::vector<uint8_t> getVersionKeyFromLicensedKey(const TimecenseKey* licensed_key, int target_version) const;

  /**
   *
   * @param keys
   * @param salt must 16 bytes
   * @return output BLAKE2B_OUTBYTES (64)
   */
  std::vector<uint8_t> getFileKey(const std::vector<std::vector<uint8_t>>& keys, const uint8_t* salt, int salt_len) const;
};

}