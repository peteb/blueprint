cmake_minimum_required(VERSION 2.8)

add_library (worldgen worldgen.cpp)
target_link_libraries(worldgen noise glog)
