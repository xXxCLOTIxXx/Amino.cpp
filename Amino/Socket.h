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
using websocket_client = websocketpp::client<websocketpp::config::asio_tls_client>;

class Socket {
public:
    req_data* profile;

    Socket(req_data* _profile);
    ~Socket();

    void connect();
    void disconnect();
    void send(const std::string& message);
    void ws_headers(const websocketpp::connection_hdl& connection, const std::string& final);

private:
    void message_handler(websocketpp::connection_hdl hdl, websocket_client::message_ptr msg);
    
    websocket_client m_client;
    websocketpp::connection_hdl m_hdl;
    std::thread m_thread;
};
