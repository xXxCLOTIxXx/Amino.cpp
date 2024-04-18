#include "Amino/Client.h"
#include "Amino/SubClient.h"



int main() {
    Client client;

    client.login("email@gmail.com", "password");
    //SubClient sub(client.profile, "your comId");

    std::ifstream file("image.png", std::ios::binary);
    std::cout << client.requester.upload_media(file, "image");
    //std::cout << sub.requester.upload_media(file, "image")

    //You can upload files from either of the two clients or from the requestser class itself
    return 0;
}