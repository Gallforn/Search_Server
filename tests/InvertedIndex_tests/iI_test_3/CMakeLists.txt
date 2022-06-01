cmake_minimum_required(VERSION 3.20)
project(iI_test_3)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable (iI_test_3 main.cpp ../../../src/InvertedIndex.cpp)

target_include_directories(iI_test_3 PUBLIC ../../../include)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(iI_test_3 PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(iI_test_3)
