#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <string>
#include <stdexcept>


class InvalidRequestType : public std::runtime_error {
public:
    InvalidRequestType(const std::string& message) : std::runtime_error(message) {}
};

class ArgumentError : public std::runtime_error {
public:
    ArgumentError(const std::string& message) : std::runtime_error(message) {}
};

class JsonDecodeError : public std::runtime_error {
public:
    JsonDecodeError(const std::string& message) : std::runtime_error(message) {}
};






class UnsupportedService : public std::runtime_error {
public:
    UnsupportedService(const std::string& message) : std::runtime_error(message) {}
};

class FileTooLarge : public std::runtime_error {
public:
    FileTooLarge(const std::string& message) : std::runtime_error(message) {}
};

class InvalidRequest : public std::runtime_error {
public:
    InvalidRequest(const std::string& message) : std::runtime_error(message) {}
};

class InvalidSession : public std::runtime_error {
public:
    InvalidSession(const std::string& message) : std::runtime_error(message) {}
};

class AccessDenied : public std::runtime_error {
public:
    AccessDenied(const std::string& message) : std::runtime_error(message) {}
};

class UnexistentData : public std::runtime_error {
public:
    UnexistentData(const std::string& message) : std::runtime_error(message) {}
};

class ActionNotAllowed : public std::runtime_error {
public:
    ActionNotAllowed(const std::string& message) : std::runtime_error(message) {}
};

class ServiceUnderMaintenance : public std::runtime_error {
public:
    ServiceUnderMaintenance(const std::string& message) : std::runtime_error(message) {}
};

class MessageNeeded : public std::runtime_error {
public:
    MessageNeeded(const std::string& message) : std::runtime_error(message) {}
};

class InvalidAccountOrPassword : public std::runtime_error {
public:
    InvalidAccountOrPassword(const std::string& message) : std::runtime_error(message) {}
};

class AccountDisabled : public std::runtime_error {
public:
    AccountDisabled(const std::string& message) : std::runtime_error(message) {}
};

class InvalidEmail : public std::runtime_error {
public:
    InvalidEmail(const std::string& message) : std::runtime_error(message) {}
};

class InvalidPassword : public std::runtime_error {
public:
    InvalidPassword(const std::string& message) : std::runtime_error(message) {}
};

class EmailAlreadyTaken : public std::runtime_error {
public:
    EmailAlreadyTaken(const std::string& message) : std::runtime_error(message) {}
};

class UnsupportedEmail : public std::runtime_error {
public:
    UnsupportedEmail(const std::string& message) : std::runtime_error(message) {}
};

class AccountDoesntExist : public std::runtime_error {
public:
    AccountDoesntExist(const std::string& message) : std::runtime_error(message) {}
};

class InvalidDevice : public std::runtime_error {
public:
    InvalidDevice(const std::string& message) : std::runtime_error(message) {}
};

class AccountLimitReached : public std::runtime_error {
public:
    AccountLimitReached(const std::string& message) : std::runtime_error(message) {}
};

class TooManyRequests : public std::runtime_error {
public:
    TooManyRequests(const std::string& message) : std::runtime_error(message) {}
};

class CantFollowYourself : public std::runtime_error {
public:
    CantFollowYourself(const std::string& message) : std::runtime_error(message) {}
};

class UserUnavailable : public std::runtime_error {
public:
    UserUnavailable(const std::string& message) : std::runtime_error(message) {}
};

class YouAreBanned : public std::runtime_error {
public:
    YouAreBanned(const std::string& message) : std::runtime_error(message) {}
};

class UserNotMemberOfCommunity : public std::runtime_error {
public:
    UserNotMemberOfCommunity(const std::string& message) : std::runtime_error(message) {}
};

class RequestRejected : public std::runtime_error {
public:
    RequestRejected(const std::string& message) : std::runtime_error(message) {}
};

class ActivateAccount : public std::runtime_error {
public:
    ActivateAccount(const std::string& message) : std::runtime_error(message) {}
};

class CantLeaveCommunity : public std::runtime_error {
public:
    CantLeaveCommunity(const std::string& message) : std::runtime_error(message) {}
};

class ReachedTitleLength : public std::runtime_error {
public:
    ReachedTitleLength(const std::string& message) : std::runtime_error(message) {}
};

class UserHasBeenDeleted : public std::runtime_error {
public:
    UserHasBeenDeleted(const std::string& message) : std::runtime_error(message) {}
};

