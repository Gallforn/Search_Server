cmake_minimum_required(VERSION 3.20)
project(Search_Engine VERSION 0.2)
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

add_executable (sS_test_1 sS_test_1.cpp ../../src/InvertedIndex.cpp ../../src/SearchServer.cpp)
add_executable (sS_test_2 sS_test_2.cpp ../../src/InvertedIndex.cpp ../../src/SearchServer.cpp)

target_include_directories(sS_test_1 PUBLIC ../../include)
target_include_directories(sS_test_2 PUBLIC ../../include)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(sS_test_1 PRIVATE gtest_main)
target_link_libraries(sS_test_2 PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(sS_test_1)
gtest_discover_tests(sS_test_2)