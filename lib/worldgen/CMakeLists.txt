cmake_minimum_required(VERSION 2.8)

include_directories ($ENV{BLUEPRINT_ROOT}/libvoid/worldgen)
link_directories( /usr/local/lib /usr/lib )
add_library (worldgen worldgen.cpp)
target_link_libraries(worldgen noise glog)
