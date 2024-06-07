#ifndef EventTypes_H
#define EventTypes_H

#include <unordered_map>
#include <vector>
#include <string>

namespace EventTypes {
    extern const std::unordered_map<std::string, std::string> ws_message_methods;
    extern const std::unordered_map<std::string, std::string> ws_chat_action_start;
    extern const std::unordered_map<std::string, std::string> ws_chat_action_end;
    extern const std::unordered_map<std::string, std::string> notification_types;
    extern const std::unordered_map<std::string, std::string> ws_message_types;

    std::vector<std::string> all_ws_types();
}

#endif