#include "EventHandler.h"
void EventHandler::addHandler(const std::string& eventName, EventFunction func) {
    eventMap[eventName].push_back(func);
}

void EventHandler::call(const std::string& method, const std::string& eventType, const json& data) {
    // Проверяем наличие метода method в eventMap
    if (eventMap.find(method) != eventMap.end()) {
        // Получаем список функций для данного метода
        const std::vector<std::function<void(const json&)>>& methodFunctions = eventMap[method];
        // Вызываем каждую функцию, передавая ей данные data
        for (const auto& func : methodFunctions) {
            func(data);
        }
    }

    if (eventMap.find(eventType) != eventMap.end()) {
        // Получаем список функций для данного eventType
        const std::vector<std::function<void(const json&)>>& eventTypeFunctions = eventMap[eventType];
        // Вызываем каждую функцию, передавая ей данные data
        for (const auto& func : eventTypeFunctions) {
            func(data);
        }
    }
}


void EventHandler::dataHandler(const json& data) {
    std::string method = std::to_string(data["t"].get<int>());
    std::string ws_event = "";
    std::string method_value = "";

    auto method_iter = EventTypes::ws_message_methods.find(method);
    if (method_iter != EventTypes::ws_message_methods.end()) {
        method_value = method_iter->second;
        if (method_value == "chat_action_start" || method_value == "chat_action_end") {
            std::string key = data["o"]["actions"].get<std::string>();
            auto action_start_iter = EventTypes::ws_chat_action_start.find(key);
            ws_event = (action_start_iter != EventTypes::ws_chat_action_start.end()) ? action_start_iter->second : "";
        } else if (method_value == "chat_message") {
            std::string key = std::to_string(data["o"]["chatMessage"]["type"].get<int>()) + ":" + std::to_string(data["o"]["chatMessage"].value("mediaType", 0));
            auto message_types_iter = EventTypes::ws_message_types.find(key);
            ws_event = (message_types_iter != EventTypes::ws_message_types.end()) ? message_types_iter->second : "";
        } else if (method_value == "notification") {
            std::string key = std::to_string(data["o"]["payload"]["notifType"].get<int>());
            auto notification_iter = EventTypes::notification_types.find(key);
            ws_event = (notification_iter != EventTypes::notification_types.end()) ? notification_iter->second : "";
        }
    }
    call(method_value, ws_event, data["o"]);
}