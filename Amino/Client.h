#ifndef CLIENT_H
#define CLIENT_H

#include "objects/exceptions.h"

#include "utils/requester.h"
#include "objects/req_data.h"
#include "Socket.h"
//#include "objects/ResponseObjects/UserProfile.h"


class Client {
public:
    req_data profile;
    Requester requester;
    Socket ws;
    bool socket_enabladed;

    Client(const std::string& deviceId = "", bool _run_socket = true, const std::string& user_agent = "Apple iPhone12,1 iOS v15.5 Main/3.12.2", const std::string& language = "en");

    json login(std::string email, std::string password = "", std::string secret = "");
    std::string login_sid(std::string sid);
    json login_phone(std::string number, std::string password);
    json logout();
    json delete_account(std::string password);
    json restore_account(std::string email, std::string password);

    json register_account(std::string nickname, std::string email, std::string password, std::string verificationCode);
    json configure(int age, std::string gender);
    json verify(std::string email, std::string code);
    json request_verify_code(std::string email, bool resetPassword = false);
    json activate_account(std::string email, std::string code);
    json change_password(std::string email, std::string password, std::string code);
    json get_account_info();
    json get_eventlog();
    json get_my_communities(int start = 0, int size = 25);
    json get_my_profiles(int start = 0, int size = 25);
    json get_user_info(std::string userId);
    json get_my_chats(int start = 0, int size = 25);
    json get_chat_info(std::string chatId);
    json get_chat_users(std::string chatId, int start = 0, int size = 25);
    json join_chat(std::string chatId);
    json leave_chat(std::string chatId);
    json start_chat(std::string userId, std::string message, std::string title = "", std::string content = "", bool isGlobal = false, bool publishToGlobal = false);
    json invite_to_chat(std::string userId, std::string chatId);
    json kick(std::string userId, std::string chatId, bool allowRejoin = true);
    json get_chat_messages(std::string chatId, int size = 25, std::string pageToken = "");
    json get_message_info(std::string chatId, std::string messageId);
    json get_community_info(int comId);
    json search_community(std::string aminoId);
    json get_user_following(std::string userId, int start = 0, int size = 25);
    json get_user_followers(std::string userId, int start = 0, int size = 25);
    json get_blocked_users(int start = 0, int size = 25);
    json get_blog_info(std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "");
    json get_blog_comments(std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "", std::string sorting = "newest", int start = 0, int size = 25);
    json get_blocker_users(int start = 0, int size = 25);
    json get_wall_comments(std::string userId, std::string sorting = "newest", int start = 0, int size = 25);
    json flag(std::string reason, int flagType, std::string userId = "", std::string blogId = "", std::string wikiId = "", bool asGuest = false);
    json send_message(std::string chatId, std::string message = "", int messageType = 0);
    json delete_message(std::string chatId, std::string messageId, bool asStaff = false, std::string reason = "");
    json mark_as_read(std::string chatId, std::string messageId);
    json edit_chat(std::string chatId, bool doNotDisturb = false, bool pinChat = false, std::string title = "", std::string icon = "", std::string backgroundImage = "", std::string content = "", std::string announcement = "", std::vector<std::string> coHosts = {}, std::vector<std::string> keywords = {}, bool pinAnnouncement = false, bool publishToGlobal = false, bool canTip = false, bool viewOnly = false, bool canInvite = false, bool fansOnly = false);
    json send_coins(int coins, std::string blogId = "", std::string chatId = "", std::string objectId = "", std::string transactionId = "");
    json follow(std::string userId);
    json unfollow(std::string userId);

    json block(std::string userId);
    json unblock(std::string userId);
    json join_community(int comId, std::string invitationId = "");
    json request_join_community(int comId, std::string message = "");
    json leave_community(int comId);
    json flag_community(int comId, std::string reason, int flagType, bool isGuest = false);
    json edit_profile(std::string nickname = "", std::string content = "", std::string icon = "", std::string backgroundColor = "", std::string backgroundImage = "", std::string defaultBubbleId = "");
    json set_amino_id(std::string aminoId);
    json get_linked_communities(std::string userId);
    json get_unlinked_communities(std::string userId);
    json reorder_linked_communities(std::vector<int> comIds);
    json add_linked_community(int comId);
    json remove_linked_community(int comId);
    json comment(std::string message, std::string userId = "", std::string blogId = "", std::string wikiId = "", std::string replyTo = "");
    json delete_comment(std::string commentId, std::string userId = "", std::string blogId = "", std::string wikiId = "");
    json like_blog(std::string blogId = "", std::string wikiId = "");
    json unlike_blog(std::string blogId);
    json like_comment(std::string commentId, std::string userId = "", std::string blogId = "", std::string wikiId = "");
    json unlike_comment(std::string commentId, std::string userId = "", std::string blogId = "", std::string wikiId = "");
    json get_membership_info();
    json get_ta_announcements(std::string language = "en", int start = 0, int size = 25);
    json get_wallet_info();
    json get_wallet_history(int start = 0, int size = 25);
    json get_from_deviceid(std::string deviceId);
    json get_from_id(std::string objectId, int objectType, int comId = 0);
    json get_from_link(std::string link);
    json get_supported_languages();
    json claim_new_user_coupon();
    json get_subscriptions(int start = 0, int size = 25);
    json get_all_users(int start = 0, int size = 25);
    json accept_host(std::string chatId, std::string requestId);
    json accept_organizer(std::string chatId, std::string requestId);
    json link_identify(std::string code);
    json invite_to_vc(std::string chatId, std::string userId);
    json wallet_config(int level);
    json purchase(std::string objectId, bool isAutoRenew = false);
    json get_public_communities(std::string language = "en", int size = 25);
    json get_blockers();





    void wait();

};


#endif