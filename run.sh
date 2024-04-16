#!/bin/bash

# Компилируем исходный код с помощью g++
g++ -std=c++11 -o MyExecutable test.cpp Amino/Client.cpp Amino/utils/requester.cpp Amino/utils/helpers.cpp -L/usr/lib -lboost_system -lssl -lcrypto

#g++ -std=c++11 -o MyExecutable test.cpp -L/usr/lib -lboost_system -lssl -lcrypto

# Проверяем успешность компиляции
if [ $? -eq 0 ]; then
    echo "Компиляция завершена успешно. Запускаем программу:"
    ./MyExecutable
else
    echo "Ошибка при компиляции."
fi
