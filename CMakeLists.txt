cmake_minimum_required(VERSION 3.10)
project(jclab_license)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third_party)

# Generate headers
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/jclab_license/generated/jclab_license_authority.h
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_cert_header.sh
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/internal/jclabconstant/jclab_license_authority.der
)
add_custom_target(generate_headers DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/jclab_license/generated/jclab_license_authority.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/jclab_license/generated/jclab_license.h
)

# Protobuf generation
set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/java/jclab-license-model/src/main/proto/jclab_license.proto)
set(GENERATED_PROTO_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/jclab_license/generated/jclab_license.h)

add_custom_command(
    OUTPUT ${GENERATED_PROTO_HEADER}
    COMMAND ${CMAKE_COMMAND} -E make_directory include/jclab_license/generated
    COMMAND ${CMAKE_COMMAND} -E env "PATH=${CMAKE_CURRENT_SOURCE_DIR}/third_party/EmbeddedProto/venv/bin:/usr/local/bin:/usr/bin:/bin"
            protoc
            --plugin=protoc-gen-eams=${CMAKE_CURRENT_SOURCE_DIR}/third_party/EmbeddedProto/venv/bin/protoc-gen-eams
            --eams_out=${CMAKE_CURRENT_SOURCE_DIR}/include/jclab_license/generated
            --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/java/jclab-license-model/src/main/proto
            ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
)

add_library(jclab_license STATIC
        src/read_buffer_read_only.cc
        src/read_buffer_read_only.h
        src/license_verifier.cc
        src/crypto/crypto_provider.h
        src/crypto/mbedtls/mbedtls_provider.h
        src/crypto/mbedtls/mbedtls_provider.cc
        ${GENERATED_PROTO_HEADER}
)

add_dependencies(jclab_license generate_headers)

target_include_directories(jclab_license PUBLIC include)
target_include_directories(jclab_license PRIVATE src)
target_link_libraries(jclab_license PUBLIC
        embedded_proto
)
target_link_libraries(jclab_license PRIVATE
        mbedtls
        mbedx509
        mbedtls_pkcs7_ex
)

add_subdirectory(test)