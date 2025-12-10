/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: jclab_license.proto
 */

// This file is generated. Please do not edit!
#ifndef JCLAB_LICENSE_H
#define JCLAB_LICENSE_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <Defines.h>
#include <limits>

// Include external proto definitions

namespace kr {
namespace jclab {
namespace license {
namespace proto {

enum class LicenseType : uint32_t
{
  kUnknownLicenseType = 0,
  kTermMaintenance = 1,
  kSubscribe = 2
};

template<
    uint32_t TimecenseKey_module_LENGTH, 
    uint32_t TimecenseKey_id_LENGTH, 
    uint32_t TimecenseKey_key_LENGTH
>
class TimecenseKey final: public ::EmbeddedProto::MessageInterface
{
  public:
    TimecenseKey() = default;
    TimecenseKey(const TimecenseKey& rhs )
    {
      set_module(rhs.get_module());
      set_id(rhs.get_id());
      set_version_limit(rhs.get_version_limit());
      set_key(rhs.get_key());
    }

    TimecenseKey(const TimecenseKey&& rhs ) noexcept
    {
      set_module(rhs.get_module());
      set_id(rhs.get_id());
      set_version_limit(rhs.get_version_limit());
      set_key(rhs.get_key());
    }

    ~TimecenseKey() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MODULE = 1,
      ID = 2,
      VERSION_LIMIT = 3,
      KEY = 4
    };

    TimecenseKey& operator=(const TimecenseKey& rhs)
    {
      set_module(rhs.get_module());
      set_id(rhs.get_id());
      set_version_limit(rhs.get_version_limit());
      set_key(rhs.get_key());
      return *this;
    }

    TimecenseKey& operator=(const TimecenseKey&& rhs) noexcept
    {
      set_module(rhs.get_module());
      set_id(rhs.get_id());
      set_version_limit(rhs.get_version_limit());
      set_key(rhs.get_key());
      return *this;
    }

    static constexpr char const* MODULE_NAME = "module";
    inline void clear_module() { module_.clear(); }
    inline ::EmbeddedProto::FieldString<TimecenseKey_module_LENGTH>& mutable_module() { return module_; }
    inline void set_module(const ::EmbeddedProto::FieldString<TimecenseKey_module_LENGTH>& rhs) { module_.set(rhs); }
    inline const ::EmbeddedProto::FieldString<TimecenseKey_module_LENGTH>& get_module() const { return module_; }
    inline const char* module() const { return module_.get_const(); }

    static constexpr char const* ID_NAME = "id";
    inline void clear_id() { id_.clear(); }
    inline ::EmbeddedProto::FieldString<TimecenseKey_id_LENGTH>& mutable_id() { return id_; }
    inline void set_id(const ::EmbeddedProto::FieldString<TimecenseKey_id_LENGTH>& rhs) { id_.set(rhs); }
    inline const ::EmbeddedProto::FieldString<TimecenseKey_id_LENGTH>& get_id() const { return id_; }
    inline const char* id() const { return id_.get_const(); }

    static constexpr char const* VERSION_LIMIT_NAME = "version_limit";
    inline void clear_version_limit() { version_limit_.clear(); }
    inline void set_version_limit(const int32_t& value) { version_limit_ = value; }
    inline void set_version_limit(const int32_t&& value) { version_limit_ = value; }
    inline int32_t& mutable_version_limit() { return version_limit_.get(); }
    inline const int32_t& get_version_limit() const { return version_limit_.get(); }
    inline int32_t version_limit() const { return version_limit_.get(); }

    static constexpr char const* KEY_NAME = "key";
    inline void clear_key() { key_.clear(); }
    inline ::EmbeddedProto::FieldBytes<TimecenseKey_key_LENGTH>& mutable_key() { return key_; }
    inline void set_key(const ::EmbeddedProto::FieldBytes<TimecenseKey_key_LENGTH>& rhs) { key_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<TimecenseKey_key_LENGTH>& get_key() const { return key_; }
    inline const uint8_t* key() const { return key_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = module_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MODULE), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ID), buffer, false);
      }

