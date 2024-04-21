#include <string>
#include "json.hpp"

#include "FanClubList.h"
#include "MediaObject.h"

using json = nlohmann::json;

class UserProfile {
public:
        json jsonData;

        FanClubList fanClub; //FanClubList(data.get("fanClubList", [])).FanClubList

        int accountMembershipStatus;
        int activation;
        std::string activePublicLiveThreadId;
        int age;
        std::string aminoId;
        bool aminoIdEditable;
        std::string avatarFrame;
        std::string avatarFrameId;
        int blogsCount;
        int commentsCount;
        std::string content;
        int createdTime;
        int followersCount;
        int followingCount;
        int followingStatus;
        std::string gender;
        std::string icon;
        bool isGlobal;
        bool isNicknameVerified;
        int itemsCount;
        int level;
        MediaObject mediaList;
        int membershipStatus;
        int modifiedTime;
        std::string mood;
        std::string moodSticker;
        std::string nickname;
        int notificationSubscriptionStatus;
        int onlineStatus;
        int onlineStatus2;
        int postsCount;
        bool pushEnabled;
        std::string race;
        int reputation;
        std::string role;
        int securityLevel;
        std::string status;
        int storiesCount;
        std::vector<std::string> tagList;
        std::string userId;
        bool verified;
        int totalQuizHighestScore;
        int totalQuizPlayedTimes;
        std::string requestId;
        std::string message;
        std::string applicant;
        int avgDailySpendTimeIn7Days;
        int adminLogCountIn7Days;

        // extensions
        std::map<std::string, std::string> extensions;
        // style
        std::map<std::string, std::string> style;
        std::string backgroundImage;
        std::string backgroundColor;

        std::string coverAnimation;
        std::vector<std::string> customTitles;
        std::string defaultBubbleId;
        int disabledLevel;
        std::string disabledStatus;
        int disabledTime;
        bool isMemberOfTeamAmino;
        bool privilegeOfChatInviteRequest;
        bool privilegeOfCommentOnUserProfile;

        // influencerInfo
        std::map<std::string, std::string> influencerInfo;
        int fansCount;
        int influencerCreatedTime;
        int influencerMonthlyFee;
        bool influencerPinned;

        // adminInfo
        std::map<std::string, std::string> staffInfo;
        int globalStrikeCount;
        int lastStrikeTime;
        int lastWarningTime;
        int strikeCount;
        int warningCount;




    UserProfile(json data); 
};
