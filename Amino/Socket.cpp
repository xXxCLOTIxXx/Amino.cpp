#include "Socket.h"

Socket::Socket(req_data* _profile) : profile(_profile) {
    m_client.init_asio();
    m_client.set_tls_init_handler([](websocketpp::connection_hdl) {
        return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12);
    });
}

Socket::~Socket() {
    disconnect();
}

void Socket::connect() {
    m_client.set_message_handler(std::bind(&Socket::message_handler, this, std::placeholders::_1, std::placeholders::_2));
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
}

void Socket::disconnect() {
    websocketpp::lib::error_code ec;
    m_client.close(m_hdl, websocketpp::close::status::going_away, "", ec);
    if (ec) {
        std::cout << "Error disconnecting: " << ec.message() << std::endl;
    }
    if (m_thread.joinable()) {
        m_thread.join();
    }
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
        std::cout << "Received message: " << msg->get_payload() << std::endl;
        // Handle the received message here
    }
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

