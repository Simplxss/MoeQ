#pragma once
#include "../Protocol/Android.h"

extern Android Sdk;
extern PluginSystem Plugin;

#if defined(_WIN_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __declspec(dllexport) ReturnType __stdcall FuncName(const uint64_t AuthCode, ##__VA_ARGS__)
#endif

#if defined(_LINUX_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __attribute__((visibility("default"))) ReturnType FuncName(const uint64_t AuthCode, ##__VA_ARGS__)
#endif

FUNC(const char*, getDataPath)
{
	char* Path = new char[MAX_PATH];
	//DataPath
	Plugin.AuthCode2Name(AuthCode);
	return Path;
}

FUNC(uint32_t, getUin)
{
	return Sdk.QQ_Get_Account();
};

FUNC(char *, getCookies, const char *Host)
{
	if (Plugin.VieryAuth(AuthCode, 1))
		return Sdk.QQ_GetCookies(Host);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getCookies which it don't have right.");
		return nullptr;
	}
};

FUNC(bool, sendLike, const uint32_t QQ, const int Times)
{
	if (Plugin.VieryAuth(AuthCode, 2))
		return Sdk.QQ_SendLike(QQ, Times);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendLike which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupLeave, const uint32_t group_code)

{
	if (Plugin.VieryAuth(AuthCode, 3))
		return Sdk.QQ_KickGroupMember(group_code, Sdk.QQ_Get_Account(), false);
	else
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupLeave which it don't have right.");
	return false;
};

FUNC(bool, setDiscussLeave, const uint32_t group_code)
{
	if (Plugin.VieryAuth(AuthCode, 4))
	{
		return false;
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupLeave which it don't have right.");
		return false;
	}
};

