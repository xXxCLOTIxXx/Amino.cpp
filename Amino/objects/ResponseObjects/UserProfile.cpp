#include "UserProfile.h"

UserProfile::UserProfile(json data) : jsonData(data), fanClub(data.value("fanClubList", std::vector<json>())), mediaList(data.value("fanClubList", "")){


    // Присваиваем значения переменным через метод value
    int accountMembershipStatus = jsonData.value("accountMembershipStatus", 0);
    int activation = jsonData.value("activation", 0);
    std::string activePublicLiveThreadId = jsonData.value("activePublicLiveThreadId", "");
    int age = jsonData.value("age", 0);
    std::string aminoId = jsonData.value("aminoId", "");
    bool aminoIdEditable = jsonData.value("aminoIdEditable", false);
    std::string avatarFrame = jsonData.value("avatarFrame", "");
    std::string avatarFrameId = jsonData.value("avatarFrameId", "");
    int blogsCount = jsonData.value("blogsCount", 0);
    int commentsCount = jsonData.value("commentsCount", 0);
    std::string content = jsonData.value("content", "");
    int createdTime = jsonData.value("createdTime", 0);
    int followersCount = jsonData.value("followersCount", 0);
    int followingCount = jsonData.value("followingCount", 0);
    int followingStatus = jsonData.value("followingStatus", 0);
    std::string gender = jsonData.value("gender", "");
    std::string icon = jsonData.value("icon", "");
    bool isGlobal = jsonData.value("isGlobal", false);
    bool isNicknameVerified = jsonData.value("isNicknameVerified", false);
    int itemsCount = jsonData.value("itemsCount", 0);
    int level = jsonData.value("level", 0);
    int membershipStatus = jsonData.value("membershipStatus", 0);
    int modifiedTime = jsonData.value("modifiedTime", 0);
    std::string mood = jsonData.value("mood", "");
    std::string moodSticker = jsonData.value("moodSticker", "");
    std::string nickname = jsonData.value("nickname", "");
    int notificationSubscriptionStatus = jsonData.value("notificationSubscriptionStatus", 0);
    int onlineStatus = jsonData.value("onlineStatus", 0);
    int onlineStatus2 = jsonData.value("onlineStatus2", 0);
    int postsCount = jsonData.value("postsCount", 0);
    bool pushEnabled = jsonData.value("pushEnabled", false);
    std::string race = jsonData.value("race", "");
    int reputation = jsonData.value("reputation", 0);
    std::string role = jsonData.value("role", "");
    int securityLevel = jsonData.value("securityLevel", 0);
    std::string status = jsonData.value("status", "");
    int storiesCount = jsonData.value("storiesCount", 0);
    std::vector<std::string> tagList = jsonData.value("tagList", std::vector<std::string>());
    std::string userId = jsonData.value("userId", "");
    bool verified = jsonData.value("verified", false);
    int totalQuizHighestScore = jsonData.value("totalQuizHighestScore", 0);
    int totalQuizPlayedTimes = jsonData.value("totalQuizPlayedTimes", 0);
    std::string requestId = jsonData.value("requestId", "");
    std::string message = jsonData.value("message", "");
    std::string applicant = jsonData.value("applicant", "");
    int avgDailySpendTimeIn7Days = jsonData.value("avgDailySpendTimeIn7Days", 0);
    int adminLogCountIn7Days = jsonData.value("adminLogCountIn7Days", 0);

    // extensions
    std::map<std::string, std::string> extensions = jsonData.value("extensions", std::map<std::string, std::string>());


    // influencerInfo
    std::map<std::string, std::string> influencerInfo = jsonData.value("influencerInfo", std::map<std::string, std::string>());

    // adminInfo
    std::map<std::string, std::string> staffInfo = jsonData.value("adminInfo", std::map<std::string, std::string>());



}