      if((0 != version_limit_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = version_limit_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VERSION_LIMIT), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = key_.serialize_with_id(static_cast<uint32_t>(FieldNumber::KEY), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::MODULE:
            return_value = module_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ID:
            return_value = id_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::VERSION_LIMIT:
            return_value = version_limit_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::KEY:
            return_value = key_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_module();
      clear_id();
      clear_version_limit();
      clear_key();

    }

#ifndef DISABLE_FIELD_NUMBER_TO_NAME 

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::MODULE:
          name = MODULE_NAME;
          break;
        case FieldNumber::ID:
          name = ID_NAME;
          break;
        case FieldNumber::VERSION_LIMIT:
          name = VERSION_LIMIT_NAME;
          break;
        case FieldNumber::KEY:
          name = KEY_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#endif

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = module_.to_string(left_chars, indent_level + 2, MODULE_NAME, true);
      left_chars = id_.to_string(left_chars, indent_level + 2, ID_NAME, false);
      left_chars = version_limit_.to_string(left_chars, indent_level + 2, VERSION_LIMIT_NAME, false);
      left_chars = key_.to_string(left_chars, indent_level + 2, KEY_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      ::EmbeddedProto::FieldString<TimecenseKey_module_LENGTH> module_;
      ::EmbeddedProto::FieldString<TimecenseKey_id_LENGTH> id_;
      EmbeddedProto::int32 version_limit_ = 0;
      ::EmbeddedProto::FieldBytes<TimecenseKey_key_LENGTH> key_;

};

template<
    uint32_t LicensePack_licensee_name_LENGTH, 
    uint32_t LicensePack_licensee_email_LENGTH, 
    uint32_t LicensePack_licensed_product_REP_LENGTH, 
    uint32_t LicensePack_licensed_product_LENGTH, 
    uint32_t LicensePack_timecense_key_REP_LENGTH, 
    uint32_t LicensePack_timecense_key_TimecenseKey_module_LENGTH, 
    uint32_t LicensePack_timecense_key_TimecenseKey_id_LENGTH, 
    uint32_t LicensePack_timecense_key_TimecenseKey_key_LENGTH, 
    uint32_t LicensePack_attribute_REP_LENGTH, 
    uint32_t LicensePack_attribute_AttributeEntry_key_LENGTH, 
    uint32_t LicensePack_attribute_AttributeEntry_value_LENGTH
>
class LicensePack final: public ::EmbeddedProto::MessageInterface
{
  public:
    LicensePack() = default;
    LicensePack(const LicensePack& rhs )
    {
      set_issued_at(rhs.get_issued_at());
      set_licensee_name(rhs.get_licensee_name());
      set_licensee_email(rhs.get_licensee_email());
      set_licensed_product(rhs.get_licensed_product());
      set_license_type(rhs.get_license_type());
      set_license_expire_at(rhs.get_license_expire_at());
      set_timecense_max_version(rhs.get_timecense_max_version());
      set_timecense_key(rhs.get_timecense_key());
      set_attribute(rhs.get_attribute());
    }

    LicensePack(const LicensePack&& rhs ) noexcept
    {
      set_issued_at(rhs.get_issued_at());
      set_licensee_name(rhs.get_licensee_name());
      set_licensee_email(rhs.get_licensee_email());
      set_licensed_product(rhs.get_licensed_product());
      set_license_type(rhs.get_license_type());
      set_license_expire_at(rhs.get_license_expire_at());
      set_timecense_max_version(rhs.get_timecense_max_version());
      set_timecense_key(rhs.get_timecense_key());
      set_attribute(rhs.get_attribute());
    }

    ~LicensePack() override = default;

    template<
        uint32_t AttributeEntry_key_LENGTH, 
        uint32_t AttributeEntry_value_LENGTH
    >
    class AttributeEntry final: public ::EmbeddedProto::MessageInterface
    {
      public:
        AttributeEntry() = default;
        AttributeEntry(const AttributeEntry& rhs )
        {
          set_key(rhs.get_key());
          set_value(rhs.get_value());
        }

        AttributeEntry(const AttributeEntry&& rhs ) noexcept
        {
          set_key(rhs.get_key());
          set_value(rhs.get_value());
        }

        ~AttributeEntry() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          KEY = 1,
          VALUE = 2
        };

        AttributeEntry& operator=(const AttributeEntry& rhs)
        {
          set_key(rhs.get_key());
          set_value(rhs.get_value());
          return *this;
        }

        AttributeEntry& operator=(const AttributeEntry&& rhs) noexcept
        {
          set_key(rhs.get_key());
          set_value(rhs.get_value());
          return *this;
        }

        static constexpr char const* KEY_NAME = "key";
        inline void clear_key() { key_.clear(); }
        inline ::EmbeddedProto::FieldString<AttributeEntry_key_LENGTH>& mutable_key() { return key_; }
        inline void set_key(const ::EmbeddedProto::FieldString<AttributeEntry_key_LENGTH>& rhs) { key_.set(rhs); }
        inline const ::EmbeddedProto::FieldString<AttributeEntry_key_LENGTH>& get_key() const { return key_; }
        inline const char* key() const { return key_.get_const(); }

        static constexpr char const* VALUE_NAME = "value";
        inline void clear_value() { value_.clear(); }
        inline ::EmbeddedProto::FieldBytes<AttributeEntry_value_LENGTH>& mutable_value() { return value_; }
        inline void set_value(const ::EmbeddedProto::FieldBytes<AttributeEntry_value_LENGTH>& rhs) { value_.set(rhs); }
        inline const ::EmbeddedProto::FieldBytes<AttributeEntry_value_LENGTH>& get_value() const { return value_; }
        inline const uint8_t* value() const { return value_.get_const(); }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = key_.serialize_with_id(static_cast<uint32_t>(FieldNumber::KEY), buffer, false);
          }

          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = value_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VALUE), buffer, false);
          }

          return return_value;
        };

        ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
          ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
          uint32_t id_number = 0;
          FieldNumber id_tag = FieldNumber::NOT_SET;

          ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
          while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
          {
            id_tag = static_cast<FieldNumber>(id_number);
            switch(id_tag)
            {
              case FieldNumber::KEY:
                return_value = key_.deserialize_check_type(buffer, wire_type);
                break;

              case FieldNumber::VALUE:
                return_value = value_.deserialize_check_type(buffer, wire_type);
                break;

              case FieldNumber::NOT_SET:
                return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
                break;

              default:
                return_value = skip_unknown_field(buffer, wire_type);
                break;
            }

            if(::EmbeddedProto::Error::NO_ERRORS == return_value)
            {
              // Read the next tag.
              tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
            }
          }

          // When an error was detect while reading the tag but no other errors where found, set it in the return value.
          if((::EmbeddedProto::Error::NO_ERRORS == return_value)
             && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
             && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
          {
            return_value = tag_value;
          }

          return return_value;
        };

        void clear() override
        {
          clear_key();
          clear_value();

        }

    #ifndef DISABLE_FIELD_NUMBER_TO_NAME 

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::KEY:
              name = KEY_NAME;
              break;
            case FieldNumber::VALUE:
              name = VALUE_NAME;
              break;
            default:
              name = "Invalid FieldNumber";
              break;
          }
          return name;
        }

    #endif

    #ifdef MSG_TO_STRING

        ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
        {
          return this->to_string(str, 0, nullptr, true);
        }

        ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
        {
          ::EmbeddedProto::string_view left_chars = str;
          int32_t n_chars_used = 0;

          if(!first_field)
          {
            // Add a comma behind the previous field.
            n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
            if(0 < n_chars_used)
            {
              // Update the character pointer and characters left in the array.
              left_chars.data += n_chars_used;
              left_chars.size -= n_chars_used;
            }
          }

          if(nullptr != name)
          {
            if( 0 == indent_level)
            {
              n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
            }
            else
            {
              n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
            }
          }
          else
          {
            if( 0 == indent_level)
            {
              n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
            }
            else
            {
              n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
            }
          }
          
          if(0 < n_chars_used)
          {
            left_chars.data += n_chars_used;
            left_chars.size -= n_chars_used;
          }

          left_chars = key_.to_string(left_chars, indent_level + 2, KEY_NAME, true);
          left_chars = value_.to_string(left_chars, indent_level + 2, VALUE_NAME, false);
      
          if( 0 == indent_level) 
          {
            n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
          }
          else 
          {
            n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
          }

          if(0 < n_chars_used)
          {
            left_chars.data += n_chars_used;
            left_chars.size -= n_chars_used;
          }

          return left_chars;
        }

    #endif // End of MSG_TO_STRING

      private:


          ::EmbeddedProto::FieldString<AttributeEntry_key_LENGTH> key_;
          ::EmbeddedProto::FieldBytes<AttributeEntry_value_LENGTH> value_;

    };

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      ISSUED_AT = 1,
      LICENSEE_NAME = 10,
      LICENSEE_EMAIL = 11,
      LICENSED_PRODUCT = 20,
      LICENSE_TYPE = 21,
      LICENSE_EXPIRE_AT = 22,
      TIMECENSE_MAX_VERSION = 30,
      TIMECENSE_KEY = 31,
      ATTRIBUTE = 100
    };

    LicensePack& operator=(const LicensePack& rhs)
    {
      set_issued_at(rhs.get_issued_at());
      set_licensee_name(rhs.get_licensee_name());
      set_licensee_email(rhs.get_licensee_email());
      set_licensed_product(rhs.get_licensed_product());
      set_license_type(rhs.get_license_type());
      set_license_expire_at(rhs.get_license_expire_at());
      set_timecense_max_version(rhs.get_timecense_max_version());
      set_timecense_key(rhs.get_timecense_key());
      set_attribute(rhs.get_attribute());
      return *this;
    }

    LicensePack& operator=(const LicensePack&& rhs) noexcept
    {
      set_issued_at(rhs.get_issued_at());
      set_licensee_name(rhs.get_licensee_name());
      set_licensee_email(rhs.get_licensee_email());
      set_licensed_product(rhs.get_licensed_product());
      set_license_type(rhs.get_license_type());
      set_license_expire_at(rhs.get_license_expire_at());
      set_timecense_max_version(rhs.get_timecense_max_version());
      set_timecense_key(rhs.get_timecense_key());
      set_attribute(rhs.get_attribute());
      return *this;
    }

    static constexpr char const* ISSUED_AT_NAME = "issued_at";
    inline void clear_issued_at() { issued_at_.clear(); }
    inline void set_issued_at(const int64_t& value) { issued_at_ = value; }
    inline void set_issued_at(const int64_t&& value) { issued_at_ = value; }
    inline int64_t& mutable_issued_at() { return issued_at_.get(); }
    inline const int64_t& get_issued_at() const { return issued_at_.get(); }
    inline int64_t issued_at() const { return issued_at_.get(); }

    static constexpr char const* LICENSEE_NAME_NAME = "licensee_name";
    inline void clear_licensee_name() { licensee_name_.clear(); }
    inline ::EmbeddedProto::FieldString<LicensePack_licensee_name_LENGTH>& mutable_licensee_name() { return licensee_name_; }
    inline void set_licensee_name(const ::EmbeddedProto::FieldString<LicensePack_licensee_name_LENGTH>& rhs) { licensee_name_.set(rhs); }
    inline const ::EmbeddedProto::FieldString<LicensePack_licensee_name_LENGTH>& get_licensee_name() const { return licensee_name_; }
    inline const char* licensee_name() const { return licensee_name_.get_const(); }

    static constexpr char const* LICENSEE_EMAIL_NAME = "licensee_email";
    inline void clear_licensee_email() { licensee_email_.clear(); }
    inline ::EmbeddedProto::FieldString<LicensePack_licensee_email_LENGTH>& mutable_licensee_email() { return licensee_email_; }
    inline void set_licensee_email(const ::EmbeddedProto::FieldString<LicensePack_licensee_email_LENGTH>& rhs) { licensee_email_.set(rhs); }
    inline const ::EmbeddedProto::FieldString<LicensePack_licensee_email_LENGTH>& get_licensee_email() const { return licensee_email_; }
    inline const char* licensee_email() const { return licensee_email_.get_const(); }

    static constexpr char const* LICENSED_PRODUCT_NAME = "licensed_product";
    inline const ::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>& licensed_product(uint32_t index) const { return licensed_product_[index]; }
    inline void clear_licensed_product() { licensed_product_.clear(); }
    inline void set_licensed_product(uint32_t index, const ::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>& value) { licensed_product_.set(index, value); }
    inline void set_licensed_product(uint32_t index, const ::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>&& value) { licensed_product_.set(index, value); }
    inline void set_licensed_product(const ::EmbeddedProto::RepeatedFieldFixedSize<::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>, LicensePack_licensed_product_REP_LENGTH>& values) { licensed_product_ = values; }
    inline void add_licensed_product(const ::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>& value) { licensed_product_.add(value); }
    inline ::EmbeddedProto::RepeatedFieldFixedSize<::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>, LicensePack_licensed_product_REP_LENGTH>& mutable_licensed_product() { return licensed_product_; }
    inline ::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>& mutable_licensed_product(uint32_t index) { return licensed_product_[index]; }
    inline const ::EmbeddedProto::RepeatedFieldFixedSize<::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>, LicensePack_licensed_product_REP_LENGTH>& get_licensed_product() const { return licensed_product_; }
    inline const ::EmbeddedProto::RepeatedFieldFixedSize<::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>, LicensePack_licensed_product_REP_LENGTH>& licensed_product() const { return licensed_product_; }

    static constexpr char const* LICENSE_TYPE_NAME = "license_type";
    inline void clear_license_type() { license_type_.clear(); }
    inline void set_license_type(const LicenseType& value) { license_type_ = value; }
    inline void set_license_type(const LicenseType&& value) { license_type_ = value; }
    inline const LicenseType& get_license_type() const { return license_type_.get(); }
    inline LicenseType license_type() const { return license_type_.get(); }

    static constexpr char const* LICENSE_EXPIRE_AT_NAME = "license_expire_at";
    inline void clear_license_expire_at() { license_expire_at_.clear(); }
    inline void set_license_expire_at(const int64_t& value) { license_expire_at_ = value; }
    inline void set_license_expire_at(const int64_t&& value) { license_expire_at_ = value; }
    inline int64_t& mutable_license_expire_at() { return license_expire_at_.get(); }
    inline const int64_t& get_license_expire_at() const { return license_expire_at_.get(); }
    inline int64_t license_expire_at() const { return license_expire_at_.get(); }

    static constexpr char const* TIMECENSE_MAX_VERSION_NAME = "timecense_max_version";
    inline void clear_timecense_max_version() { timecense_max_version_.clear(); }
    inline void set_timecense_max_version(const int32_t& value) { timecense_max_version_ = value; }
    inline void set_timecense_max_version(const int32_t&& value) { timecense_max_version_ = value; }
    inline int32_t& mutable_timecense_max_version() { return timecense_max_version_.get(); }
    inline const int32_t& get_timecense_max_version() const { return timecense_max_version_.get(); }
    inline int32_t timecense_max_version() const { return timecense_max_version_.get(); }

    static constexpr char const* TIMECENSE_KEY_NAME = "timecense_key";
    inline const TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>& timecense_key(uint32_t index) const { return timecense_key_[index]; }
    inline void clear_timecense_key() { timecense_key_.clear(); }
    inline void set_timecense_key(uint32_t index, const TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>& value) { timecense_key_.set(index, value); }
    inline void set_timecense_key(uint32_t index, const TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>&& value) { timecense_key_.set(index, value); }
    inline void set_timecense_key(const ::EmbeddedProto::RepeatedFieldFixedSize<TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>, LicensePack_timecense_key_REP_LENGTH>& values) { timecense_key_ = values; }
    inline void add_timecense_key(const TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>& value) { timecense_key_.add(value); }
    inline ::EmbeddedProto::RepeatedFieldFixedSize<TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>, LicensePack_timecense_key_REP_LENGTH>& mutable_timecense_key() { return timecense_key_; }
    inline TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>& mutable_timecense_key(uint32_t index) { return timecense_key_[index]; }
    inline const ::EmbeddedProto::RepeatedFieldFixedSize<TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>, LicensePack_timecense_key_REP_LENGTH>& get_timecense_key() const { return timecense_key_; }
    inline const ::EmbeddedProto::RepeatedFieldFixedSize<TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>, LicensePack_timecense_key_REP_LENGTH>& timecense_key() const { return timecense_key_; }

    static constexpr char const* ATTRIBUTE_NAME = "attribute";
    inline const AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>& attribute(uint32_t index) const { return attribute_[index]; }
    inline void clear_attribute() { attribute_.clear(); }
    inline void set_attribute(uint32_t index, const AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>& value) { attribute_.set(index, value); }
    inline void set_attribute(uint32_t index, const AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>&& value) { attribute_.set(index, value); }
    inline void set_attribute(const ::EmbeddedProto::RepeatedFieldFixedSize<AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>, LicensePack_attribute_REP_LENGTH>& values) { attribute_ = values; }
    inline void add_attribute(const AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>& value) { attribute_.add(value); }
    inline ::EmbeddedProto::RepeatedFieldFixedSize<AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>, LicensePack_attribute_REP_LENGTH>& mutable_attribute() { return attribute_; }
    inline AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>& mutable_attribute(uint32_t index) { return attribute_[index]; }
    inline const ::EmbeddedProto::RepeatedFieldFixedSize<AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>, LicensePack_attribute_REP_LENGTH>& get_attribute() const { return attribute_; }
    inline const ::EmbeddedProto::RepeatedFieldFixedSize<AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>, LicensePack_attribute_REP_LENGTH>& attribute() const { return attribute_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != issued_at_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = issued_at_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ISSUED_AT), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = licensee_name_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LICENSEE_NAME), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = licensee_email_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LICENSEE_EMAIL), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = licensed_product_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LICENSED_PRODUCT), buffer, false);
      }

      if((static_cast<LicenseType>(0) != license_type_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = license_type_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LICENSE_TYPE), buffer, false);
      }

      if((0 != license_expire_at_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = license_expire_at_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LICENSE_EXPIRE_AT), buffer, false);
      }

      if((0 != timecense_max_version_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = timecense_max_version_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TIMECENSE_MAX_VERSION), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = timecense_key_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TIMECENSE_KEY), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = attribute_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ATTRIBUTE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::ISSUED_AT:
            return_value = issued_at_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LICENSEE_NAME:
            return_value = licensee_name_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LICENSEE_EMAIL:
            return_value = licensee_email_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LICENSED_PRODUCT:
            return_value = licensed_product_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LICENSE_TYPE:
            return_value = license_type_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LICENSE_EXPIRE_AT:
            return_value = license_expire_at_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TIMECENSE_MAX_VERSION:
            return_value = timecense_max_version_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TIMECENSE_KEY:
            return_value = timecense_key_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ATTRIBUTE:
            return_value = attribute_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_issued_at();
      clear_licensee_name();
      clear_licensee_email();
      clear_licensed_product();
      clear_license_type();
      clear_license_expire_at();
      clear_timecense_max_version();
      clear_timecense_key();
      clear_attribute();

    }

