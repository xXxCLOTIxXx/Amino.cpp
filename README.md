<body>
	<p align="center">
	    <a href="https://github.com/xXxCLOTIxXx/Amino.cpp/tree/main/docs/images/logo.png"><img src=""/></a>
	    <a href="https://github.com/xXxCLOTIxXx/Amino.cpp/releases"><img src="https://img.shields.io/github/v/release/xXxCLOTIxXx/Amino.cpp" alt="GitHub release" />
	    <a href="https://github.com/xXxCLOTIxXx/Amino.cpp/blob/main/LICENSE"><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="licence" /></a>
	    <a href="https://github.com/xXxCLOTIxXx/Amino.cpp/blob/main/docs/main.md"><img src="https://img.shields.io/website?down_message=failing&label=docs&up_color=green&up_message=passing&url=https://github.com/xXxCLOTIxXx/Amino.cpp/blob/main/docs/main.md" alt="docs" /></a>
	</p>
	<div align="center">
		<a href="https://github.com/xXxCLOTIxXx/xXxCLOTIxXx/blob/main/sponsor.md">
			<img src="https://img.shields.io/badge/%D0%A1%D0%BF%D0%BE%D0%BD%D1%81%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-Donate-F79B1F?style=for-the-badge&logo=github&logoColor=FF69B4&color=FF69B4" alt="Sponsor project"/>
		</a>
		<hr>
		<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=28&duration=2000&pause=2000&color=457b9d&random=false&width=200&repeat=false&lines=Installation" alt="Installation"/>
	
```bash
git clone https://github.com/xXxCLOTIxXx/Amino.cpp.git
```
<hr><br>
<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=28&duration=2000&pause=2000&color=457b9d&repeat=false&random=false&width=90&lines=Using" alt="Using"/>
</div>
<h4 align="center">Login example</h4>

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


```cpp
#include "Amino/Client.h"


void on_text_message(json data){
    std::cout << "Text message in chat" << std::endl;
}


void on_chat_message(json data){
    std::cout << "some message in chat" << std::endl;
    std::cout << data << std::endl;
}

int main() {
    Client client;
    std::cout << "All types of events: " << std::endl;
    std::vector<std::string>vec = EventTypes::all_ws_types();
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << std::endl;
    }

    client.login("email@gmail.com", "password");
    client.ws_socket.addHandler("on_text_message", on_text_message);
    client.ws_socket.addHandler("chat_message", on_chat_message);

    client.wait();
}
```

<br><hr>
<div align="center">
    <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=28&duration=2000&pause=2000&color=457b9d&repeat=false&random=false&width=134&lines=Building" alt="Building"/>
</div>

```bash
cd Amino.cpp
sh collect.sh
sh run.sh
```
<div align="center">
    
## or
</div>


### collect lib with cmake

```bash
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
```

### compiling program

```bash
#!/bin/bash

if [ ! -f "libAmino.a" ]; then
    echo "Error: File libAmino.a not found in the current directory."
    exit 1
fi

g++ -std=c++11 -o programm main.cpp libAmino.a -L/usr/lib -lboost_system -lssl -lcrypto
```
<div align="center">
    
# important, when compiling a program you also need to find the source code of the library (more precisely, the headers) and the assembled library file


<div align="center">   
<a href="https://github.com/xXxCLOTIxXx/Amino.cpp/blob/main/docs/main.md">
<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=14&duration=1&pause=31&color=457b9d&random=false&width=195&lines=Read+the+documentation" alt="=Read the documentation"/>
</a>
</div>
</body>
