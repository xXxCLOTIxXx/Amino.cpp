#include "Client.h"


/*
TODO:
global socket requests
clear code
clean imports
add objects for functions
add features
*/


Client::Client(const std::string& deviceId, bool _run_socket, const std::string& user_agent, const std::string& language): requester(&profile), socket_enabladed(_run_socket), ws(&profile) {
    profile.language = language;
    profile.user_agent = user_agent;
    if (deviceId.empty()) {
        profile.deviceId = Helpers::genDeviceId();
    } else {
        profile.deviceId = deviceId;
        
    }
}

json Client::login(std::string email, std::string password, std::string secret) {
    
    if (password == "" && secret == ""){
        throw  ArgumentError("Authorization key not specified.");
    }
    json data = {
        {"email", email},
        {"secret", (secret == "") ? "0 " + password : secret},
        {"clientType", 100},
        {"deviceID", profile.deviceId},
        {"v", 2},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/login", json_str);
    profile.userId = result["auid"]; profile.sid = result["sid"];
    if (socket_enabladed){
        ws.connect();
    }

    return result;
}


std::string Client::login_sid(std::string sid) {
    
    std::string uid = Helpers::sid_to_uid(sid);
    profile.userId = uid; profile.sid = sid;

    if (socket_enabladed){
        ws.connect();
    }
    return uid;
}

json Client::login_phone(std::string number, std::string password) {
    
    json data = {
        {"phoneNumber", number},
        {"secret", "0 " + password},
        {"clientType", 100},
        {"deviceID", profile.deviceId},
        {"v", 2},
        {"action", "normal"}
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/login", json_str);
    profile.userId = result["auid"]; profile.sid = result["sid"];

    if (socket_enabladed){
        ws.connect();
    }

    return result;
}





json Client::logout() {

    json data = {
        {"clientType", 100},
        {"deviceID", profile.deviceId},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/logout", json_str);
    profile.userId = ""; profile.sid = "";
    if (socket_enabladed){
        ws.disconnect();
    }

    return result;
}


json Client::delete_account(std::string password) {

    json data = {
        {"secret", "0 " + password},
        {"deviceID", profile.deviceId},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/account/delete-request", json_str);

    return result;
}


json Client::restore_account(std::string email, std::string password) {

    json data = {
        {"email", email},
        {"secret", "0 " + password},
        {"deviceID", profile.deviceId},
    };

    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/account/delete-request/cancel", json_str);

    return result;
}


json Client::get_user_info(std::string userId) {

    json result = requester.sendRequest(Requester::GET, "/g/s/user-profile/"+userId);
    return result;
}


json Client::get_from_link(std::string link) {

    json result = requester.sendRequest(Requester::GET, "/g/s/link-resolution?q="+link);
    return result;
}


json Client::get_my_communities(int start, int size){
    json result = requester.sendRequest(Requester::GET, "/g/s/community/joined?v=1&start="+std::to_string(start)+"&size="+std::to_string(size));
    return result;
}
