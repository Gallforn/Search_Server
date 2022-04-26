cmake_minimum_required(VERSION 3.20)
project(Search_Engine)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_executable (Search_Engine main.cpp search_except.cpp ConvertJson.cpp InvertedIndex.cpp SearchServer.cpp)

target_include_directories(Search_Engine PUBLIC ../include)

target_link_libraries(Search_Engine PRIVATE nlohmann_json::nlohmann_json)










