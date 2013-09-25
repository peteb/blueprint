cmake_minimum_required(VERSION 2.8)

link_directories( /usr/local/lib /usr/lib )
find_package(Curses)

include_directories( $ENV{VOIDS_ROOT}/include ${CURSES_INCLUDE_DIRS} )
add_executable(voids
 	voids.cpp
	screen.cpp)
target_link_libraries (voids ${CURSES_LIBRARIES})
