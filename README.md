<body>

<h1 align="center">Amino.cpp</h1>
<h2 align="center">Examples (more examples in the corresponding directory):</h2>

<h3 align="center">Login</h3>

```cpp
#include "Amino/Client.h"

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
<h3 align="center">Get link info</h3>

```cpp
#include "Amino/Client.h"
int main() {
    Client client;
    std::cout << client.get_from_link("http://aminoapps.com/p/13zo0g");

    return 0;
}

```
<br>
<h2 align="center">Install lib & Compiling your programs:</h2>

```bash
git clone https://github.com/xXxCLOTIxXx/Amino.cpp.git
cd Amino.cpp
sh collect.sh
sh run.sh
```
<p align="center">when you run run.sh, there should be a file with your main.cpp code in the same directory</p>
</body>
