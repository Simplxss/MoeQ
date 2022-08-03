#pragma once

#include <vector>
#include <atomic>
#include <stdint.h>

#include "../Utils/Utils.h"

#define AndroidQQ_APPID 537127041
#define AndroidQQ_VERSION "8.9.2.3072"
#define AndroidQQ_VERSION_ "A8.9.2.4e64659d"
#define AndroidQQ_APKID "com.tencent.mobileqq"
#define AndroidQQ_ASIG (const byte *)"\xA6\xB7\x45\xBF\x24\xA2\xC2\x77\x52\x77\x16\xF6\xF3\x6E\xB6\x8D" // A6B745BF24A2C277527716F6F36EB68D
#define AndroidQQ_SDK_VERSION "6.0.0.2515"
#define AndroidQQ_BUILDTIME 1657223893

#define TimQQ_APPID
#define TimQQ_VERSION
#define TimQQ_VERSION_
#define TimQQ_APKID
#define TimQQ_ASIG (const byte *)"" //
#define TimQQ_SDK_VERSION ""
#define TimQQ_BUILDTIME 1657223893

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long ulong;
typedef byte *LPBYTE;

namespace Message
{
    enum class MsgType
    {
        text = 1,
        classcal_face = 2,
        expression = 6,
        picture = 8,
        xml = 12,
        red_packet = 24,
        voice = 37,
        reply = 45,
        json = 51,
    };

    struct Data
    {
        uint32_t Length = 0;
        byte *Contain = nullptr;
        char8_t *URL = nullptr;
    };

    struct Msg
    {
        Message::MsgType MsgType;
        Msg *NextPoint = nullptr;
        void *Message = nullptr;
    };

    struct text
    {
        char8_t *text;
        uint32_t AtQQ; // if text == nullptr,this is a at,0=AtAll
    };

    struct classcal_face
    {
        uint32_t id = 0;
    };

    struct expression
    {
        uint32_t id = 0;
        byte *MD5 = nullptr;
    };

    struct picture
    {
        int64_t Width = 0;
        int64_t Height = 0;
        byte *MD5 = nullptr;
        Message::Data Data;
    };

    struct voice
    {
        byte *MD5 = nullptr;
        Message::Data Data;
    };

    struct xml
    {
        char8_t *text = nullptr;
    };

    struct json
    {
        char8_t *text = nullptr;
    };

    struct reply
    {
        uint32_t MsgId;
        uint32_t QQ;
        uint32_t Time;
        Message::Msg *Msg = nullptr;
    };
}

namespace Target
{
    enum class TargetType
    {
        _private = 0,
        group = 1,
    };

    struct Target
    {
        const ::Target::TargetType TargetType;
        const void *Sender;
    };

    struct _private
    {
        const uint32_t FromQQ;
        // 0 FromFriend 1 From Online State 2 From Group
        // 0 来自好友 1 来自在线状态 2 来自群
        const uint32_t FromType;
    };
    struct group
    {
        const uint32_t FromGroup;
        const uint32_t FromQQ;
    };
}

namespace Event
{
    enum class ReturnType
    {
        ignore, // Ignore 忽略
        block,  // Block 阻塞
    };

    namespace LifeCycleEvent
    {
        enum class LifeCycleEventType
        {
            StartUp,
            ShutDown,
            PluginEnabled,
            PluginDisabled
        };
    }

    namespace NoticeEvent
    {
        enum class NoticeEventType
        {
            group_fileupload,   // Group file upload 群文件上传
            group_adminchange,  // Group administrator changes 群管理员变动
            group_memberchange, // The change in the number of group members 群成员数量变动
            group_mute,         // Group ban 群禁言
            friend_added,       // Friend added 好友已添加
        };

        struct NoticeEvent
        {
            Event::NoticeEvent::NoticeEventType NoticeEventType;
            void *Information;
        };

        struct FileInfo
        {
            char8_t *Name;
            char8_t *ID;
            unsigned long long size;
        };

        struct group_fileupload
        {
            uint32_t FromGroup;
            uint32_t FromQQ;
            FileInfo File;
        };
        struct group_adminchange
        {
            uint32_t FromGroup;
            uint32_t FromQQ;
            uint32_t Type; // 0 Cancelled administrator 被取消管理员 1 Set up administrator 被设置管理员 2 Group transfer 群转让
        };
        struct group_memberchange
        {
            uint32_t Type; // 0 Increase(Don't include Invited) 增加(不包括被邀请) 1 Invited 被邀请 2 Decrease(Don't include kicked and disband) 减少(不包括被踢和解散) 3 Kicked 被踢 4 Disband 解散
            uint32_t FromGroup;
            uint32_t FromQQ;
            uint32_t OperateQQ; // Type为1,3可用
        };
        struct group_mute
        {
            uint32_t FromGroup;
            uint32_t FromQQ;
            uint32_t OperateQQ;
            uint32_t Type; // 0 Ban 被禁言 1 Free 被解禁
        };
        struct friend_added
        {
            uint32_t FromQQ;
        };
    }

    namespace RequestEvent
    {
        enum class RequestEventType
        {
            add_friend,
            other_join_group,
            self_invited
        };

        enum class ReturnType
        {
            agree,    // Agree 同意
            disagree, // Disagree 不同意
            block,    // Block 拒绝并拉黑
            ignore,   // Ignore 忽略
        };

