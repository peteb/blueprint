link_directories( $ENV{BLUEPRINT_ROOT}/lib /usr/local/lib /usr/lib )
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

set (SFML_STATIC_LIBRARIES)
find_package(SFML REQUIRED COMPONENTS graphics window system network audio)
find_package(Boost REQUIRED)
find_package(Noise REQUIRED)
include_directories( ${Boost_INCLUDE_DIRS} $ENV{BLUEPRINT_ROOT}/lib $ENV{BLUEPRINT_ROOT}/inc $ENV{BLUEPRINT_ROOT}/src ${NOISE_INCLUDE_DIR} ${SFML_INCLUDE_DIR} )
add_executable(blueprint
 	blueprint.cpp
        common.h
        worldmap.h
        worldmap.cpp
        tileloader.h
        worldloader.h
	worldloader.cpp
        scenenode.h
        scenenode.cpp
        textureholder.h
        textureholder.cpp
        entity.h
        entity.cpp
        noiseutils.h
        noiseutils.cpp
	)
target_link_libraries (blueprint voidworld ${NOISE_LIBRARY} ${SFML_LIBRARIES} glog ${Boost_LIBRARIES} )
