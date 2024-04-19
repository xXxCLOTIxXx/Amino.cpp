#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include "objects/constants.h"
#include "objects/req_data.h"
#include "utils/helpers.h"
#include "EventHandler.h"
using websocket_client = websocketpp::client<websocketpp::config::asio_tls_client>;


#include "libs/json.hpp"
using json = nlohmann::json;


class Socket : public EventHandler{
public:
    req_data* profile;
    bool m_isConnected; 
    bool m_isConnecting;

    Socket(req_data* _profile);
    ~Socket();

    void connect();
    void disconnect();
    void send(const std::string& message);

private:
    void message_handler(websocketpp::connection_hdl hdl, websocket_client::message_ptr msg);
    void ws_headers(const websocketpp::connection_hdl& connection, const std::string& final);
    void on_disconnect(websocketpp::connection_hdl hdl);
    void connectionSupport();
    
    websocket_client m_client;
    websocketpp::connection_hdl m_hdl;
    std::thread m_thread;
    std::thread m_supportThread;
};
