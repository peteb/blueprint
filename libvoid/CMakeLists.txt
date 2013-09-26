cmake_minimum_required(VERSION 2.8)
include_directories ($ENV{BLUEPRINT_ROOT}/include)
add_library (void libvoid.cpp astar.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_CXX_FLAGS "-Wall -pedantic -pipe -ggdb -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
