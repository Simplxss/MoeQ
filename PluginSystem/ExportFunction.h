#pragma once
#include "../Protocol/Android.h"

extern Android Sdk;
extern PluginSystem Plugin;

#if defined(_WIN_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __declspec(dllexport) ReturnType __stdcall FuncName(__VA_ARGS__)
#endif

#if defined(_LINUX_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __attribute__((visibility("default"))) ReturnType FuncName(__VA_ARGS__)
#endif

FUNC(uint32_t, getUin, const uint64_t AuthCode)
{
	if (Plugin.VieryAuth(AuthCode, 1))
		return Sdk.QQ_Get_Account();
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getCookies which it don't have right.");
		return 0;
	}
};

FUNC(char *, getCookies, const uint64_t AuthCode, const char *Host)
{
	if (Plugin.VieryAuth(AuthCode, 1))
		return Sdk.QQ_GetCookies(Host);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getCookies which it don't have right.");
		return nullptr;
	}
};

FUNC(bool, sendLike, const uint64_t AuthCode, const uint32_t QQ, const int Times)
{
	if (Plugin.VieryAuth(AuthCode, 2))
		return Sdk.QQ_SendLike(QQ, Times);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendLike which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupLeave, const uint64_t AuthCode, const uint32_t group_code)

{
	if (Plugin.VieryAuth(AuthCode, 3))
		return Sdk.QQ_KickGroupMember(group_code, Sdk.QQ_Get_Account(), false);
	else
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupLeave which it don't have right.");
	return false;
};

FUNC(bool, setDiscussLeave, const uint64_t AuthCode, const uint32_t group_code)
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

FUNC(bool, sendPrivateMsg, const uint64_t AuthCode, const uint32_t QQ, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 5))
		return Sdk.QQ_SendMsg(QQ, 2, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendPrivateMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, sendGroupMsg, const uint64_t AuthCode, const uint32_t Group, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 6))
		return Sdk.QQ_SendMsg(Group, 1, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendGroupMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, sendDisscussMsg, const uint64_t AuthCode, const uint32_t Disscuss, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 7))
		return Sdk.QQ_SendDisscussMsg(Disscuss, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendGroupMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, drawPrivateMsg, const uint64_t AuthCode, const uint32_t QQ, const uint64_t MsgID_)
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

FUNC(bool, drawGroupMsg, const uint64_t AuthCode, const uint32_t Group, const uint64_t MsgID_)
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

FUNC(bool, setGroupBan, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const uint32_t Time)
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

FUNC(bool, setGroupKick, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const bool Forever)
{
	if (Plugin.VieryAuth(AuthCode, 10))
		return Sdk.QQ_KickGroupMember(Group, QQ, Forever);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupKick which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupAdmin, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const bool Set)
{
	if (Plugin.VieryAuth(AuthCode, 11))
		return Sdk.QQ_SetGroupAdmin(Group, QQ, Set);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupAdmin which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupMemberTitle, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const char *Title)
{
	if (Plugin.VieryAuth(AuthCode, 12))
		return Sdk.QQ_SetGroupMemberTitle(Group, QQ, Title);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberTitle which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupMemberCard, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const char *Card)
{
	if (Plugin.VieryAuth(AuthCode, 13))
		return Sdk.QQ_SetGroupMemberCard(Group, QQ, Card);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
		return false;
	}
};

FUNC(void, getGroupMemberInfo, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ){
	/*
	if (Plugin.VieryAuth(AuthCode, 14)) Sdk.QQ_GetGroupMemberInfo(Group, QQ);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(void, getStrangerInfo, const uint64_t AuthCode, const uint32_t QQ){
	/*
	if (Plugin.VieryAuth(AuthCode, 15)) Sdk.QQ_GetStrangerInfo(QQ);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(void, getGroupInfo, const uint64_t AuthCode, const uint32_t Group){
	/*
	if (Plugin.VieryAuth(AuthCode, 16)) Sdk.QQ_GetGroupInfo(Group);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(LPBYTE, getFriendList, const uint64_t AuthCode)
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
		return (LPBYTE) "\0\0\0\0";
	}
};

FUNC(LPBYTE, getGroupList, const uint64_t AuthCode)
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
		return (LPBYTE) "\0\0\0\0";
	}
};

FUNC(LPBYTE, getGroupMemberList, const uint64_t AuthCode, uint32_t group_code)
{
	if (Plugin.VieryAuth(AuthCode, 19))
	{
		const std::vector<QQ::GroupMemberInfo> *GroupMemberList = Sdk.QQ_GetGroupMemberList(group_code);
		if (GroupMemberList == nullptr)
			return (LPBYTE) "\0\0\0\0";

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
		return (LPBYTE) "\0\0\0\0";
	}
};

FUNC(LPBYTE, getGroupAdminList, const uint64_t AuthCode, uint32_t group_code)
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
		return (LPBYTE) "\0\0\0\0";
	}
};

FUNC(void, addLog, const uint64_t AuthCode, const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg)
{
	Log::AddLog(LogType, MsgType, Type, Msg);
};