class AccountDeleted : public std::runtime_error {
public:
    AccountDeleted(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_EMAIL_NO_PASSWORD : public std::runtime_error {
public:
    API_ERR_EMAIL_NO_PASSWORD(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_COMMUNITY_USER_CREATED_COMMUNITIES_VERIFY : public std::runtime_error {
public:
    API_ERR_COMMUNITY_USER_CREATED_COMMUNITIES_VERIFY(const std::string& message) : std::runtime_error(message) {}
};

class ReachedMaxTitles : public std::runtime_error {
public:
    ReachedMaxTitles(const std::string& message) : std::runtime_error(message) {}
};

class VerificationRequired : public std::runtime_error {
public:
    VerificationRequired(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_INVALID_AUTH_NEW_DEVICE_LINK : public std::runtime_error {
public:
    API_ERR_INVALID_AUTH_NEW_DEVICE_LINK(const std::string& message) : std::runtime_error(message) {}
};

class CommandCooldown : public std::runtime_error {
public:
    CommandCooldown(const std::string& message) : std::runtime_error(message) {}
};

class UserBannedByTeamAmino : public std::runtime_error {
public:
    UserBannedByTeamAmino(const std::string& message) : std::runtime_error(message) {}
};

class BadImage : public std::runtime_error {
public:
    BadImage(const std::string& message) : std::runtime_error(message) {}
};

class InvalidThemepack : public std::runtime_error {
public:
    InvalidThemepack(const std::string& message) : std::runtime_error(message) {}
};

class InvalidVoiceNote : public std::runtime_error {
public:
    InvalidVoiceNote(const std::string& message) : std::runtime_error(message) {}
};

class IpTemporaryBan : public std::runtime_error {
public:
    IpTemporaryBan(const std::string& message) : std::runtime_error(message) {}
};

class RequestedNoLongerExists : public std::runtime_error {
public:
    RequestedNoLongerExists(const std::string& message) : std::runtime_error(message) {}
};

class PageRepostedTooRecently : public std::runtime_error {
public:
    PageRepostedTooRecently(const std::string& message) : std::runtime_error(message) {}
};

class InsufficientLevel : public std::runtime_error {
public:
    InsufficientLevel(const std::string& message) : std::runtime_error(message) {}
};

class WallCommentingDisabled : public std::runtime_error {
public:
    WallCommentingDisabled(const std::string& message) : std::runtime_error(message) {}
};

class CommunityNoLongerExists : public std::runtime_error {
public:
    CommunityNoLongerExists(const std::string& message) : std::runtime_error(message) {}
};

class InvalidCodeOrLink : public std::runtime_error {
public:
    InvalidCodeOrLink(const std::string& message) : std::runtime_error(message) {}
};

class CommunityNameAlreadyTaken : public std::runtime_error {
public:
    CommunityNameAlreadyTaken(const std::string& message) : std::runtime_error(message) {}
};

class CommunityCreateLimitReached : public std::runtime_error {
public:
    CommunityCreateLimitReached(const std::string& message) : std::runtime_error(message) {}
};

class CommunityDisabled : public std::runtime_error {
public:
    CommunityDisabled(const std::string& message) : std::runtime_error(message) {}
};

class CommunityDeleted : public std::runtime_error {
public:
    CommunityDeleted(const std::string& message) : std::runtime_error(message) {}
};

class DuplicatePollOption : public std::runtime_error {
public:
    DuplicatePollOption(const std::string& message) : std::runtime_error(message) {}
};

class ReachedMaxPollOptions : public std::runtime_error {
public:
    ReachedMaxPollOptions(const std::string& message) : std::runtime_error(message) {}
};

class TooManyChats : public std::runtime_error {
public:
    TooManyChats(const std::string& message) : std::runtime_error(message) {}
};

class ChatFull : public std::runtime_error {
public:
    ChatFull(const std::string& message) : std::runtime_error(message) {}
};

class TooManyInviteUsers : public std::runtime_error {
public:
    TooManyInviteUsers(const std::string& message) : std::runtime_error(message) {}
};

class ChatInvitesDisabled : public std::runtime_error {
public:
    ChatInvitesDisabled(const std::string&message) : std::runtime_error(message) {}
};

class RemovedFromChat : public std::runtime_error {
public:
    RemovedFromChat(const std::string& message) : std::runtime_error(message) {}
};

class UserNotJoined : public std::runtime_error {
public:
    UserNotJoined(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_CHAT_VVCHAT_NO_MORE_REPUTATIONS : public std::runtime_error {
public:
    API_ERR_CHAT_VVCHAT_NO_MORE_REPUTATIONS(const std::string& message) : std::runtime_error(message) {}
};

class MemberKickedByOrganizer : public std::runtime_error {
public:
    MemberKickedByOrganizer(const std::string& message) : std::runtime_error(message) {}
};

class LevelFiveRequiredToEnableProps : public std::runtime_error {
public:
    LevelFiveRequiredToEnableProps(const std::string& message) : std::runtime_error(message) {}
};

class ChatViewOnly : public std::runtime_error {
public:
    ChatViewOnly(const std::string& message) : std::runtime_error(message) {}
};

class ChatMessageTooBig : public std::runtime_error {
public:
    ChatMessageTooBig(const std::string& message) : std::runtime_error(message) {}
};

class InviteCodeNotFound : public std::runtime_error {
public:
    InviteCodeNotFound(const std::string& message) : std::runtime_error(message) {}
};

class AlreadyRequestedJoinCommunity : public std::runtime_error {
public:
    AlreadyRequestedJoinCommunity(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_PUSH_SERVER_LIMITATION_APART : public std::runtime_error {
public:
    API_ERR_PUSH_SERVER_LIMITATION_APART(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_PUSH_SERVER_LIMITATION_COUNT : public std::runtime_error {
public:
    API_ERR_PUSH_SERVER_LIMITATION_COUNT(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_PUSH_SERVER_LINK_NOT_IN_COMMUNITY : public std::runtime_error {
public:
    API_ERR_PUSH_SERVER_LINK_NOT_IN_COMMUNITY(const std::string& message) : std::runtime_error(message) {}
};

class API_ERR_PUSH_SERVER_LIMITATION_TIME : public std::runtime_error {
public:
    API_ERR_PUSH_SERVER_LIMITATION_TIME(const std::string& message) : std::runtime_error(message) {}
};

class AlreadyCheckedIn : public std::runtime_error {
public:
    AlreadyCheckedIn(const std::string& message) : std::runtime_error(message) {}
};

class AlreadyUsedMonthlyRepair : public std::runtime_error {
public:
    AlreadyUsedMonthlyRepair(const std::string& message) : std::runtime_error(message) {}
};

class AccountAlreadyRestored : public std::runtime_error {
public:
    AccountAlreadyRestored(const std::string& message) : std::runtime_error(message) {}
};

class IncorrectVerificationCode : public std::runtime_error {
public:
    IncorrectVerificationCode(const std::string& message) : std::runtime_error(message) {}
};

class NotOwnerOfChatBubble : public std::runtime_error {
public:
    NotOwnerOfChatBubble(const std::string& message) : std::runtime_error(message) {}
};

class NotEnoughCoins : public std::runtime_error {
public:
    NotEnoughCoins(const std::string& message) : std::runtime_error(message) {}
};

class AlreadyPlayedLottery : public std::runtime_error {
public:
    AlreadyPlayedLottery(const std::string& message) : std::runtime_error(message) {}
};

class CannotSendCoins : public std::runtime_error {
public:
    CannotSendCoins(const std::string& message) : std::runtime_error(message) {}
};

class FailedSubscribeFanClub : public std::runtime_error {
public:
    FailedSubscribeFanClub(const std::string& message) : std::runtime_error(message) {}
};

class AminoIDAlreadyChanged : public std::runtime_error {
public:
    AminoIDAlreadyChanged(const std::string& message) : std::runtime_error(message) {}
};

class InvalidAminoID : public std::runtime_error {
public:
    InvalidAminoID(const std::string& message) : std::runtime_error(message) {}
};

class InvalidName : public std::runtime_error {
public:
    InvalidName(const std::string& message) : std::runtime_error(message) {}
};

class AccountDoesNotExist : public std::runtime_error {
public:
    AccountDoesNotExist(const std::string& message) : std::runtime_error(message) {}
};

class UnsupportedDeviceId : public std::runtime_error {
public:
    UnsupportedDeviceId(const std::string& message) : std::runtime_error(message) {}
};

class UnknownError : public std::runtime_error {
public:
    UnknownError(const std::string& message) : std::runtime_error(message) {}
};

#endif
