#include <vector>

#include "read_buffer_read_only.h"

#include "jclab_license/license_verifier.h"

#include "crypto/crypto_provider.h"
#include "crypto/mbedtls/mbedtls_provider.h"
#include "jclab_license/generated/jclab_license_authority.h"

#include <mbedtls/base64.h>
#include <psa/crypto.h>

namespace jclab_license {

namespace {
// 1.3.6.1.4.1.62615.10.3.1501
const unsigned char KEY_USAGE_LICENSE_OID[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x83, 0xE9, 0x17, 0x0A, 0x03, 0x8B, 0x5D };
//  1.3.6.1.4.1.62615.20.1501.1
const unsigned char CONTENT_TYPE_LICENSE_OID[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x83, 0xE9, 0x17, 0x14, 0x8b, 0x5d, 0x01 };
}

class LicenseVerifierImpl : public LicenseVerifier {
private:
    crypto::mbedtls::MbedtlsProvider provider_;

public:
    LicenseVerifierImpl() : LicenseVerifier() {}

    VerifyResult verifyB64(const std::string_view& input) override;
    VerifyResult verifyDER(const std::string_view& der) override;
    VerifyResult verifyB64(const char* input, int len) override;
    VerifyResult verifyDER(const uint8_t* der, int len) override;
};

static LicenseVerifierImpl instance;

LicenseVerifier *LicenseVerifier::getInstance() {
    psa_crypto_init();
    return &instance;
}

LicenseVerifier::VerifyResult LicenseVerifierImpl::verifyB64(const std::string_view& input) {
    return verifyB64(input.data(), input.length());
}

LicenseVerifier::VerifyResult LicenseVerifierImpl::verifyDER(const std::string_view& der) {
    return verifyDER(reinterpret_cast<const uint8_t*>(der.data()), der.length());
}

LicenseVerifier::VerifyResult LicenseVerifierImpl::verifyB64(const char* input, int len) {
    size_t out_len;
    mbedtls_base64_decode(nullptr, 0, &out_len, reinterpret_cast<const unsigned char*>(input), len);
    std::vector<uint8_t> der(out_len);
    int ret = mbedtls_base64_decode(der.data(), der.size(), &out_len, reinterpret_cast<const unsigned char*>(input), len);
    if (ret != 0) {
        return { false, {} };
    }
    return verifyDER(der.data(), out_len);
}

LicenseVerifier::VerifyResult LicenseVerifierImpl::verifyDER(const uint8_t* der, int len) {
    VerifyResult result = {false};

    provider_.hashSha256(result.hash_sha256, {reinterpret_cast<const char*>(der), (size_t)len});

    auto verify_result = provider_.verify(
        {reinterpret_cast<const char*>(der), (size_t)len},
        {reinterpret_cast<const char*>(JCLAB_LICENSE_AUTHORITY_DER), sizeof(JCLAB_LICENSE_AUTHORITY_DER)},
        {reinterpret_cast<const char*>(KEY_USAGE_LICENSE_OID), sizeof(KEY_USAGE_LICENSE_OID)},
        {reinterpret_cast<const char*>(CONTENT_TYPE_LICENSE_OID), sizeof(CONTENT_TYPE_LICENSE_OID)}
    );
    if (!verify_result.success) {
        return result;
    }

    result.verified = true;

    ReadBufferReadOnly read_buffer(verify_result.data.data(), verify_result.data.size());
    result.pack.deserialize(read_buffer);

    return result;
}

}  // namespace jclab_license