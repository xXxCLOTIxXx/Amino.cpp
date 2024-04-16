#ifndef AUTH_H
#define AUTH_H

struct req_data {
    std::string sid = "";
    std::string deviceId = "";
    std::string userId = "";
    std::string language;
    std::string user_agent;

};
#endif