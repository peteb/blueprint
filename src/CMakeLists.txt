cmake_minimum_required(VERSION 2.8)

link_directories( $ENV{BLUEPRINT_ROOT}/libvoid /usr/local/lib /usr/lib )
find_package(Curses)

include_directories( $ENV{BLUEPRINT_ROOT}/src $ENV{BLUEPRINT_ROOT}/include ${CURSES_INCLUDE_DIRS} )
add_executable(blueprint
 	blueprint.cpp
	screen.cpp
	input.cpp)
target_link_libraries (blueprint void ${CURSES_LIBRARIES})
