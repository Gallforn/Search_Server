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

add_executable (Inverted_Index_Basic_Test_1 Inverted_Index_Basic_Test_1.cpp ../../src/InvertedIndex.cpp)
add_executable (Inverted_Index_Basic_Test_2 Inverted_Index_Basic_Test_2.cpp ../../src/InvertedIndex.cpp)
add_executable (Inverted_Index_Missing_Word_Test Inverted_Index_Missing_Word_Test.cpp ../../src/InvertedIndex.cpp)

target_include_directories(Inverted_Index_Basic_Test_1 PUBLIC ../../include)
target_include_directories(Inverted_Index_Basic_Test_2 PUBLIC ../../include)
target_include_directories(Inverted_Index_Missing_Word_Test PUBLIC ../../include)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(Inverted_Index_Basic_Test_1 PRIVATE gtest_main)
target_link_libraries(Inverted_Index_Basic_Test_2 PRIVATE gtest_main)
target_link_libraries(Inverted_Index_Missing_Word_Test PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(Inverted_Index_Basic_Test_1)
gtest_discover_tests(Inverted_Index_Basic_Test_2)
gtest_discover_tests(Inverted_Index_Missing_Word_Test)