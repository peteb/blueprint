cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/inc)
add_library (voidworld STATIC 
  voidworld.cpp
  voidworld_impl.cpp
  omniview.cpp
  astar.cpp
  resource_base.h
  )
target_link_libraries(voidworld noise glog)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
