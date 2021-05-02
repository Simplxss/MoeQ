#pragma once
#include <stdint.h>

typedef unsigned char byte;
typedef unsigned int uint;
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
        reply = 45,
        json = 51,
    };

    struct Data
    {
        uint32_t Length = 0;
        byte *Contain = nullptr;
        char8_t *URL = nullptr;
        char *Location = nullptr;
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
        uint32_t AtQQ; //if text == nullptr,this is a at,0=AtAll
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
        uint32_t Width = 0;
        uint32_t Height = 0;
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
		discuss = 2,
	};

	struct Target
	{
		const ::Target::TargetType TargetType;
		const void *Sender;
	};

	struct _private
	{
		const uint32_t FromQQ;
		// 0 FromFriend 1 From Online State 2 From Group 3 From Discuss
		// 0 来自好友 1 来自在线状态 2 来自群 3来自讨论组
		const uint32_t FromType;
	};
	struct group
	{
		const uint32_t FromGroup;
		const uint32_t FromQQ;
	};
	struct discuss
	{
		const uint32_t FromDiscuss;
		const uint32_t FromQQ;
	};
}

namespace Event
{
    enum class ReturnType
    {
        ignore, //Ignore 忽略
        block,	//Block 阻塞
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
            group_fileupload,	//Group file upload 群文件上传
            group_adminchange,	//Group administrator changes 群管理员变动
            group_memberchange, //The change in the number of group members 群成员数量变动
            group_mute,			//Group ban 群禁言
            friend_added,		//Friend added 好友已添加
        };

        struct NoticeEvent
        {
            Event::NoticeEvent::NoticeEventType NoticeEventType;
            void *Information;
        };

        struct FileInfo
        {
            char *Name;
            char *ID;
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
            uint32_t Type; // 0 Cancelled administrator 被取消管理员 1 Set up administrator 被设置管理员
        };
        struct group_memberchange
        {
            uint32_t Type; // 0 Increase(Don't include Invited) 增加(不包括被邀请) 1 Invited 被邀请 2 Decrease(Don't include kicked and disband) 减少(不包括被踢和解散) 3 Kicked 被踢 4 Disband 解散
            uint32_t FromGroup;
            uint32_t FromQQ;
            uint32_t OperateQQ; //Type为1,3可用
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
            add_group
        };

        enum class ReturnType
        {
            agree,	  //Agree 同意
            disagree, //Disagree 不同意
            ignore,	  //Ignore 忽略
        };

        struct RequestEvent
        {
            Event::RequestEvent::RequestEventType RequestEventType;
            void *Information;
        };

        struct add_friend
        {
            uint32_t FromQQ;
            char8_t *msg;
        };
        struct add_group
        {
            uint32_t FromGroup;
            uint32_t FromQQ;
            char8_t *msg;
            uint32_t Type; // 0 Others apply to join the group 他人申请入群 1 Myself was invited to join the group 自己受邀入群
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
        OTHER = 4
    };

    struct Log
    {
        ::Log::LogType LogType;
        ::Log::MsgType MsgType;
        const std::u8string Type;
        const std::u8string Msg;
    };
}