cmake_minimum_required(VERSION 3.20)
project(Search_Engine)
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


add_executable (Search_Engine main.cpp search_except.cpp ConvertJson.cpp InvertedIndex.cpp SearchServer.cpp)

target_include_directories(Search_Engine PUBLIC ../include)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(Search_Engine PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(Search_Engine)













