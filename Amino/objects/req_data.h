#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include "../libs/json.hpp"
using json = nlohmann::json;


struct req_data {
    std::string sid = "";
    std::string deviceId = "";
    std::string userId = "";
    std::string language;
    std::string user_agent;

};
#endif