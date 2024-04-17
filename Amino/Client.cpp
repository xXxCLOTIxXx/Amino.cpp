#include "Client.h"

#include <iostream>

Client::Client(const std::string& deviceId, const std::string& user_agent, const std::string& language): requester(&profile) {
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
    json result = requester.sendRequest("POST", "/g/s/auth/login", json_str);
    profile.userId = result["auid"]; profile.sid = result["sid"];

    return result;
}


json Client::login_sid(std::string sid) {
    /**
     * @brief Sid login
     * Login to your account using an authorization token. (todo)
     * 
     * @param sid - yourn auth token
     * @return json object.
     */
    
    json data;

    return data;
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
    json result = requester.sendRequest("POST", "/g/s/auth/login", json_str);
    profile.userId = result["auid"]; profile.sid = result["sid"];

    return result;

    return data;
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
    json result = requester.sendRequest("POST", "/g/s/auth/logout", json_str);
    profile.userId = ""; profile.sid = "";

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
    json result = requester.sendRequest("POST", "/g/s/account/delete-request", json_str);

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
    json result = requester.sendRequest("POST", "/g/s/account/delete-request/cancel", json_str);

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

    json result = requester.sendRequest("GET", "/g/s/user-profile/"+userId);
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

    json result = requester.sendRequest("GET", "/g/s/link-resolution?q="+link);
    return result;
}