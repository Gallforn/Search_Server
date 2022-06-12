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

add_executable (Search_Server_Simple_Test Search_Server_Simple_Test.cpp ../../src/InvertedIndex.cpp ../../src/SearchServer.cpp)
add_executable (Search_Server_Top_5_Test Search_Server_Top_5_Test.cpp ../../src/InvertedIndex.cpp ../../src/SearchServer.cpp)

target_include_directories(Search_Server_Simple_Test PUBLIC ../../include)
target_include_directories(Search_Server_Top_5_Test PUBLIC ../../include)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(Search_Server_Simple_Test PRIVATE gtest_main)
target_link_libraries(Search_Server_Top_5_Test PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(Search_Server_Simple_Test)
gtest_discover_tests(Search_Server_Top_5_Test)