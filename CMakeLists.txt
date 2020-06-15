cmake_minimum_required(VERSION 3.15)
project(lconf)

if(${CMAKE_SOURCE_DIR} EQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "lconf does not support in-tree builds")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LUA_STDLIB os io math str tab utf8)

set(LCONF_KNOWN_GENERATORS "make;ninja;msvc")

set(LCONF_DEFAULT_GENERATOR make CACHE STRING "Sets the Default generator to use for lconf")
set(LCONF_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/lib/lconf/modules/?.lua;${CMAKE_INSTALL_PREFIX}/lib/lconf/modules/?/init.lua")
set_property(CACHE LCONF_DEFAULT_GENERATOR PROPERTY STRINGS ${LCONF_KNOWN_GENERATORS})

configure_file("Configure.h.cmake.in" "Configure.h" ESCAPE_QUOTES)

add_subdirectory(lua)

add_subdirectory(C-Programming-Utilities/collect)

include_directories(lua)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(lconf-stage1 src/main.c src/Options.h src/Options.c)
set_target_properties(lconf-stage1 PROPERTIES OUTPUT_NAME "lconf")
target_link_libraries(lconf-stage1 lua-static collect)

option(LCONF_BUILD_BOOTSTRAP "Configures whether or not lconf will build itself" ON)

message(STATUS "Building lconf bootstrapped: ${LCONF_BUILD_BOOTSTRAP}")

if(LCONF_BUILD_BOOTSTRAP)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage2)
    add_custom_target(lconf-stage2 ALL
        DEPENDS lconf-stage1
        COMMAND $<TARGET_FILE:lconf-stage1> configure --generator=${LCONF_DEFAULT_GENERATOR}
        --module-path="${CMAKE_CURRENT_SOURCE_DIR}/modules/?.lua"
        --with-default-generator=${LCONF_DEFAULT_GENERATOR}
        --with-default-module-path=${LCONF_MODULE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND $<TARGET_FILE:lconf-stage1> build ${CMAKE_CURRENT_BINARY_DIR}/stage2
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage2)
    install(CODE "execute_process(COMMAND $<TARGET_FILE:lconf-stage1> install ${CMAKE_CURRENT_BINARY_DIR}/stage2)")
endif()
