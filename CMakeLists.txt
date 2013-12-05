# CMake file for Blueprint

cmake_minimum_required (VERSION 2.8)
project (blueprint)

set (CMAKE_CXX_FLAGS "-Wall -std=c++11 -pedantic -pipe -ggdb -O0")
set (CMAKE_CXX_FLAGS_DEBUG "-ggdb -std=c++11 -O0")
set (CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O2")

message ("CMAKE Source Dir: " ${CMAKE_SOURCE_DIR})
message ("CMAKE Binary Dir: " ${CMAKE_BINARY_DIR})

include_directories (${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/inc)
add_subdirectory (3pp/SFML)
add_subdirectory (lib)
add_subdirectory (src)
add_subdirectory (unittest)
add_subdirectory (gtest)
add_subdirectory (lib/entities)
add_subdirectory (lib/worldgen)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

