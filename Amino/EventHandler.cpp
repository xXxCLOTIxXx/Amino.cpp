#include "EventHandler.h"

void EventHandler::addHandler(const std::string& eventName, EventFunction func) {
    eventMap[eventName].push_back(func);
}

void EventHandler::call(const std::string& eventType, const json& data) {
    for (const auto& pair : eventMap) {
        if (pair.first.substr(0, eventType.size()) == eventType) {
            for (const auto& func : pair.second) {
                func(data);
            }
        }
    }
}
