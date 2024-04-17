#include "Client.h"

#include <iostream>

Client::Client(const std::string& deviceId, const std::string& user_agent, const std::string& language): requester(&profile) {
    profile.language = language;
    profile.user_agent = user_agent;
    if (deviceId.empty()) {
        profile.deviceId = Helpers::genDeviceId();
    } else {
        profile.deviceId = deviceId;
    }
}
json Client::login(std::string email, std::string password) {

    json data = {
        {"email", email},
        {"secret", "0 " + password},
        {"clientType", 100},
        {"deviceID", profile.deviceId},
        {"v", 2},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest("POST", "/g/s/auth/login", json_str);
    profile.userId = result["auid"]; profile.sid = result["sid"];

    return result;
}


json Client::logout() {

    json data = {
        {"clientType", 100},
        {"deviceID", profile.deviceId},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest("POST", "/g/s/auth/logout", json_str);
    profile.userId = ""; profile.sid = "";

    return result;
}


json Client::get_from_link(std::string link) {

    json result = requester.sendRequest("GET", "/g/s/link-resolution?q="+link);
    return result;
}