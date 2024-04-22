#pragma once

#include <thread>
#include <functional>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include "objects/constants.h"
#include "objects/req_data.h"
#include "utils/helpers.h"
#include "EventHandler.h"
#include "objects/Types.h"
using websocket_client = websocketpp::client<websocketpp::config::asio_tls_client>;


class Socket : public EventHandler{
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR,
        DEBUG,
        NONE
    };

    LogLevel loggerLevel = LogLevel::NONE; 

    req_data* profile;
    bool m_isConnected; 
    bool m_isConnecting;

    Socket(req_data* _profile);
    ~Socket();

    void connect();
    void disconnect();
    void send(const std::string& message);

    //actions
    void BrowsingBlogs(int comId, std::string blogId = "", int blogType = AccessTypes::PRIVATE);
    void Chatting(int comId, std::string chatId, int threadType = AccessTypes::PUBLIC);
    void PublicChats(int comId);
    void BrowsingLeaderBoards(int comId);
    void Browsing(int comId);
    void Typing(std::string chatId, int comId, int threadType = AccessTypes::PUBLIC);
    void Recording(std::string chatId, int comId, int threadType = AccessTypes::PUBLIC);
    void join_voice_chat(std::string chatId, int comId = 0, int joinType = WsJoinTypes::AS_PARTICIPANT);
    void join_video_chat(std::string chatId, int comId = 0, int joinType = WsJoinTypes::AS_PARTICIPANT);


private:
    void message_handler(websocketpp::connection_hdl hdl, websocket_client::message_ptr msg);
    void ws_headers(const websocketpp::connection_hdl& connection, const std::string& final);
    void on_disconnect(websocketpp::connection_hdl hdl);
    void connectionSupport();
    void log(LogLevel level, const std::string& message) const;
    
    websocket_client m_client;
    websocketpp::connection_hdl m_hdl;
    std::thread m_thread;
    std::thread m_supportThread;
};
