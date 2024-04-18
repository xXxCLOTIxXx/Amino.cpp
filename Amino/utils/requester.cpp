#include "requester.h"

Requester::Requester(req_data* profile) : ctx_(ssl::context::tlsv12_client), profile_data(profile) {
    ctx_.set_default_verify_paths();
}

json Requester::sendRequest(std::string method, const std::string& endpoint, const std::string& body, const int successfully, const std::string& content_type) {
    http::response<http::dynamic_body> result;
    method = Helpers::upper(method);
    if (method == "GET"){
        result = Requester::get(endpoint, content_type);
    } else if (method == "POST"){
        result = Requester::post(endpoint, body, content_type);
    } else if (method == "DELETE"){
        result = Requester::delete_request(endpoint, content_type);
    } else{
        throw InvalidRequestType("Invalid request type ["+method+"]");
    }
    auto status_code = result.result_int();
    if (status_code != successfully){
        Requester::checkError(result.result_int(), boost::beast::buffers_to_string(result.body().data()));
    }
    return json::parse(boost::beast::buffers_to_string(result.body().data()));   
}

void Requester::header(http::request<http::string_body>& req, const std::string& data, const std::string& content_type){
    req.set(http::field::host, Constants::HTTPS_HOST);
    Helpers::set_headers(req, profile_data->deviceId, profile_data->sid, profile_data->userId, data, profile_data->user_agent, profile_data->language, content_type);
}



http::response<http::dynamic_body> Requester::get(const std::string& endpoint, const std::string& content_type) {
    try {
        net::io_context ioc;
        ssl::stream<tcp::socket> stream(ioc, ctx_);
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(Constants::HTTPS_HOST, "https");
        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(ssl::stream_base::client);
        http::request<http::string_body> req{http::verb::get, Constants::API_ENDPOINT+endpoint, 11};
        header(req, "", content_type);
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

http::response<http::dynamic_body> Requester::post(const std::string& endpoint, std::string body, const std::string& content_type) {
    try {
        net::io_context ioc;
        ssl::stream<tcp::socket> stream(ioc, ctx_);
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(Constants::HTTPS_HOST, "https");
        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(ssl::stream_base::client);
        http::request<http::string_body> req{http::verb::post, Constants::API_ENDPOINT + endpoint, 11};
        req.set(http::field::host, Constants::HTTPS_HOST);

        if (body!=""){
            if (content_type == "application/json"){
                json temp = json::parse(body);
                temp["timestamp"] = Helpers::timestamp();
                body=temp.dump();
            }
            header(req, body, content_type);
            req.body() = body;
        } else{
            header(req, body, "application/x-www-form-urlencoded");
        }

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

http::response<http::dynamic_body> Requester::delete_request(const std::string& endpoint, const std::string& content_type) {
    try {
        net::io_context ioc;
        ssl::stream<tcp::socket> stream(ioc, ctx_);
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(Constants::HTTPS_HOST, "https");
        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(ssl::stream_base::client);
        http::request<http::string_body> req{http::verb::delete_, Constants::API_ENDPOINT+endpoint, 11};
        header(req, "", content_type);
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


json Requester::upload_media(std::ifstream& file, const std::string& fileType){
    std::string t;
    if (fileType == "audio") {
        t = "audio/aac";
    } else if (fileType == "image") {
        t = "image/jpg";
    } else if (fileType == "gif"){
        t = "image/gif";
    } else {
        throw ArgumentError("SpecifyType Error: Invalid file type");
    }
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return sendRequest("POST", "/g/s/media/upload", data, 200, t);
}



void Requester::checkError(int statusCode, const std::string& data) {
    std::cout << data;
    std::string message;
    int apiCode;
    try {
        json j = json::parse(data);

        apiCode = j["api:statuscode"];
        message = j["api:message"];
        message+= "[api:statuscode]: "+std::to_string(apiCode);
    } catch (std::exception const& e) {
        message = data;
        apiCode = -1;
    }

    switch (apiCode) {
        case 103:
            throw InvalidRequest(message);
        case 104:
            throw InvalidRequest(message);
        case 216:
            throw AccountDoesNotExist(message);
        case 218:
            throw UnsupportedDeviceId(message);
        case -1:
            throw JsonDecodeError(message);
        default:
            throw UnknownError(message);
    }
}