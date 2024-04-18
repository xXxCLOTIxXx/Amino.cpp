#include "SubClient.h"
#include <iostream>

SubClient::SubClient(req_data& _profile_data, const std::string _comId) : profile(&_profile_data), comId(_comId), requester(&_profile_data) {
}

json SubClient::delete_community(std::string email, std::string password, std::string verificationCode){
    json data = {
        {"secret", "0 " + password},
        {"deviceID", profile->deviceId},
        {"validationContext", {
            {"type", 1},
            {"identity", email},
            {"data", {
                {"code", verificationCode}
            }}
        }}
    };
    std::string json_str = data.dump();
    json result = requester.sendRequest("POST", "/g/s-x"+comId+"/community/delete-request", json_str);
    return result;
}
json SubClient::list_communities(int start, int size){
    json result = requester.sendRequest("GET", "");
    return result;
}
json SubClient::get_blog_categories(int start, int size){
    json result = requester.sendRequest("GET", "");
    return result;
}
json SubClient::change_sidepanel_color(std::string color){
    json result = requester.sendRequest("POST", "");
    return result;
}




json SubClient::get_all_users(std::string type, int start, int size){
    type = Helpers::lower(type);
    std::vector<std::string> validTypes = {"recent", "banned", "featured", "leaders", "curators"};
    if (Helpers::checkType(type, validTypes)){
        throw ArgumentError("Invalid member type ["+type+"]");
    }
    json result = requester.sendRequest("GET", "/x"+comId+"/s/user-profile?type="+type+"&start="+std::to_string(start)+"&size="+std::to_string(size));
    return result;
}
