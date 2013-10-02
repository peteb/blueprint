link_directories( $ENV{BLUEPRINT_ROOT}/lib /usr/local/lib /usr/lib )
set (CURSES_NEED_NCURSES true)
find_package(Curses)

include_directories( $ENV{BLUEPRINT_ROOT}/inc $ENV{BLUEPRINT_ROOT}/src ${CURSES_INCLUDE_DIRS} )
add_executable(blueprint
 	blueprint.cpp
	world_view.cpp
	input.cpp)
target_link_libraries (blueprint voidworld ${CURSES_LIBRARIES} panel glog)
