#include "Amino/Client.h"
int main() {
    Client client;
    std::cout << client.get_from_link("http://aminoapps.com/p/13zo0g");

    return 0;
}
