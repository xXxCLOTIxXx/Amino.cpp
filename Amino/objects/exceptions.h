#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class CustomError1 : public std::exception {
private:
    std::string errorMessage;

public:
    CustomError1(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

class CustomError2 : public std::exception {
private:
    std::string errorMessage;

public:
    CustomError2(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

#endif
