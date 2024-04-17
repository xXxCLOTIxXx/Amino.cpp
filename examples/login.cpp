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
