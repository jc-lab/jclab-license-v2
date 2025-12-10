#pragma once

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

namespace jclab_license {

class TimecenseKey {
public:
 std::string module;
 uint8_t id[8];   // key_id (8 bytes, 64 bits)
 int32_t version_limit;
 std::vector<uint8_t> key;

 TimecenseKey()
     : version_limit(0) {}
};

enum class LicenseType : int32_t {
 kUnknownLicenseType = 0,
 kTermMaintenance    = 1,
 kSubscribe          = 2
};

class LicensePack {
public:
 int64_t issued_at; // unix epoch time in milliseconds

 std::string licensee_name;
 std::string licensee_email;

 std::vector<std::string> licensed_product;
 LicenseType license_type;
 int64_t license_expire_at;

 int32_t timecense_max_version;
 std::vector<TimecenseKey> timecense_key;

 std::map<std::string, std::vector<uint8_t>> attribute;

 LicensePack()
     : issued_at(0),
       license_type(LicenseType::kUnknownLicenseType),
       license_expire_at(0),
       timecense_max_version(0) {}
};

}  // namespace jclab_license