cmake_minimum_required(VERSION 2.8)

include_directories( ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR/lib/entities} )
add_library ( voidworld STATIC
  voidworld.cpp
  ../inc/voidworld.h
  omniview.cpp
  astar.cpp
  )

target_link_libraries( voidworld noise glog)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
