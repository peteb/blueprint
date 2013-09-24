cmake_minimum_required(VERSION 2.8)

link_directories( /usr/local/lib /usr/lib )
find_package(Curses)

include_directories( "$ENV{VOIDS_ROOT}/include" )
add_executable(voids
 	voids.cpp)
include_directories( $ENV{VOIDS_ROOT}/include $ENV{VOIDS_ROOT}/build/include )
if (CURSES_FOUND)
  include_directories(${CURSES_INCLUDE_DIRS})
  target_link_libraries (voids ${CURSES_LIBRARIES})
endif (CURSES_FOUND)
