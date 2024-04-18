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
    json delete_community(std::string email, std::string password, std::string verificationCode);
    json list_communities(int start = 0, int size = 25);
    json get_blog_categories(int start = 0, int size = 25);
    json change_sidepanel_color(std::string color);

    //Community
    json get_all_users(std::string type = "recent", int start = 0, int size = 25);
};


#endif