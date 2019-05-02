cmake_minimum_required(VERSION 3.13)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        main.cpp
        encryption/encrypted.h
        lazy.h
        rand.h
        bytes.h
        range.h
        sfinae.h encryption/encryptor.h)

target_compile_features(main PRIVATE
        cxx_constexpr
        cxx_attributes
        cxx_attribute_deprecated
        cxx_contextual_conversions
        cxx_variadic_templates
        cxx_variable_templates
        )

find_package(fmt)
target_link_libraries(main fmt::fmt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O0")
