#ifndef CLIENT_H
#define CLIENT_H

#include "objects/exceptions.h"

#include "utils/requester.h"
#include "objects/req_data.h"
#include "Socket.h"
#include "EventHandler.h"


class Client  : public EventHandler {
public:
    req_data profile;
    Requester requester;
    Socket ws_socket;
    bool socket_enabladed;

    Client(const std::string& deviceId = "", bool _run_socket = true, const std::string& user_agent = "Apple iPhone12,1 iOS v15.5 Main/3.12.2", const std::string& language = "en");

    json login(std::string email, std::string password = "", std::string secret = "");
    json login_sid(std::string sid);
    json login_phone(std::string number, std::string password);
    json logout();
    json delete_account(std::string password);
    json restore_account(std::string email, std::string password);

    json get_user_info(std::string userId);
    json get_from_link(std::string link);
    void wait();

};


#endif