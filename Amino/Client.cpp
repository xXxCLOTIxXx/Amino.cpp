#include "Client.h"

#include <iostream>

Client::Client(const std::string& deviceId, bool _run_socket, const std::string& user_agent, const std::string& language): requester(&profile), socket_enabladed(_run_socket), ws_socket(&profile) {
    profile.language = language;
    profile.user_agent = user_agent;
    if (deviceId.empty()) {
        profile.deviceId = Helpers::genDeviceId();
    } else {
        profile.deviceId = deviceId;
        
    }
}

json Client::login(std::string email, std::string password, std::string secret) {
    /**
     * @brief Email login
     * Sends an authorization request.
     * 
     * @param email - your account email address
     * @param password - your account password
     * @param secret - password for your account (optional)
     * @return json object.
     */
    
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
        ws_socket.connect();
    }

    return result;
}


std::string Client::login_sid(std::string sid) {
    /**
     * @brief Sid login
     * Login to your account using an authorization token. (todo)
     * 
     * @param sid - yourn auth token
     * @return json object.
     */
    
    std::string uid = Helpers::sid_to_uid(sid);
    profile.userId = uid; profile.sid = sid;

    if (socket_enabladed){
        ws_socket.connect();
    }
    return uid;
}

json Client::login_phone(std::string number, std::string password) {
    /**
     * @brief Phone login
     * Login to your account using your phone number
     * 
     * @param number - yourn phone number
     * @param password - yourn account password
     * @return json object.
     */
    
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
        ws_socket.connect();
    }

    return result;
}





json Client::logout() {
    /**
     * @brief Account logout
     * Will send a request to log out of your account.
     *
     * @return json object.
     */

    json data = {
        {"clientType", 100},
        {"deviceID", profile.deviceId},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/logout", json_str);
    profile.userId = ""; profile.sid = "";
    if (socket_enabladed){
        ws_socket.disconnect();
    }

    return result;
}


json Client::delete_account(std::string password) {
    /**
     * @brief Delete account
     * Send a request to delete your account (you need to log in client.login)
     * 
     * @param password - your account password
     * @return json object.
     */

    json data = {
        {"secret", "0 " + password},
        {"deviceID", profile.deviceId},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/account/delete-request", json_str);

    return result;
}


json Client::restore_account(std::string email, std::string password) {
    /**
     * @brief Restore account
     * Recover a deleted account.
     * 
     * @param email - your account email address
     * @param password - your account password
     * @return json object.
     */

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
    /**
     * @brief Get user info
     * Get user profile information.
     * 
     * @param userId - target user id
     * @return json object.
     */

    json result = requester.sendRequest(Requester::GET, "/g/s/user-profile/"+userId);
    return result;
}


json Client::get_from_link(std::string link) {
    /**
     * @brief Get link info
     * Sends a request for information about the link.
     * 
     * @param link - your link
     * @return json object.
     */

    json result = requester.sendRequest(Requester::GET, "/g/s/link-resolution?q="+link);
    return result;
}


void Client::wait(){
    if (!socket_enabladed){return;}
    while (ws_socket.m_isConnected == true){
        //nothing :)
    }
}