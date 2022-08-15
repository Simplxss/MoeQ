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
/* AndroidQQ_ASIG 为 MD5('...')
30 82 02 53 30 82 01 BC A0 03 02 01 02 02 04 4B
BB 03 61 30 0D 06 09 2A 86 48 86 F7 0D 01 01 05
05 00 30 6D 31 0E 30 0C 06 03 55 04 06 13 05 43
68 69 6E 61 31 0F 30 0D 06 03 55 04 08 0C 06 E5
8C 97 E4 BA AC 31 0F 30 0D 06 03 55 04 07 0C 06
E5 8C 97 E4 BA AC 31 0F 30 0D 06 03 55 04 0A 0C
06 E8 85 BE E8 AE AF 31 1B 30 19 06 03 55 04 0B
0C 12 E6 97 A0 E7 BA BF E4 B8 9A E5 8A A1 E7 B3
BB E7 BB 9F 31 0B 30 09 06 03 55 04 03 13 02 51
51 30 20 17 0D 31 30 30 34 30 36 30 39 34 38 31
37 5A 18 0F 32 32 38 34 30 31 32 30 30 39 34 38
31 37 5A 30 6D 31 0E 30 0C 06 03 55 04 06 13 05
43 68 69 6E 61 31 0F 30 0D 06 03 55 04 08 0C 06
E5 8C 97 E4 BA AC 31 0F 30 0D 06 03 55 04 07 0C
06 E5 8C 97 E4 BA AC 31 0F 30 0D 06 03 55 04 0A
0C 06 E8 85 BE E8 AE AF 31 1B 30 19 06 03 55 04
0B 0C 12 E6 97 A0 E7 BA BF E4 B8 9A E5 8A A1 E7
B3 BB E7 BB 9F 31 0B 30 09 06 03 55 04 03 13 02
51 51 30 81 9F 30 0D 06 09 2A 86 48 86 F7 0D 01
01 01 05 00 03 81 8D 00 30 81 89 02 81 81 00 A1
5E 97 56 21 6F 69 4C 59 15 E0 B5 29 09 52 54 36
7C 4E 64 FA EF F0 7A E1 34 88 D9 46 61 5A 58 DD
C3 1A 41 5F 71 7D 01 9E DC 6D 30 B9 60 3D 3E 2A
7B 3D E0 AB 7E 0C F5 2D FE E3 93 73 BC 47 2F A9
97 02 7D 79 8D 59 F8 1D 52 5A 69 EC F1 56 E8 85
FD 1E 27 90 92 43 86 B2 23 0C C9 0E 3B 7A DC 95
60 3D DC F4 C4 0B DC 72 F2 2D B0 F2 16 A9 9C 37
1D 3B F8 9C BA 65 78 C6 06 99 E8 A0 D5 36 95 02
03 01 00 01 30 0D 06 09 2A 86 48 86 F7 0D 01 01
05 05 00 03 81 81 00 94 A9 B8 0E 80 69 16 45 DD
42 D6 61 17 75 A8 55 F7 1B CD 4D 77 CB 60 A8 E2
94 04 03 5A 5E 00 B2 1B CC 5D 4A 56 24 82 12 6B
D9 1B 6B 0E 50 70 93 77 CE B9 EF 8C 2E FD 12 CC
8B 16 AF D9 A1 59 F3 50 BB 27 0B 14 20 4F F0 65
D8 43 83 27 20 70 2E 28 B4 14 91 FB C3 A2 05 F5
F2 F4 25 26 D6 7F 17 61 4D 8A 97 4D E6 48 7B 2C
86 6E FE DE 3B 4E 49 A0 F9 16 BA A3 C1 33 6F D2
EE 1B 16 29 65 20 49
*/
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
            group_recall,       // Group recall 群消息撤回
            friend_recall,      // Friend recall 好友消息撤回
            friend_added        // Friend added 好友已添加
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
            uint32_t FromQQ; // 0 全群禁言
            uint32_t OperateQQ;
            uint32_t Duration; // 单位为秒 0 即被解禁
        };
        struct group_recall
        {
            uint32_t FromGroup;
            uint32_t FromQQ;
            uint32_t OperateQQ;
            uint32_t MsgId;
            uint32_t Time;
        };
        struct friend_recall
        {
            uint32_t FromQQ;
            uint32_t OperateQQ;
            uint32_t MsgId;
            uint32_t Time;
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
        };

        struct RequestEvent
        {
            Event::RequestEvent::RequestEventType RequestEventType;
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

    struct GroupWithdrawMsg
    {
        uint32_t FromGroup;
        uint32_t FromQQ;
        uint32_t OperateQQ;

        uint32_t SendTime;
        uint32_t MsgType;
        uint32_t MsgID;
        uint32_t MsgRand;
    };

    struct PrivateWithdrawMsg
    {
        uint32_t FromQQ;
        uint32_t OperateQQ;

        uint32_t SendTime;
        uint32_t MsgType;
        uint32_t MsgID;
        uint32_t MsgRand;
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