#!/bin/bash

if [ -f "libAmino.a" ]; then
    echo "File libAmino.a exists in the current directory."
else
    echo "Error: File libAmino.a not found in the current directory."
    exit 1
fi

g++ -std=c++11 -o programm main.cpp libAmino.a -L/usr/lib -lboost_system -lssl -lcrypto


if [ $? -eq 0 ]; then
    echo "Compilation completed successfully. Let's run the program:"
    ./programm
else
    echo "Compilation error."
fi
