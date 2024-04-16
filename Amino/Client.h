#ifndef CLIENT_H
#define CLIENT_H

#include "utils/requester.h"
#include "objects/req_data.h"

class Client {
public:
    req_data profile;
    Requester requester;

    Client(const std::string& deviceId = "", const std::string& user_agent = "Apple iPhone12,1 iOS v15.5 Main/3.12.2", const std::string& language = "en");

    json login(std::string email, std::string password);
    json get_from_link(std::string link);

};


#endif