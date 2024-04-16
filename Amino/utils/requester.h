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
    Requester(req_data* profile);
    //~Requester();

    json sendRequest(const std::string& method, const std::string& endpoint, const std::string& body = "", const int successfully = 200);
    http::response<http::dynamic_body> get(const std::string& endpoint);
    http::response<http::dynamic_body> post(const std::string& endpoint, const std::string& body);
    std::string delete_request(const std::string& endpoint);
    json json_parse(const std::string& data);
    void header(http::request<http::string_body>& req, const std::string& data = "", const std::string& content_type = "Apple iPhone12,1 iOS v15.5 Main/3.12.2");

private:
    std::string host = "service.aminoapps.com";
    std::string api ="/api/v1/";

    ssl::context ctx_; 
    req_data* profile_data;
};

#endif
