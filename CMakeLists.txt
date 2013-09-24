cmake_minimum_required(VERSION 2.8)
project(voids)
add_subdirectory(src)
add_subdirectory(unittest)
add_subdirectory(gtest)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
# set (CURSES_LIBRARY "$ENV{VOIDS_ROOT}/build/lib/libncurses.a")
# set (CURSES_INCLUDE_PATH "$ENV{VOIDS_ROOT}/build/include")

# set (GTEST_LIBRARY "$ENV{VOIDS_ROOT}/build/lib/libgtest.a")
# set (GTEST_MAIN_LIBRARY "$ENV{VOIDS_ROOT}/build/lib/libgtest_main.a")
# set (GTEST_INCLUDE_DIR "$ENV{VOIDS_ROOT}/build/include")


link_directories (/usr/lib $ENV{VOIDS_ROOT}/gtest/lib)

#link_directories( $ENV{VOIDS_ROOT}/build/lib )
set(CMAKE_CXX_FLAGS "-Wall -pedantic -pipe -ggdb -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
