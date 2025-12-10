cmake_minimum_required(VERSION 3.10)
project(jclab_license_test)

add_executable(jclab_license_test main.cc)

target_link_libraries(jclab_license_test
    jclab_license
)