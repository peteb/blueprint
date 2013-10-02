#!/bin/sh
cd $BLUEPRINT_ROOT
rm -rf ./build > /dev/null
mkdir build
cd build
cmake ..
make -j9
