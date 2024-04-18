#ifndef REQUESTER_H
#define REQUESTER_H

#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "../libs/json.hpp"
#include <fstream>
using json = nlohmann::json;


#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>

#include "helpers.h"

#include "../objects/req_data.h"
#include "../objects/exceptions.h"

#include "../libs/json.hpp"
#include "../objects/constants.h"
using json = nlohmann::json;

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;

class Requester {
public:
    Requester(req_data* profile);
    //~Requester();
    enum RequestTypes {POST, GET, DELETE};
    json sendRequest(RequestTypes method, const std::string& endpoint, const std::string& body = "", const int successfully = 200, const std::string& content_type = "application/json");
    http::response<http::dynamic_body> get(const std::string& endpoint, const std::string& content_type = "application/json");
    http::response<http::dynamic_body> post(const std::string& endpoint, std::string body = "", const std::string& content_type = "application/json");
    http::response<http::dynamic_body> delete_request(const std::string& endpoint, const std::string& content_type = "application/json");
    void header(http::request<http::string_body>& req, const std::string& data = "", const std::string& content_type = "application/json");
    void checkError(int statusCode, const std::string& data);

    json upload_media(std::ifstream& file, const std::string& fileType);

private:
    ssl::context ctx_; 
    req_data* profile_data;
};

#endif
