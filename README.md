<body>

<h1 align="center">Amino.cpp</h1>
<h2 align="center">Examples (more examples in the corresponding directory):</h2>

<h2 align="center">Login</h2>

```с++
#include "Amino/Client.h"
#include "Amino/libs/json.hpp"
using json = nlohmann::json;

int main() {
    Client client;

    json data = client.login("example_mail@gmail.com", "example_password");
    std::cout << "userId: " << client.profile.userId << std::endl << "SID: " << client.profile.sid << std::endl;
    std::cout << std::endl << "Account info: " << data << std::endl;

    data = client.logout();
    std::cout << std::endl << "logout info: " << data << std::endl;
    return 0;
}
```
<h2 align="center">Get link info</h2>

```с++
#include "Amino/Client.h"
int main() {
    Client client;
    std::cout << client.get_from_link("http://aminoapps.com/p/13zo0g");

    return 0;
}

```

<h2 align="center">Compiling your programs:</h2>

```
g++ -std=c++11 -o programm filename.cpp Amino/Client.cpp Amino/utils/requester.cpp Amino/utils/helpers.cpp -L/usr/lib -lboost_system -lssl -lcrypto
```

<p align="center">or bash script (linux)</p>

```bash
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
