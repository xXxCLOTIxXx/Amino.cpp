#include "Client.h"

#include <iostream>

Client::Client(const std::string& deviceId, const std::string& user_agent, const std::string& language) {
    profile.language = language;
    profile.user_agent = user_agent;
    if (deviceId.empty()) {
        profile.deviceId = Helpers::genDeviceId();
    } else {
        profile.deviceId = deviceId;
    }
}
std::string Client::login(std::string email, std::string password) {

    json data = {
        {"email", email},
        {"secret", "0 " + password},
        {"clientType", 100},
        {"deviceID", profile.deviceId},
        {"v", 2}
    };
    std::string json_str = data.dump();
    return requester.sendRequest("POST", "/g/s/auth/login", json_str);
}