#ifndef DISABLE_FIELD_NUMBER_TO_NAME 

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::ISSUED_AT:
          name = ISSUED_AT_NAME;
          break;
        case FieldNumber::LICENSEE_NAME:
          name = LICENSEE_NAME_NAME;
          break;
        case FieldNumber::LICENSEE_EMAIL:
          name = LICENSEE_EMAIL_NAME;
          break;
        case FieldNumber::LICENSED_PRODUCT:
          name = LICENSED_PRODUCT_NAME;
          break;
        case FieldNumber::LICENSE_TYPE:
          name = LICENSE_TYPE_NAME;
          break;
        case FieldNumber::LICENSE_EXPIRE_AT:
          name = LICENSE_EXPIRE_AT_NAME;
          break;
        case FieldNumber::TIMECENSE_MAX_VERSION:
          name = TIMECENSE_MAX_VERSION_NAME;
          break;
        case FieldNumber::TIMECENSE_KEY:
          name = TIMECENSE_KEY_NAME;
          break;
        case FieldNumber::ATTRIBUTE:
          name = ATTRIBUTE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#endif

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = issued_at_.to_string(left_chars, indent_level + 2, ISSUED_AT_NAME, true);
      left_chars = licensee_name_.to_string(left_chars, indent_level + 2, LICENSEE_NAME_NAME, false);
      left_chars = licensee_email_.to_string(left_chars, indent_level + 2, LICENSEE_EMAIL_NAME, false);
      left_chars = licensed_product_.to_string(left_chars, indent_level + 2, LICENSED_PRODUCT_NAME, false);
      left_chars = license_type_.to_string(left_chars, indent_level + 2, LICENSE_TYPE_NAME, false);
      left_chars = license_expire_at_.to_string(left_chars, indent_level + 2, LICENSE_EXPIRE_AT_NAME, false);
      left_chars = timecense_max_version_.to_string(left_chars, indent_level + 2, TIMECENSE_MAX_VERSION_NAME, false);
      left_chars = timecense_key_.to_string(left_chars, indent_level + 2, TIMECENSE_KEY_NAME, false);
      left_chars = attribute_.to_string(left_chars, indent_level + 2, ATTRIBUTE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int64 issued_at_ = 0;
      ::EmbeddedProto::FieldString<LicensePack_licensee_name_LENGTH> licensee_name_;
      ::EmbeddedProto::FieldString<LicensePack_licensee_email_LENGTH> licensee_email_;
      ::EmbeddedProto::RepeatedFieldFixedSize<::EmbeddedProto::FieldString<LicensePack_licensed_product_LENGTH>, LicensePack_licensed_product_REP_LENGTH> licensed_product_;
      EmbeddedProto::enumeration<LicenseType> license_type_ = static_cast<LicenseType>(0);
      EmbeddedProto::int64 license_expire_at_ = 0;
      EmbeddedProto::int32 timecense_max_version_ = 0;
      ::EmbeddedProto::RepeatedFieldFixedSize<TimecenseKey<LicensePack_timecense_key_TimecenseKey_module_LENGTH, LicensePack_timecense_key_TimecenseKey_id_LENGTH, LicensePack_timecense_key_TimecenseKey_key_LENGTH>, LicensePack_timecense_key_REP_LENGTH> timecense_key_;
      ::EmbeddedProto::RepeatedFieldFixedSize<AttributeEntry<LicensePack_attribute_AttributeEntry_key_LENGTH, LicensePack_attribute_AttributeEntry_value_LENGTH>, LicensePack_attribute_REP_LENGTH> attribute_;

};

} // End of namespace proto
} // End of namespace license
} // End of namespace jclab
} // End of namespace kr
#endif // JCLAB_LICENSE_H