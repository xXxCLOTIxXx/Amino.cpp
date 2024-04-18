#include "Socket.h"

//In development, still a rough sketch

Socket::Socket(req_data* _profile) : profile(_profile), m_isConnected(false), m_isConnecting(false) {
    m_client.init_asio();
    m_client.set_tls_init_handler([](websocketpp::connection_hdl) {
        return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12);
    });
    m_client.set_access_channels(websocketpp::log::alevel::none);
}

Socket::~Socket() {
    disconnect();
}


void Socket::ws_headers(const websocketpp::connection_hdl& connection, const std::string& final) {
    auto con = m_client.get_con_from_hdl(connection);
    if (con) {
        con->append_header("NDCDEVICEID", profile->deviceId);
        con->append_header("NDCAUTH", "sid="+profile->sid);
        con->append_header("NDC-MSG-SIG", Helpers::genSignature(final));
    } else {
        std::cout << "Error: Invalid connection handle" << std::endl;
    }
}


void Socket::connect() {
    if (m_isConnected || m_isConnecting) {return;}
    m_isConnecting = true;

    m_client.set_message_handler(std::bind(&Socket::message_handler, this, std::placeholders::_1, std::placeholders::_2));
    m_client.set_close_handler(std::bind(&Socket::on_disconnect, this, std::placeholders::_1));
    websocketpp::lib::error_code ec;
    std::string final = profile->deviceId+"|"+std::to_string(Helpers::timestamp());
    std::string url = Constants::SOCKET_ADDRESS+"/?signbody="+Helpers::replaceChars(final, '|', "%7C");
    auto con = m_client.get_connection(url, ec);
    if (ec) {
        std::cout << "Error connecting: " << ec.message() << std::endl;
        return;
    }
    ws_headers(con, final);

    m_hdl = con->get_handle();
    m_client.connect(con);

    m_thread = std::thread([this]() {
        m_client.run();
    });

    m_supportThread = std::thread([this]() {
        connectionSupport();
    });
    m_isConnected = true;
    m_isConnecting = false;

}

void Socket::connectionSupport() {
    while (m_isConnected) {
        send(R"({"t": 116, "o": {"threadChannelUserInfoList": []}})");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

void Socket::disconnect() {
    if (!m_isConnected) {return;}

    websocketpp::lib::error_code ec;
    m_client.close(m_hdl, websocketpp::close::status::going_away, "", ec);
    if (ec) {
        std::cout << "Error disconnecting: " << ec.message() << std::endl;
    }
    if (m_thread.joinable()) {
        m_thread.join();
    }
    if (m_supportThread.joinable()) {
        m_supportThread.join();
    }
    m_client.set_close_handler(nullptr);
    m_isConnected = false;
}


void Socket::on_disconnect(websocketpp::connection_hdl hdl) {
    websocketpp::lib::error_code ec;
    auto con = m_client.get_con_from_hdl(hdl, ec);
    if (ec) {
        std::cerr << "Error getting connection from handle: " << ec.message() << std::endl;
        return;
    }

    auto close_code = con->get_remote_close_code();
    auto close_reason = con->get_remote_close_reason();

    std::cout << "Disconnected with code: " << close_code << " (" << close_reason << ")" << std::endl;
    disconnect();

}



void Socket::send(const std::string& message) {
    websocketpp::lib::error_code ec;
    m_client.send(m_hdl, message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        std::cout << "Error sending message: " << ec.message() << std::endl;
    }
}

void Socket::message_handler(websocketpp::connection_hdl hdl, websocket_client::message_ptr msg) {
    if (hdl.lock() == m_hdl.lock()) {

        try {
            json jsonData = json::parse(msg->get_payload());
            dataHandler(jsonData);
        } catch (const json::parse_error& e) {
    }
}

}