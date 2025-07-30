cmake_minimum_required(VERSION 3.27)

project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
add_executable(sw_battle_test ${SOURCES})

target_include_directories(sw_battle_test PUBLIC src/)

# Google Tests
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Disable installing GTest
set(INSTALL_GTEST OFF)
set(BUILD_GMOCK OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(unit-tests
    src/IO/System/CommandParser.cpp
    src/Features/MarchUnit.cpp
    src/Features/AttackCloseUnit.cpp
    src/Features/AttackFarUnit.cpp
    
    tests/UnitsBaseTests.cpp
    tests/MarchableTests.cpp
    tests/StrengthableTests.cpp
    tests/AgiliableTests.cpp
    tests/CommandParserTests.cpp
    tests/IntegrationTests.cpp
)

target_include_directories(unit-tests PUBLIC src/)

target_link_libraries(unit-tests
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit-tests)