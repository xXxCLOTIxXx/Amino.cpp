#include "Client.h"
#include <algorithm>


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
/*
json Client::register_account(std::string nickname, std::string email, std::string password, std::string verificationCode) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}
*/

json Client::configure(int age, int gender) {
    if (std::find(Gender::all.begin(), Gender::all.end(), gender) == Gender::all.end()){
        throw ArgumentError("Invalid gender value");
    }
    json data = {
        {"age", age},
        {"gender",  gender},
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/persona/profile/basic", json_str);
    return result;
}

json Client::verify(std::string email, std::string code) {
    json data = {
			"validationContext", {
				"type", 1,
				"identity", email,
				"data", {"code", code}},
			"deviceID", profile.deviceId,
    };

    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/check-security-validation", json_str);
    return result;
}

json Client::request_verify_code(std::string email, bool resetPassword) {
    json data = {
            "type", 1,
            "identity", email,
			"deviceID", profile.deviceId,
    };
    if (resetPassword == true){
        data["level"] = 2;
        data["purpose"] = "reset-password";
    }

    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/request-security-validation", json_str);
    return result;
}

json Client::activate_account(std::string email, std::string code) {
    json data = {
            "type", 1,
            "identity", email,
            "data", {"code", code},
			"deviceID", profile.deviceId,
    };

    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/activate-email", json_str);
    return result;
}

json Client::change_password(std::string email, std::string password, std::string code) {
    json data = {
        {"updateSecret", "0 " + password},
        {"emailValidationContext", {
            {"data", {
                {"code", code}
            }},
            {"type", 1},
            {"identity", email},
            {"level", 2},
            {"deviceID", profile.deviceId}
        }},
        {"phoneNumberValidationContext", nullptr},
        {"deviceID", profile.deviceId},
    };

    std::string json_str = data.dump();
    json result = requester.sendRequest(Requester::POST, "/g/s/auth/reset-password", json_str);
    return result;
}

json Client::get_account_info() {
    json result = requester.sendRequest(Requester::GET, "/g/s/account");
    return result;
}

json Client::get_eventlog() {
    json result = requester.sendRequest(Requester::GET, "/g/s/eventlog/profile?language="+profile.language);
    return result;
}

json Client::get_my_communities(int start, int size){
    json result = requester.sendRequest(Requester::GET, "/g/s/community/joined?v=1&start="+std::to_string(start)+"&size="+std::to_string(size));
    return result["communityList"];
}

json Client::get_my_profiles(int start, int size) {
    json result = requester.sendRequest(Requester::GET, "/g/s/community/joined?v=1&start="+std::to_string(start)+"&size="+std::to_string(size));
    return result["userInfoInCommunities"];
}

json Client::get_user_info(std::string userId) {
    json result = requester.sendRequest(Requester::GET, "/g/s/user-profile/"+userId);
    return result["userProfile"];
}

json Client::get_my_chats(int start, int size) {
    json result = requester.sendRequest(Requester::GET, "/g/s/chat/thread?type=joined-me&start="+std::to_string(start)+"&size="+std::to_string(size));
    return result["threadList"];
}

json Client::get_chat_info(std::string chatId) {
    json result = requester.sendRequest(Requester::GET, "/g/s/chat/thread/"+chatId);
    return result["thread"];
}

json Client::get_chat_users(std::string chatId, int start, int size) {
    json result = requester.sendRequest(Requester::GET, "/g/s/chat/thread/{chatId}/member?cv=1.2&type=default&start="+std::to_string(start)+"&size="+std::to_string(size));
    return result["memberList"];
}







json Client::join_chat(std::string chatId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::leave_chat(std::string chatId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::start_chat(std::string userId, std::string message, std::string title, std::string content, bool isGlobal, bool publishToGlobal) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::invite_to_chat(std::string userId, std::string chatId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::kick(std::string userId, std::string chatId, bool allowRejoin) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::get_chat_messages(std::string chatId, int size, std::string pageToken) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_message_info(std::string chatId, std::string messageId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_community_info(int comId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::search_community(std::string aminoId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_user_following(std::string userId, int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_user_followers(std::string userId, int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_blocked_users(int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_blog_info(std::string blogId, std::string wikiId, std::string quizId, std::string fileId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_blog_comments(std::string blogId, std::string wikiId, std::string quizId, std::string fileId, std::string sorting, int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_blocker_users(int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_wall_comments(std::string userId, std::string sorting, int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::flag(std::string reason, int flagType, std::string userId, std::string blogId, std::string wikiId, bool asGuest) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::send_message(std::string chatId, std::string message, int messageType) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::delete_message(std::string chatId, std::string messageId, bool asStaff, std::string reason) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::mark_as_read(std::string chatId, std::string messageId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::edit_chat(std::string chatId, bool doNotDisturb, bool pinChat, std::string title, std::string icon, std::string backgroundImage, std::string content, std::string announcement, std::vector<std::string> coHosts, std::vector<std::string> keywords, bool pinAnnouncement, bool publishToGlobal, bool canTip, bool viewOnly, bool canInvite, bool fansOnly) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::send_coins(int coins, std::string blogId, std::string chatId, std::string objectId, std::string transactionId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::follow(std::string userId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::unfollow(std::string userId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::block(std::string userId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::unblock(std::string userId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::join_community(int comId, std::string invitationId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::request_join_community(int comId, std::string message) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::leave_community(int comId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::flag_community(int comId, std::string reason, int flagType, bool isGuest) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::edit_profile(std::string nickname, std::string content, std::string icon, std::string backgroundColor, std::string backgroundImage, std::string defaultBubbleId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::set_amino_id(std::string aminoId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::get_linked_communities(std::string userId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_unlinked_communities(std::string userId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::reorder_linked_communities(std::vector<int> comIds) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::add_linked_community(int comId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::remove_linked_community(int comId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::comment(std::string message, std::string userId, std::string blogId, std::string wikiId, std::string replyTo) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::delete_comment(std::string commentId, std::string userId, std::string blogId, std::string wikiId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::like_blog(std::string blogId, std::string wikiId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::unlike_blog(std::string blogId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::like_comment(std::string commentId, std::string userId, std::string blogId, std::string wikiId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::unlike_comment(std::string commentId, std::string userId, std::string blogId, std::string wikiId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::get_membership_info() {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_ta_announcements(std::string language, int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_wallet_info() {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_wallet_history(int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_from_deviceid(std::string deviceId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_from_id(std::string objectId, int objectType, int comId) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_from_link(std::string link) {
    json result = requester.sendRequest(Requester::GET, "/g/s/link-resolution?q="+link);
    return result;
}

json Client::get_supported_languages() {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::claim_new_user_coupon() {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::get_subscriptions(int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_all_users(int start, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::accept_host(std::string chatId, std::string requestId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::accept_organizer(std::string chatId, std::string requestId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::link_identify(std::string code) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::invite_to_vc(std::string chatId, std::string userId) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::wallet_config(int level) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::purchase(std::string objectId, bool isAutoRenew) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

json Client::get_public_communities(std::string language, int size) {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::get_blockers() {
    json result = requester.sendRequest(Requester::GET, "");
    return result;
}

json Client::set_privacy_status(bool isAnonymous, bool getNotifications) {
    json result = requester.sendRequest(Requester::POST, "");
    return result;
}

