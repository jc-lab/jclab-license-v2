#pragma once

#include "crypto/provider.h"
#include "license_info.h"

namespace jclab_license {

struct FileKey {
  uint8_t iv[12];
  uint8_t key[32];
};


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
  FileKey getFileKey(const std::vector<std::vector<uint8_t>>& keys, const uint8_t* salt, int salt_len) const;

  bool aesGcmDecrypt(
      const FileKey* file_key,
      std::string_view aad,
      std::string_view ciphertext_with_tag,
      std::vector<uint8_t>& plaintext_out) const;
};

}