        struct RequestEvent
        {
            Event::RequestEvent::RequestEventType RequestEventType;
            int64_t MsgSeq;
            void *Information;
        };

        struct add_friend
        {
            uint32_t FromQQ;
            char8_t *FromQQName;

            char8_t *msg;
        };
        struct other_join_group
        {
            uint32_t FromGroup;
            uint32_t FromQQ;
            char8_t *FromGroupName;
            char8_t *FromQQName;
            
            uint32_t InvitorQQ;
            char8_t *InvitorQQName;

            char8_t *msg;
        };
        struct self_invited
        {
            uint32_t FromGroup;
            char8_t *FromGroupName;
            uint32_t InvitorQQ;
            char8_t *InvitorQQName;
        };
    }

    struct GroupMsg
    {
        uint32_t FromQQ;
        uint32_t FromGroup;
        char8_t *FromQQName;
        char8_t *FromGroupName;

        uint32_t SendTime;
        uint32_t MsgType;
        uint32_t MsgID;
        uint32_t MsgRand;

        Message::Msg *Msg = nullptr;
    };

    struct PrivateMsg
    {
        uint32_t FromQQ;
        char8_t *FromQQName;

        uint32_t SendTime;
        uint32_t MsgType;
        uint32_t MsgID;
        uint32_t MsgRand;

        Message::Msg *Msg = nullptr;
    };
}

namespace Log
{
    enum class LogType
    {
        __DEBUG = 0,
        INFORMATION = 1,
        NOTICE = 2,
        WARNING = 3,
        _ERROR = 4
    };

    enum class MsgType
    {
        SERVER = 0,
        PROGRAM = 1,
        PRIVATE = 2,
        _GROUP = 3,
        PLUGIN = 4,
        OTHER = 5
    };

    struct Log
    {
        ::Log::LogType LogType;
        ::Log::MsgType MsgType;
        const std::u8string Type;
        const std::u8string Msg;
    };
}

namespace QQ
{
    struct FriendInfo
    {
        uint QQ;
        char8_t *Nick;
        int status;
        char8_t *Remark;
    };
    struct GroupMemberInfo
    {
        uint QQ;
        char8_t *Nick;
    };
    struct GroupInfo
    {
        uint GroupCode;
        char8_t *GroupName;
        uint MasterQQ;
        short MemberCount;
        byte SelfIdentity;
    };

    struct Token
    {
        byte *A2 = nullptr; // 64
        byte *A5 = nullptr;
        byte *A8 = nullptr;
        byte *D2Key = nullptr;              // 16
        byte *wtSessionTicket = nullptr;    // 48
        byte *wtSessionTicketKey = nullptr; // 16
        byte *StSig = nullptr;
        byte *StKey = nullptr;
        byte *token_16A = nullptr; // 56
        byte *md5 = nullptr;       // 16
        byte *md52 = nullptr;      // 16
        byte *TGT = nullptr;       // 72
        byte *TGTkey = nullptr;    // 16
        byte *ksid = nullptr;      // 16
    };
    struct sig
    {
        uint32_t sync_const1;
        uint32_t sync_const2;
        uint32_t sync_const3;

        char8_t *UploadVoice_IP = nullptr;
        int UploadVoice_Port = 0;
        LPBYTE UploadVoice_ukey = nullptr; // 104
    };
    struct Login
    {
        Utils::ECDHKEY ECDH;
        byte *RandKey = nullptr;
        byte *VieryToken1 = nullptr;
        byte *VieryToken2 = nullptr;
        byte *ClientPow = nullptr;
        byte *token_402 = nullptr; // 8
        byte *token_403 = nullptr; // 8
        byte *Viery_Image = nullptr;
        char *Viery_Ticket = nullptr;
        char *PhoneNumber = nullptr;
        char *SmsToken = nullptr;
        int state = 0;
    };
    struct p_skey
    {
        char *host;
        char *p_skey;
    };
    struct Cookie
    {
        byte *StWebSig = nullptr;
        byte *sid = nullptr;
        char *skey = nullptr;
        char *vkey = nullptr;
        char *superKey = nullptr;
        std::vector<::QQ::p_skey> p_skey;
    };
    struct QQ
    {
        uint QQ;
        char *QQ_Str = nullptr;
        char8_t *Nick = nullptr;
        byte Status = 21;
        char8_t *ErrorMsg = nullptr;
        std::atomic_int SsoSeq;
        unsigned char *MsgCookie = nullptr; // 4
        char Version[33] = "|\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0|" AndroidQQ_VERSION_;
        ::QQ::Login *Login = nullptr;
        ::QQ::Token Token;
        ::QQ::sig sig;
        ::QQ::Cookie Cookie;

        std::vector<::QQ::FriendInfo> FriendList;
        std::vector<::QQ::GroupInfo> GroupList; //不包含被封群
    };
    struct Device
    {
        char *IMEI = nullptr;
        char *IMSI = nullptr;
        byte *MAC = nullptr;
        char *IP = nullptr;
        byte *GUID = nullptr;
        char *_device = nullptr;
        char *Brand = nullptr;
        unsigned short _network_type;
        const char *BSSID = nullptr;
        const char *os_type = nullptr;
        const char *os_version = nullptr;
        const char *_apn = nullptr;
        const char *NetworkName = nullptr;
        const char *WiFiName = nullptr;
    };
}