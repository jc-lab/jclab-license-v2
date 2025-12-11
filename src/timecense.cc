#include <string.h>

#include <blake2.h>

#include <jclab_license/timecense.h>
#define MBEDTLS_DECLARE_PRIVATE_IDENTIFIERS
#include <mbedtls/private/gcm.h>

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

FileKey TimecenseUtil::getFileKey(const std::vector<std::vector<uint8_t>>& keys, const uint8_t* salt, int salt_len) const {
  uint8_t output[12+32];

  blake2b_state S;
  blake2b_param P;
  memset(&P, 0, sizeof(P));

  P.digest_length = sizeof(output);
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

  blake2b_final(&S, output, BLAKE2B_OUTBYTES);

  FileKey file_key = {};
  memcpy(file_key.iv, &output[0], sizeof(file_key.iv));
  memcpy(file_key.key, &output[12], sizeof(file_key.key));

  return file_key;
}


bool TimecenseUtil::aesGcmDecrypt(
    const FileKey* file_key,
    std::string_view aad,
    std::string_view ciphertext_with_tag,
    std::vector<uint8_t>& plaintext_out
) const {
  constexpr size_t TAG_LEN = 16;  // GCM TAG = 128bit

  if (ciphertext_with_tag.size() < TAG_LEN) {
    return false; // invalid input
  }

  const size_t ciphertext_len = ciphertext_with_tag.size() - TAG_LEN;
  const uint8_t* ciphertext = reinterpret_cast<const uint8_t*>(ciphertext_with_tag.data());
  const uint8_t* tag        = reinterpret_cast<const uint8_t*>(ciphertext_with_tag.data() + ciphertext_len);

  plaintext_out.resize(ciphertext_len);

  mbedtls_gcm_context gcm;
  mbedtls_gcm_init(&gcm);

  int ret = 0;

  // key length: 128/192/256 bits supported → here use key.size()*8 bits
  ret = mbedtls_gcm_setkey(
      &gcm, MBEDTLS_CIPHER_ID_AES,
      file_key->key,
      sizeof(file_key->key) * 8);
  if (ret != 0) {
    mbedtls_gcm_free(&gcm);
    return false;
  }

  ret = mbedtls_gcm_auth_decrypt(
      &gcm,
      ciphertext_len,
      file_key->iv, sizeof(file_key->iv),
      reinterpret_cast<const uint8_t*>(aad.data()), aad.size(),
      tag, TAG_LEN,
      ciphertext,
      plaintext_out.data()
  );

  mbedtls_gcm_free(&gcm);

  if (ret != 0) {
    // 인증 실패 또는 복호화 실패
    return false;
  }

  // 정상 복호화 → 성공 시 빈 vector 반환
  return true;
}

}
