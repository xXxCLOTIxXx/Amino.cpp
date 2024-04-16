#include "requester.h"
#include "../objects/exceptions.h"

Requester::Requester(req_data* profile) : ctx_(ssl::context::tlsv12_client), profile_data(profile) {
    ctx_.set_default_verify_paths();
}

json Requester::sendRequest(const std::string& method, const std::string& endpoint, const std::string& body, const int successfully) {
    http::response<http::dynamic_body> result;
    if (method == "GET"){
        result = Requester::get(endpoint);
    } else if (method == "POST"){
        result = Requester::post(endpoint, body);
    }
    auto status_code = result.result_int();
    if (status_code != successfully){
        checkError(result.result_int(), boost::beast::buffers_to_string(result.body().data()));
    }
    return json_parse(boost::beast::buffers_to_string(result.body().data()));   
}


json Requester::json_parse(const std::string& data){
    return json::parse(data);
}

void Requester::header(http::request<http::string_body>& req, const std::string& data, const std::string& content_type){
    req.set(http::field::host, host);
    Helpers::set_headers(req, profile_data->deviceId, profile_data->sid, data, profile_data->user_agent, profile_data->language, content_type);
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
        header(req);
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
        header(req);
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
