link_directories( $ENV{BLUEPRINT_ROOT}/lib /usr/local/lib /usr/lib )
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

set (SFML_STATIC_LIBRARIES)
find_package(SFML COMPONENTS graphics window system network audio)
find_package(Boost REQUIRED)
include_directories( ${Boost_INCLUDE_DIRS} $ENV{BLUEPRINT_ROOT}/lib $ENV{BLUEPRINT_ROOT}/inc $ENV{BLUEPRINT_ROOT}/src ${SFML_INCLUDE_DIR} )
add_executable(blueprint
 	blueprint.cpp
	)
target_link_libraries (blueprint voidworld ${SFML_LIBRARIES} glog ${Boost_LIBRARIES} )
