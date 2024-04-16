<body>

<h1 align="center">Amino.cpp</h1>
<h1 align="center">ACompiling your programs:</h1>


```
#!/bin/bash


g++ -std=c++11 -o programm filename.cpp Amino/Client.cpp Amino/utils/requester.cpp Amino/utils/helpers.cpp -L/usr/lib -lboost_system -lssl -lcrypto

if [ $? -eq 0 ]; then
    echo "Compilation completed successfully. Let's run the program:"
    ./programm
else
    echo "Compilation error."
fi
```

</body>
