#ifndef ASYNC_SOCKET_H
#define ASYNC_SOCKET_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
//todo
class AsyncSocket {
public:
    AsyncSocket();
    ~AsyncSocket();

    void connect();
    void disconnect();
    void send(const std::string& message);

private:
    void async_read();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void run_io_context();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::thread thread_;
    boost::array<char, 1024> buffer_;
};

#endif
