#include "Socket.h"
#include <iostream> 
#include <boost/bind.hpp>
#include "objects/constants.h"
#include "utils/helpers.h"
//todo
AsyncSocket::AsyncSocket() : io_context_(), socket_(io_context_), thread_() {}

AsyncSocket::~AsyncSocket() {
    disconnect();
}

void AsyncSocket::connect() {
    try {
        boost::asio::ip::tcp::resolver resolver(io_context_);
        auto endpoints = resolver.resolve(Constants::SOCKET_ADDRESS+"/?signbody="+Helpers::sock_signbody(), std::to_string(Constants::SOCKET_PORT));
        boost::asio::connect(socket_, endpoints);

        thread_ = boost::thread(boost::bind(&AsyncSocket::run_io_context, this));
        async_read();
    } catch (std::exception& e) {
        std::cerr << "Connect error: " << e.what() << std::endl;
    }
}

void AsyncSocket::disconnect() {
    try {
        io_context_.stop();
        if (thread_.joinable()) {
            thread_.join();
        }
        socket_.close();
    } catch (std::exception& e) {
        std::cerr << "Disconnect error: " << e.what() << std::endl;
    }
}

void AsyncSocket::send(const std::string& message) {
    try {
        boost::asio::write(socket_, boost::asio::buffer(message));
    } catch (std::exception& e) {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}

void AsyncSocket::async_read() {
    boost::asio::async_read(socket_, boost::asio::buffer(buffer_), boost::bind(&AsyncSocket::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void AsyncSocket::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        std::string received(buffer_.data(), bytes_transferred);
        std::cout << "Received: " << received << std::endl;
        async_read(); // Continue reading
    } else {
        std::cerr << "Read error: " << error.message() << std::endl;
    }
}

void AsyncSocket::run_io_context() {
    try {
        io_context_.run();
    } catch (std::exception& e) {
        std::cerr << "IO context error: " << e.what() << std::endl;
    }
}
