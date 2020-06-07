cmake_minimum_required(VERSION 3.15)
project(lconf)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(LUA_STDLIB os io math str tab utf8)

add_subdirectory(lua)

include_directories(lua)

add_executable(lcconf main.cpp src/Target.hpp)

target_link_libraries(lcconf lua-static)
