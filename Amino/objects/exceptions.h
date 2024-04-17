#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <string>
#include <stdexcept>


class InvalidRequestType : public std::runtime_error {
public:
    InvalidRequestType(const std::string& message) : std::runtime_error(message) {}
};


class ArgumentError : public std::runtime_error {
public:
    ArgumentError(const std::string& message) : std::runtime_error(message) {}
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

class AccountDoesNotExist : public std::runtime_error {
public:
    AccountDoesNotExist(const std::string& message) : std::runtime_error(message) {}
};


#endif
