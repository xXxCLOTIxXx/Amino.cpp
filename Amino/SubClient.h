#ifndef SUBCLIENT_H
#define SUBCLIENT_H

#include "objects/exceptions.h"
#include "utils/requester.h"
#include "objects/req_data.h"

class SubClient {
public:
    req_data* profile;
    Requester requester;
    const std::string comId;

    SubClient(req_data& _profile, const std::string _comId);

    //ACM

    json create_community(std::string name, std::string tagline, std::istream& icon, std::string themeColor, int joinType = 0, std::string primaryLanguage = "en");
    json delete_community(std::string email, std::string password, std::string verificationCode);
    json list_communities(int start = 0, int size = 25);
    json get_blog_categories(int start = 0, int size = 25);
    json change_sidepanel_color(std::string color);
    json promote(std::string userId, std::string rank);
    json get_join_requests(int start = 0, int size = 25);
    json accept_join_request(std::string userId);
    json reject_join_request(std::string userId);
    json get_community_stats();
    json get_community_user_stats(std::string type, int start = 0, int size = 25);
    json change_welcome_message(std::string message, bool isEnabled = true);
    json change_guidelines(std::string message);
    json edit_community(std::string name = "", std::string description = "", std::string aminoId = "", std::string primaryLanguage = "", std::string themePackUrl = "");
    json change_module(std::string module, bool isEnabled);
    json add_influencer(std::string userId, int monthlyFee);
    json remove_influencer(std::string userId);
    json get_notice_list(int start = 0, int size = 25);
    json delete_pending_role(std::string noticeId);

    // Community
    json get_all_users(std::string type = "recent", int start = 0, int size = 25);

};


#endif