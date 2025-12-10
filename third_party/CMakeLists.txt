if(NOT TARGET mbedtls)
    add_subdirectory(mbedtls)
endif()

if(NOT TARGET embedded_proto)
    file(GLOB embedded_proto_src_files
            "${CMAKE_CURRENT_SOURCE_DIR}/EmbeddedProto/src/*.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/EmbeddedProto/src/*.cpp"
    )

    add_library(embedded_proto STATIC ${embedded_proto_src_files})
    target_include_directories(embedded_proto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/EmbeddedProto/src)
endif()

if(NOT TARGET mbedtls_pkcs7_ex)
    set(MbedTLS_FOUND ON)
    set(MbedTLS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/include)
    set(MBEDTLS_LIBRARIES mbedtls mbedx509)
    add_subdirectory(mbedtls-pkcs7-ex)
endif()