FUNC(bool, sendPrivateMsg, const uint32_t QQ, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 5))
		return Sdk.QQ_SendMsg(QQ, 2, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendPrivateMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, sendGroupMsg, const uint32_t Group, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 6))
		return Sdk.QQ_SendMsg(Group, 1, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendGroupMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, sendDisscussMsg, const uint32_t Disscuss, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 7))
		return Sdk.QQ_SendDisscussMsg(Disscuss, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendGroupMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, drawPrivateMsg, const uint32_t QQ, const uint64_t MsgID_)
{
	if (Plugin.VieryAuth(AuthCode, 8))
	{
		auto [MsgID, MsgRand] = Database::GetPrivateMsg(MsgID_);
		return Sdk.QQ_DrawPrivateMsg(QQ, MsgID, MsgRand);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called drawPrivateMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, drawGroupMsg, const uint32_t Group, const uint64_t MsgID_)
{
	if (Plugin.VieryAuth(AuthCode, 8))
	{
		auto [MsgID, MsgRand] = Database::GetGroupMsg(MsgID_);
		return Sdk.QQ_DrawGroupMsg(Group, MsgID, MsgRand);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called drawGroupMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupBan, const uint32_t Group, const uint32_t QQ, const uint32_t Time)
{
	if (Plugin.VieryAuth(AuthCode, 9))
	{
		if (QQ == 0)
			return Sdk.QQ_SetGroupBan(Group, Time);
		else
			return Sdk.QQ_SetGroupMemberBan(Group, QQ, Time);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupBan which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupKick, const uint32_t Group, const uint32_t QQ, const bool Forever)
{
	if (Plugin.VieryAuth(AuthCode, 10))
		return Sdk.QQ_KickGroupMember(Group, QQ, Forever);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupKick which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupAdmin, const uint32_t Group, const uint32_t QQ, const bool Set)
{
	if (Plugin.VieryAuth(AuthCode, 11))
		return Sdk.QQ_SetGroupAdmin(Group, QQ, Set);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupAdmin which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupMemberTitle, const uint32_t Group, const uint32_t QQ, const char *Title)
{
	if (Plugin.VieryAuth(AuthCode, 12))
		return Sdk.QQ_SetGroupMemberTitle(Group, QQ, Title);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberTitle which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupMemberCard, const uint32_t Group, const uint32_t QQ, const char *Card)
{
	if (Plugin.VieryAuth(AuthCode, 13))
		return Sdk.QQ_SetGroupMemberCard(Group, QQ, Card);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
		return false;
	}
};

FUNC(void, getGroupMemberInfo, const uint32_t Group, const uint32_t QQ){
	/*
	if (Plugin.VieryAuth(AuthCode, 14)) Sdk.QQ_GetGroupMemberInfo(Group, QQ);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(void, getStrangerInfo, const uint32_t QQ){
	/*
	if (Plugin.VieryAuth(AuthCode, 15)) Sdk.QQ_GetStrangerInfo(QQ);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(void, getGroupInfo, const uint32_t Group){
	/*
	if (Plugin.VieryAuth(AuthCode, 16)) Sdk.QQ_GetGroupInfo(Group);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(LPBYTE, getFriendList)
{
	if (Plugin.VieryAuth(AuthCode, 17))
	{
		const std::vector<QQ::FriendInfo> *FriendList = Sdk.QQ_GetFriendList();
		Pack Pack(FriendList->size() * 24 + 8, true);
		Pack.SetInt(FriendList->size());
		for (size_t i = 0; i < FriendList->size(); i++)
		{
			Pack.SetInt((*FriendList)[i].QQ);
			Pack.SetLong((long long)(*FriendList)[i].Nick);
			Pack.SetInt((*FriendList)[i].status);
			Pack.SetLong((long long)(*FriendList)[i].Remark);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getFriendList which it don't have right.");
		return 0;
	}
};

FUNC(LPBYTE, getGroupList)
{
	if (Plugin.VieryAuth(AuthCode, 18))
	{
		const std::vector<QQ::GroupInfo> *GroupList = Sdk.QQ_GetGroupList();
		Pack Pack(GroupList->size() * 19 + 8, true);
		Pack.SetInt(GroupList->size());
		for (size_t i = 0; i < GroupList->size(); i++)
		{
			Pack.SetInt((*GroupList)[i].GroupCode);
			Pack.SetLong((long long)(*GroupList)[i].GroupName);
			Pack.SetInt((*GroupList)[i].MasterQQ);
			Pack.SetShort((*GroupList)[i].MemberCount);
			Pack.SetByte((*GroupList)[i].SelfIdentity);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getGroupList which it don't have right.");
		return 0;
	}
};

FUNC(LPBYTE, getGroupMemberList, uint32_t group_code)
{
	if (Plugin.VieryAuth(AuthCode, 19))
	{
		const std::vector<QQ::GroupMemberInfo> *GroupMemberList = Sdk.QQ_GetGroupMemberList(group_code);
		if (GroupMemberList == nullptr)
			return 0;

		Pack Pack(GroupMemberList->size() * +8, true);
		Pack.SetInt(GroupMemberList->size());
		for (size_t i = 0; i < GroupMemberList->size(); i++)
		{
			Pack.SetInt((*GroupMemberList)[i].QQ);
			Pack.SetInt(strlen((*GroupMemberList)[i].Nick));
			Pack.SetStr((*GroupMemberList)[i].Nick);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getGroupMemberList which it don't have right.");
		return 0;
	}
};

FUNC(LPBYTE, getGroupAdminList, uint32_t group_code)
{
	if (Plugin.VieryAuth(AuthCode, 20))
	{
		const std::vector<uint32_t> *AdminList = Sdk.QQ_GetGroupAdminList(group_code);
		Pack Pack(AdminList->size() * 4 + 8, true);
		Pack.SetInt(AdminList->size());
		for (size_t i = 0; i < AdminList->size(); i++)
		{
			Pack.SetInt((*AdminList)[i]);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getGroupList which it don't have right.");
		return 0;
	}
};

FUNC(void, addLog, const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg)
{
	Log::AddLog(LogType, MsgType, Type, Msg);
};

FUNC(void*, function, const uint64_t id, ...)
{
	if (Plugin.VieryAuth(AuthCode, id))
	{
		va_list args;
		va_start(args, id);
		switch (id)
		{
		case 40:
		{
			return 0;
		}
		break;
		default:
			break;
		}
		va_end(args);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called function which it don't have right.");
		return 0;
	}
};
