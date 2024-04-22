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

    SubClient(req_data& _profile, const int _comId);



    // Community
    json get_all_users(std::string type = "recent", int start = 0, int size = 25);
    json get_invite_codes(std::string status = "normal", int start = 0, int size = 25);
    json generate_invite_code(int duration = 0, bool force = true);
    json delete_invite_code(std::string inviteId);
    json post_blog(std::string title, std::string content, std::vector<std::string> imageList = {}, std::vector<std::string> captionList = {}, std::vector<std::string> categoriesList = {}, std::string backgroundColor = "", bool fansOnly = false, json extensions = {});
    json post_wiki(std::string title, std::string content, std::string icon = "", std::vector<std::string> imageList = {}, std::string keywords = "", std::string backgroundColor = "", std::vector<std::string> props = {}, std::vector<std::string> backgroundMediaList = {});
    json edit_blog(std::string blogId, std::string title = "", std::string content = "", std::vector<std::string> imageList = {}, std::vector<std::string> categoriesList = {}, std::string backgroundColor = "", bool fansOnly = false);
    json delete_blog(std::string blogId);
    json delete_wiki(std::string wikiId);
    json repost_blog(std::string content = "", std::string blogId = "", std::string wikiId = "");
    json check_in(int tz = 0);
    json repair_check_in(int method = 0);
    json lottery(int tz = 0);
    json edit_profile(std::string nickname = "", std::string content = "", std::string chatRequestPrivilege = "", std::vector<std::string> imageList = {}, std::vector<std::string> captionList = {}, std::string backgroundImage = "", std::string backgroundColor = "", std::vector<std::string> titles = {}, std::vector<std::string> colors = {}, std::string defaultBubbleId = "");
    json vote_poll(std::string blogId, std::string optionId);
    json comment(std::string message, std::string userId = "", std::string blogId = "", std::string wikiId = "", std::string replyTo = "", bool isGuest = false);
    json delete_comment(std::string commentId, std::string userId = "", std::string blogId = "", std::string wikiId = "");
    json like_blog(std::string blogId = "", std::string wikiId = "");
    json unlike_blog(std::string blogId = "", std::string wikiId = "");
    json like_comment(std::string commentId, std::string userId = "", std::string blogId = "", std::string wikiId = "");
    json unlike_comment(std::string commentId, std::string userId = "", std::string blogId = "", std::string wikiId = "");
    json upvote_comment(std::string blogId, std::string commentId);
    json downvote_comment(std::string blogId, std::string commentId);
    json unvote_comment(std::string blogId, std::string commentId);
    json reply_wall(std::string userId, std::string commentId, std::string message);
    json send_active_obj(int startTime = 0, int endTime = 0, int tz = 0, std::vector<int> timers = {});
    json activity_status(std::string status);
    json check_notifications();
    json delete_notification(std::string notificationId);
    json clear_notifications();
    json start_chat(std::string userId, std::string message, std::string title = "", std::string content = "", bool isGlobal = false, bool publishToGlobal = false);
    json invite_to_chat(std::string userId, std::string chatId);
    json add_to_favorites(std::string userId);
    json send_coins(int coins, std::string blogId = "", std::string chatId = "", std::string objectId = "", std::string transactionId = "");
    json thank_tip(std::string chatId, std::string userId);
    json follow(std::string userId);
    json unfollow(std::string userId);
    json block(std::string userId);
    json unblock(std::string userId);
    json flag(std::string reason, int flagType, std::string userId = "", std::string blogId = "", std::string wikiId = "", bool asGuest = false);
    json send_message(std::string chatId, std::string message = "", int messageType = 0, std::istream* file = nullptr, std::string fileType = "", std::string replyTo = "", std::vector<std::string> mentionUserIds = {}, std::string stickerId = "", std::string embedId = "", int embedType = 0, std::string embedLink = "", std::string embedTitle = "", std::string embedContent = "", std::istream* embedImage = nullptr);
    json full_embed(std::string link, std::istream* image, std::string message, std::string chatId);
    json delete_message(std::string chatId, std::string messageId, bool asStaff = false, std::string reason = "");
    json mark_as_read(std::string chatId, std::string messageId);
    json edit_chat(std::string chatId, bool doNotDisturb = false, bool pinChat = false, std::string title = "", std::string icon = "", std::string backgroundImage = "", std::string content = "", std::string announcement = "", std::vector<std::string> coHosts = {}, std::vector<std::string> keywords = {}, bool pinAnnouncement = false, bool publishToGlobal = false, bool canTip = false, bool viewOnly = false, bool canInvite = false, bool fansOnly = false);
    json transfer_host(std::string chatId, std::vector<std::string> userIds);
    json accept_host(std::string chatId, std::string requestId);
    json kick(std::string userId, std::string chatId, bool allowRejoin = true);
    json join_chat(std::string chatId);
    json leave_chat(std::string chatId);
    json delete_chat(std::string chatId);
    json subscribe(std::string userId, bool autoRenew = false, std::string transactionId = "");
    json promotion(std::string noticeId, std::string type = "accept");
    json play_quiz_raw(std::string quizId, std::vector<std::string> quizAnswerList, int quizMode = 0);
    json play_quiz(std::string quizId, std::vector<std::string> questionIdsList, std::vector<std::string> answerIdsList, int quizMode = 0);
    json vc_permission(std::string chatId, int permission);
    json get_vc_reputation_info(std::string chatId);
    json claim_vc_reputation(std::string chatId);
    json get_online_users(int start = 0, int size = 25);
    json get_user_info(std::string userId);
    json get_user_following(std::string userId, int start = 0, int size = 25);
    json get_user_followers(std::string userId, int start = 0, int size = 25);
    json get_user_checkins(std::string userId);
    json get_user_blogs(std::string userId, int start = 0, int size = 25);
    json get_user_wikis(std::string userId, int start = 0, int size = 25);
    json get_user_achievements(std::string userId);
    json get_influencer_fans(std::string userId, int start = 0, int size = 25);
    json get_blocked_users(int start = 0, int size = 25);
    json get_blocker_users(int start = 0, int size = 25);
    json search_users(std::string nickname, int start = 0, int size = 25);
    json get_saved_blogs(int start = 0, int size = 25);
    json get_leaderboard_info(std::string type, int start = 0, int size = 25);
    json get_wiki_info(std::string wikiId);
    json get_recent_wiki_items(int start = 0, int size = 25);
    json get_wiki_categories(int start = 0, int size = 25);
    json get_wiki_category(std::string categoryId, int start = 0, int size = 25);
    json get_tipped_users(std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "", std::string chatId = "", int start = 0, int size = 25);
    json get_chat_threads(int start = 0, int size = 25);
    json get_public_chat_threads(std::string type = "recommended", int start = 0, int size = 25);
    json get_chat_thread(std::string chatId);
    json get_chat_messages(std::string chatId, int size = 25, std::string pageToken = "");
    json get_message_info(std::string chatId, std::string messageId);
    json get_blog_info(std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "");
    json get_blog_comments(std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "", std::string sorting = "newest", int start = 0, int size = 25);
    json get_blog_categories(int size = 25);
    json get_blogs_by_category(std::string categoryId, int start = 0, int size = 25);
    json get_quiz_rankings(std::string quizId, int start = 0, int size = 25);
    json get_wall_comments(std::string userId, std::string sorting, int start = 0, int size = 25);
    json get_recent_blogs(std::string pageToken = "", int start = 0, int size = 25);
    json get_chat_users(std::string chatId, int start = 0, int size = 25);
    json get_notifications(int start = 0, int size = 25);
    json get_notices(int start = 0, int size = 25);
    json get_sticker_pack_info(std::string sticker_pack_id);
    json get_sticker_packs();
    json get_store_chat_bubbles(int start = 0, int size = 25);
    json get_store_stickers(int start = 0, int size = 25);
    json get_community_stickers();
    json get_sticker_collection(std::string collectionId);
    json get_shared_folder_info();
    json get_shared_folder_files(std::string type = "latest", int start = 0, int size = 25);



    //MODERATION MENU

    json moderation_history(std::string userId = "", std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "", int size = 25);
    json feature(int time, std::string userId = "", std::string chatId = "", std::string blogId = "", std::string wikiId = "");
    json unfeature(std::string userId = "", std::string chatId = "", std::string blogId = "", std::string wikiId = "");
    json hide(std::string userId = "", std::string chatId = "", std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "", std::string reason = "");
    json unhide(std::string userId = "", std::string chatId = "", std::string blogId = "", std::string wikiId = "", std::string quizId = "", std::string fileId = "", std::string reason = "");
    json edit_titles(std::string userId, std::vector<std::string> tlt);
    json warn(std::string userId, std::string reason = "");
    json strike(std::string userId, int time, std::string title = "", std::string reason = "");
    json ban(std::string userId, std::string reason, int banType = 0);
    json unban(std::string userId, std::string reason);
    json reorder_featured_users(std::vector<std::string> userIds);
    json get_hidden_blogs(int start = 0, int size = 25);
    json get_featured_users(int start = 0, int size = 25);
    json review_quiz_questions(std::string quizId);
    json get_recent_quiz(int start = 0, int size = 25);
    json get_trending_quiz(int start = 0, int size = 25);
    json get_best_quiz(int start = 0, int size = 25);
    json purchase(std::string objectId, int objectType, bool aminoPlus = true, bool autoRenew = false);
    json apply_avatar_frame(std::string avatarId, bool applyToAll = true);
    json invite_to_vc(std::string chatId, std::string userId);
    json add_poll_option(std::string blogId, std::string question);
    json create_wiki_category(std::string title, std::string backgroundColor, std::string icon);
    json rename_wiki_category(std::string categoryId, std::string title, std::string backgroundColor, std::string icon);
    json reorder_wiki_categories(std::vector<std::string> categoryIds);
    json get_community_wiki_list(std::string categoryId = "", std::string searchKeyword = "", int start = 0, int size = 25);
    json get_user_wiki_list(std::string categoryId = "", std::string searchKeyword = "", int start = 0, int size = 25);
    json get_user_wiki_edits(std::string wikiId, int start = 0, int size = 25);
    json delete_wiki_category(std::string categoryId);
    json pin_blog(std::string blogId, std::string wikiId);
    json unpin_blog(std::string blogId, std::string wikiId);
    json enable_replies(std::string blogId, std::string wikiId);
    json disable_replies(std::string blogId, std::string wikiId);
    json get_app_version();
    json get_metadata();
    json get_ads(std::string category, std::string tag, int count = 5);
    json get_content_info(std::string objectId, int objectType);
    json get_file_info(std::string fileId);
    json report_content(std::string objectId, int objectType, std::string reason);
    json get_flag_reasons();
    json get_sticker_info(std::string stickerId);
    json set_wiki_privilege(std::string wikiId, std::string type, std::string roleId);
    json create_wiki_item(std::string title, std::string content, std::string categoryId, std::string keywords, std::string icon, std::string backgroundColor, std::vector<std::string> props, std::vector<std::string> backgroundMediaList);
    json edit_wiki_item(std::string wikiId, std::string title, std::string content, std::string icon, std::string backgroundColor, std::vector<std::string> props, std::vector<std::string> backgroundMediaList);
    json delete_wiki_item(std::string wikiId);
    json invite_to_vc_stage(std::string chatId, std::string userId);
    json mute(std::string chatId, std::string userId);
    json unmute(std::string chatId, std::string userId);
    json request_to_join_chat(std::string chatId, std::string title = "", std::string content = "");
    json accept_chat_join_request(std::string requestId);
    json reject_chat_join_request(std::string requestId);
    json get_chat_join_requests(std::string chatId, int start = 0, int size = 25);
    json get_user_messages(std::string chatId, std::string userId, int start = 0, int size = 25);
    json enable_user_mentions(std::string chatId);
    json disable_user_mentions(std::string chatId);
    json get_role_privileges(std::string chatId);
    json set_role_privileges(std::string chatId, std::string roleId, std::string privileges);
    json reset_role_privileges(std::string chatId, std::string roleId);
    json get_chat_voting_info(std::string chatId);
    json start_chat_voting(std::string chatId, std::string optionId);
    json end_chat_voting(std::string chatId);
    json cancel_chat_voting(std::string chatId);
    json get_chat_poll_info(std::string chatId);
    json start_chat_poll(std::string chatId, std::string optionId);
    json end_chat_poll(std::string chatId);
    json cancel_chat_poll(std::string chatId);
    json delete_chat_poll_option(std::string chatId, std::string optionId);
    json update_chat_poll_option(std::string chatId, std::string optionId, std::string newOptionText);
    json get_chat_poll_result(std::string chatId);
    json get_chat_game_info(std::string chatId);
    json start_chat_game(std::string chatId, std::string gameId);
    json end_chat_game(std::string chatId);
    json cancel_chat_game(std::string chatId);
    json get_chat_game_result(std::string chatId);





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


};


#endif