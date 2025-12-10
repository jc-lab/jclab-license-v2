#include <string>
#include <vector>

#include <string.h>

#include "read_buffer_read_only.h"

#include "jclab_license/license_verifier.h"

#include "crypto/crypto_provider.h"
#include "crypto/mbedtls/mbedtls_provider.h"
#include "jclab_license/generated/jclab_license_authority.h"

#include <mbedtls/base64.h>
#include <psa/crypto.h>

#include "jclab_license/generated/jclab_license.h"

namespace jclab_license {

using LicensePackProto = ::kr::jclab::license::proto::LicensePack<
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

    LicensePackProto pack_proto;
    pack_proto.deserialize(read_buffer);

    result.pack = std::make_shared<LicensePack>();
    result.pack->issued_at = pack_proto.get_issued_at();
    result.pack->licensee_name.assign(pack_proto.get_licensee_name().get_const(), pack_proto.get_licensee_name().get_length());
    result.pack->licensee_email.assign(pack_proto.get_licensee_email().get_const(), pack_proto.get_licensee_email().get_length());
    for (int i=0; i<pack_proto.get_licensed_product().get_length(); i++) {
        auto const& item = pack_proto.get_licensed_product().get_const(i);
        result.pack->licensed_product.push_back(std::string(item.get_const(), item.get_length()));
    }
    result.pack->license_type = (LicenseType) pack_proto.get_license_type();
    result.pack->license_expire_at = pack_proto.get_license_expire_at();
    result.pack->timecense_max_version = pack_proto.get_timecense_max_version();
    for (int i=0; i<pack_proto.get_timecense_key().get_length(); i++) {
        auto const& item = pack_proto.get_timecense_key().get_const(i);
        TimecenseKey key;
        key.module.assign(item.get_module().get_const(), item.get_module().get_length());
        memcpy(key.id, item.get_id().get_const(), sizeof(key.id));
        key.version_limit = item.get_version_limit();
        const uint8_t *key_begin = item.get_key().get_const();
        const uint8_t *key_end = key_begin + item.get_key().get_length();
        key.key.assign(key_begin, key_end);
        result.pack->timecense_key.push_back(std::move(key));
    }
    for (int i=0; i<pack_proto.get_attribute().get_length(); i++) {
        auto const& item = pack_proto.get_attribute().get_const(i);
        std::string key(item.get_key().get_const(), item.get_key().get_length());
        const uint8_t *value_begin = item.get_value().get_const();
        const uint8_t *value_end = value_begin + item.get_value().get_length();
        std::vector<uint8_t> value(value_begin, value_end);
        result.pack->attribute[std::move(key)] = std::move(value);
    }

    return result;
}

}  // namespace jclab_license