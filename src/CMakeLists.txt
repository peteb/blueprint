link_directories( $ENV{BLUEPRINT_ROOT}/lib /usr/local/lib /usr/lib )
set (CURSES_NEED_NCURSES true)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

find_package(Curses)
find_package(SFML COMPONENTS graphics window system)
include_directories( $ENV{BLUEPRINT_ROOT}/inc $ENV{BLUEPRINT_ROOT}/src ${CURSES_INCLUDE_DIRS} ${SFML_INCLUDE_DIR} )
add_executable(blueprint
 	blueprint.cpp
	world_view.cpp
	input.cpp)
target_link_libraries (blueprint voidworld ${SFML_LIBRARIES} ${CURSES_LIBRARIES} panel glog)
