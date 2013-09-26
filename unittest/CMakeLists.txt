cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
link_directories( /usr/local/lib /usr/lib $ENV{BLUEPRINT_ROOT}/gtest/lib $ENV{BLUEPRINT_ROOT}/gtest )
include_directories(${GTEST_INCLUDE_DIRS} $ENV{BLUEPRINT_ROOT}/src)
add_executable (blueprint-test blueprinttest.cpp)
target_link_libraries (blueprint-test gtest)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release"
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)
