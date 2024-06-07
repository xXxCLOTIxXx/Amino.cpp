#include "requester.h"


Requester::Requester(req_data* profile) : ctx_(ssl::context::tlsv12_client), profile_data(profile) {
    ctx_.set_default_verify_paths();
}

json Requester::sendRequest(RequestTypes method, const std::string& endpoint, const std::string& body, const int successfully, const std::string& content_type) {
    http::response<http::dynamic_body> result;
    switch (method) {
    case RequestTypes::POST:
        result = Requester::post(endpoint, body, content_type);

        break;
    case RequestTypes::GET:
        result = Requester::get(endpoint, content_type);

        break;
    case RequestTypes::DELETE:
        result = Requester::delete_request(endpoint, content_type);

        break;
    default:
        throw InvalidRequestType("Invalid request method");

        break;
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
    return sendRequest(RequestTypes::POST, "/g/s/media/upload", data, 200, t);
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
        case -1:
            throw JsonDecodeError(message);
        case 100:
            throw UnsupportedService(message);
        case 102:
            throw FileTooLarge(message);
        case 103:
            throw InvalidRequest(message);
        case 104:
            throw InvalidRequest(message);
        case 105:
            throw InvalidSession(message);
        case 106:
            throw AccessDenied(message);
        case 107:
            throw UnexistentData(message);
        case 110:
            throw ActionNotAllowed(message);
        case 111:
            throw ServiceUnderMaintenance(message);
        case 113:
            throw MessageNeeded(message);
        case 200:
            throw InvalidAccountOrPassword(message);
        case 201:
            throw AccountDisabled(message);
        case 213:
            throw InvalidEmail(message);
        case 214:
            throw InvalidPassword(message);
        case 215:
            throw EmailAlreadyTaken(message);
        case 216:
            throw AccountDoesNotExist(message);
        case 218:
            throw UnsupportedDeviceId(message);
        case 219:
            throw AccountLimitReached(message);
        case 221:
            throw CantFollowYourself(message);
        case 225:
            throw UserUnavailable(message);
        case 229:
            throw YouAreBanned(message);
        case 230:
            throw UserNotMemberOfCommunity(message);
        case 235:
            throw RequestRejected(message);
        case 238:
            throw ActivateAccount(message);
        case 239:
            throw CantLeaveCommunity(message);
        case 240:
            throw ReachedTitleLength(message);
        case 245:
            throw UserHasBeenDeleted(message);
        case 246:
            throw AccountDeleted(message);
        case 251:
            throw API_ERR_EMAIL_NO_PASSWORD(message);
        case 257:
            throw API_ERR_COMMUNITY_USER_CREATED_COMMUNITIES_VERIFY(message);
        case 262:
            throw ReachedMaxTitles(message);
        case 270:
            throw VerificationRequired(message);
        case 271:
            throw API_ERR_INVALID_AUTH_NEW_DEVICE_LINK(message);
        case 291:
            throw CommandCooldown(message);
        case 293:
            throw UserBannedByTeamAmino(message);
        case 300:
            throw BadImage(message);
        case 313:
            throw InvalidThemepack(message);
        case 314:
            throw InvalidVoiceNote(message);
        case 403:
            throw IpTemporaryBan(message);
        case 500:
        case 700:
        case 1600:
            throw RequestedNoLongerExists(message);
        case 503:
            throw PageRepostedTooRecently(message);
        case 551:
            throw InsufficientLevel(message);
        case 702:
            throw WallCommentingDisabled(message);
        case 801:
            throw CommunityNoLongerExists(message);
        case 802:
            throw InvalidCodeOrLink(message);
        case 805:
            throw CommunityNameAlreadyTaken(message);
        case 806:
            throw CommunityCreateLimitReached(message);
        case 814:
            throw CommunityDisabled(message);
        case 833:
            throw CommunityDeleted(message);
        case 1501:
            throw DuplicatePollOption(message);
        case 1507:
            throw ReachedMaxPollOptions(message);
        case 1602:
            throw TooManyChats(message);
        case 1605:
            throw ChatFull(message);
        case 1606:
            throw TooManyInviteUsers(message);
        case 1611:
            throw ChatInvitesDisabled(message);
        case 1612:
            throw RemovedFromChat(message);
        case 1613:
            throw UserNotJoined(message);
        case 1627:
            throw API_ERR_CHAT_VVCHAT_NO_MORE_REPUTATIONS(message);
        case 1637:
            throw MemberKickedByOrganizer(message);
        case 1661:
            throw LevelFiveRequiredToEnableProps(message);
        case 1663:
            throw ChatViewOnly(message);
        case 1664:
            throw ChatMessageTooBig(message);
        case 1900:
            throw InviteCodeNotFound(message);
        case 2001:
            throw AlreadyRequestedJoinCommunity(message);
        case 2501:
            throw API_ERR_PUSH_SERVER_LIMITATION_APART(message);
        case 2502:
            throw API_ERR_PUSH_SERVER_LIMITATION_COUNT(message);
        case 2503:
            throw API_ERR_PUSH_SERVER_LINK_NOT_IN_COMMUNITY(message);
        case 2504:
            throw API_ERR_PUSH_SERVER_LIMITATION_TIME(message);
        case 2601:
            throw AlreadyCheckedIn(message);
        case 2611:
            throw AlreadyUsedMonthlyRepair(message);
        case 2800:
            throw AccountAlreadyRestored(message);
        case 3102:
            throw IncorrectVerificationCode(message);
        case 3905:
            throw NotOwnerOfChatBubble(message);
        case 4300:
            throw NotEnoughCoins(message);
        case 4400:
            throw AlreadyPlayedLottery(message);
        case 4500:
        case 4501:
            throw CannotSendCoins(message);
        case 4805:
            throw FailedSubscribeFanClub(message);
        case 6001:
            throw AminoIDAlreadyChanged(message);
        case 6002:
            throw InvalidAminoID(message);
        case 9901:
            throw InvalidName(message);
        default:
            throw UnknownError(message);
    }
}
