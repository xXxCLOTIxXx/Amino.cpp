#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <string>

#include "../libs/json.hpp"
using json = nlohmann::json;


class UnknownError : public std::exception {
public:
    UnknownError(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
private:
    std::string message_;
};




class IpTemporaryBan : public std::runtime_error {
public:
    IpTemporaryBan(const std::string& message) : std::runtime_error(message) {}
};

class InvalidRequest : public std::runtime_error {
public:
    InvalidRequest(const std::string& message) : std::runtime_error(message) {}
};


void checkError(int statusCode, const std::string& data) {
    std::string message;
    int apiCode;
    try {
        json j = json::parse(data);

        message = j["api:message"];
        apiCode = j["api:statuscode"];
    } catch (std::exception const& e) {
        message = data;
        apiCode = 403;
    }

    switch (apiCode) {
        case 103:
            throw InvalidRequest(message);
        case 104:
            throw InvalidRequest(message);
        case 403:
            throw IpTemporaryBan(message);
        default:
            throw UnknownError(message);
    }
}

#endif
