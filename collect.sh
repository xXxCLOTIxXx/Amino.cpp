#!/bin/bash
mkdir build
if [ $? -ne 0 ]; then
    echo "Error: Failed to create the build directory."
    exit 1
fi
cd build
if [ $? -ne 0 ]; then
    echo "Error: Failed to change directory to build."
    exit 1
fi
cmake ..
if [ $? -ne 0 ]; then
    echo "Error: cmake exited with an error."
    exit 1
fi
make
if [ $? -ne 0 ]; then
    echo "Error: make exited with an error."
    exit 1
fi

echo "The library has been built. The file is located at libAmino.a"

