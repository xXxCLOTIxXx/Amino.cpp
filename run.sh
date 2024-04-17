#!/bin/bash


g++ -std=c++11 -o programm main.cpp Amino/Client.cpp Amino/utils/requester.cpp Amino/utils/helpers.cpp Amino/objects/exceptions.h Amino/objects/constants.h -L/usr/lib -lboost_system -lssl -lcrypto

# Проверяем успешность компиляции
if [ $? -eq 0 ]; then
    echo "Compilation completed successfully. Let's run the program:"
    ./programm
else
    echo "Compilation error."
fi
