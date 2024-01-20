cmake_minimum_required(VERSION 3.17)
project(Sets-Template)

if (APPLE)
    set(CMAKE_CXX_STANDARD 11)
endif()

# Precompile Catch2
add_library(catch2_main STATIC unit_tests/catch-main.cpp)
target_include_directories(catch2_main PUBLIC unit_tests/)

add_executable(Basic_SetType_Test SetType.h SetDriver.cpp)

add_executable(SetType_Tests unit_tests/SetType_Tests.cpp SetType.h unit_tests/unit_util.h)

# Use precompiled header for catch so recompiles are faster
target_link_libraries(SetType_Tests catch2_main)
target_compile_definitions(SetType_Tests PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(SetType_Tests PRIVATE unit_tests/catch.hpp)

if (APPLE)
    set_property(TARGET Basic_SetType_Test PROPERTY CXX_STANDARD 11)
    set_property(TARGET SetType_Tests PROPERTY CXX_STANDARD 11)
endif()
