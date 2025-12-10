#include <string.h>

#include <blake2.h>

#include <jclab_license/timecense.h>

namespace jclab_license {

#define KEY_SIZE 32

void TimecenseUtil::deriveWithLoop(const uint8_t *input, size_t input_len, int iteration, uint8_t *output) {
  uint8_t temp[KEY_SIZE];

  // iteration == 0일 경우 input을 그대로 output에 복사
  if (iteration == 0) {
    memset(output, 0, KEY_SIZE);
    memcpy(output, input, input_len < KEY_SIZE ? input_len : KEY_SIZE);
    return;
  }

  memset(output, 0, KEY_SIZE);

  for (int i = 0; i < iteration; i++) {
    if (i == 0) {
      // 첫 번째 반복: input을 해시
      blake2b(output, KEY_SIZE, input, input_len, nullptr, 0);
    } else {
      // 이후 반복: 이전 output을 다시 해시
      memcpy(temp, output, KEY_SIZE);
      blake2b(output, KEY_SIZE, temp, KEY_SIZE, nullptr, 0);
    }
  }
}

std::vector<uint8_t> TimecenseUtil::getVersionKeyFromLicensedKey(
  const TimecenseKey* licensed_key,
  int target_version
) const {
  int iteration = licensed_key->version_limit - target_version;
  if (iteration < 0) {
    return {};
  }
  std::vector<uint8_t> output;
  output.resize(KEY_SIZE);
  deriveWithLoop(licensed_key->key.data(), licensed_key->key.size(), iteration, &output[0]);
  return output;
}

std::vector<uint8_t> TimecenseUtil::getFileKey(const std::vector<std::vector<uint8_t>>& keys, const uint8_t* salt, int salt_len) const {
  std::vector<uint8_t> output(BLAKE2B_OUTBYTES);

  blake2b_state S;
  blake2b_param P;
  memset(&P, 0, sizeof(P));

  P.digest_length = BLAKE2B_OUTBYTES;
  P.fanout        = 1;
  P.depth         = 1;
  if (salt && salt_len > 0) {
    if (salt_len > BLAKE2B_SALTBYTES) {
      salt_len = BLAKE2B_SALTBYTES;
    }
    memcpy(P.salt, salt, salt_len);
  }
  blake2b_init_param(&S, &P);

  for (auto iter = keys.begin(); iter != keys.end(); iter++) {
    const std::vector<uint8_t>& key = *iter;
    blake2b_update(&S, key.data(), key.size());
  }

  blake2b_final(&S, output.data(), BLAKE2B_OUTBYTES);

  return output;
}

}
