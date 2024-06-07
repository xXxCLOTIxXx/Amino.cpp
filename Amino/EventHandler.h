#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include "objects/args/EventTypes.h"

#include "json.hpp"
using json = nlohmann::json;

using EventFunction = std::function<void(const json&)>;

class EventHandler {
private:
    std::unordered_map<std::string, std::vector<EventFunction>> eventMap;

public:
    EventHandler() {}
    void addHandler(const std::string& eventName, EventFunction func);
    void call(const std::string& method, const std::string& eventType, const json& data);
    void dataHandler(const json& data);
};

#endif
