#include "requester.h"

Requester::Requester() : ctx_(ssl::context::tlsv12_client) {
    ctx_.set_default_verify_paths();
}

Requester::~Requester() {
    // Destructor implementation
}

std::string Requester::sendRequest(const std::string& method, const std::string& endpoint, const std::string& body, const int successfully) {
    http::response<http::dynamic_body> result;
    if (method == "GET"){
        result = Requester::get(endpoint);
    } else if (method == "POST"){
        result = Requester::post(endpoint, body);
    }

    return boost::beast::buffers_to_string(result.body().data());
}


json Requester::json_parse(const std::string& data){
    return json::parse(data);
}

http::response<http::dynamic_body> Requester::get(const std::string& endpoint) {
    try {
        net::io_context ioc;
        ssl::stream<tcp::socket> stream(ioc, ctx_);

        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(host, "https");

        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(ssl::stream_base::client);

        http::request<http::string_body> req{http::verb::get, api+endpoint, 11};
        req.set(http::field::host, host);
        Helpers::get_headers(req, Helpers::genDeviceId());

        http::write(stream, req);

        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        return res;
    } catch (std::exception const& e) {
        std::string responseBody = "Error: " + std::string(e.what());
        boost::beast::multi_buffer responseBuffer;
        responseBuffer.commit(boost::asio::buffer_copy(responseBuffer.prepare(responseBody.size()), boost::asio::buffer(responseBody)));
        http::response<http::dynamic_body> errorResponse{http::status::client_closed_request, 11, std::move(responseBuffer)};
        errorResponse.prepare_payload();
        return errorResponse;
    }
}

http::response<http::dynamic_body> Requester::post(const std::string& endpoint, const std::string& body) {
    try {
        net::io_context ioc;
        ssl::stream<tcp::socket> stream(ioc, ctx_);

        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(host, "https");

        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(ssl::stream_base::client);

        http::request<http::string_body> req{http::verb::post, api + endpoint, 11};
        req.set(http::field::host, host);
        Helpers::get_headers(req, Helpers::genDeviceId(), "", body);

        req.body() = body;
        req.prepare_payload();

        http::write(stream, req);

        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        return res;
    } catch (std::exception const& e) {
        std::string responseBody = "Error: " + std::string(e.what());
        boost::beast::multi_buffer responseBuffer;
        responseBuffer.commit(boost::asio::buffer_copy(responseBuffer.prepare(responseBody.size()), boost::asio::buffer(responseBody)));
        http::response<http::dynamic_body> errorResponse{http::status::client_closed_request, 11, std::move(responseBuffer)};
        errorResponse.prepare_payload();
        return errorResponse;
    }
}

std::string Requester::delete_request(const std::string& endpoint) {
    return "";
}
