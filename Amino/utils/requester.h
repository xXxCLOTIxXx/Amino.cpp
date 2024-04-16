#ifndef REQUESTER_H
#define REQUESTER_H

#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "../libs/json.hpp"
using json = nlohmann::json;


#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>

#include "helpers.h"

#include "../objects/req_data.h"



namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;

class Requester {
public:
    Requester();
    ~Requester();

    std::string sendRequest(const std::string& method, const std::string& endpoint, const std::string& body = "", const int successfully = 200);
    http::response<http::dynamic_body> get(const std::string& endpoint);
    http::response<http::dynamic_body> post(const std::string& endpoint, const std::string& body);
    std::string delete_request(const std::string& endpoint);
    json json_parse(const std::string& data);

private:
    std::string host = "service.aminoapps.com";
    std::string api ="/api/v1/";

    ssl::context ctx_;  // SSL context member variable
};

#endif // REQUESTER_H
