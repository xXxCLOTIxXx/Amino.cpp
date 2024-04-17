#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <string>

#include "../libs/json.hpp"
using json = nlohmann::json;


class InvalidRequestType : public std::runtime_error {
public:
    InvalidRequestType(const std::string& message) : std::runtime_error(message) {}
};




class UnknownError : public std::exception {
public:
    UnknownError(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
private:
    std::string message_;
};

class JsonDecodeError : public std::runtime_error {
public:
    JsonDecodeError(const std::string& message) : std::runtime_error(message) {}
};

class IpTemporaryBan : public std::runtime_error {
public:
    IpTemporaryBan(const std::string& message) : std::runtime_error(message) {}
};

class InvalidRequest : public std::runtime_error {
public:
    InvalidRequest(const std::string& message) : std::runtime_error(message) {}
};

class UnsupportedDeviceId : public std::runtime_error {
public:
    UnsupportedDeviceId(const std::string& message) : std::runtime_error(message) {}
};



void checkError(int statusCode, const std::string& data) {
    std::string message;
    int apiCode;
    try {
        json j = json::parse(data);

        apiCode = j["api:statuscode"];
        message = j["api:message"];
        message+= "[api:statuscode]: "+std::to_string(apiCode);
    } catch (std::exception const& e) {
        message = data;
        apiCode = -1;
    }

    switch (apiCode) {
        case 103:
            throw InvalidRequest(message);
        case 104:
            throw InvalidRequest(message);
        case 218:
            throw UnsupportedDeviceId(message);
        case -1:
            throw JsonDecodeError(message);
        default:
            throw UnknownError(message);
    }
}

#endif
