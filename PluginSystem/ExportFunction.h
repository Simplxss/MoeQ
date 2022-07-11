#pragma once
#include "../Protocol/Android.h"

extern Android Sdk;
extern PluginSystem Plugin;

#if defined(_WIN_PLATFORM_)
extern wchar_t DataPath[MAX_PATH + 1];
#define FUNC(ReturnType, FuncName, ...) extern "C" __declspec(dllexport) ReturnType __stdcall FuncName(const uint64_t AuthCode, ##__VA_ARGS__)
#endif

#if defined(_LINUX_PLATFORM_)
extern char DataPath[PATH_MAX + 1];
#define FUNC(ReturnType, FuncName, ...) extern "C" __attribute__((visibility("default"))) ReturnType FuncName(const uint64_t AuthCode, ##__VA_ARGS__)
#endif

FUNC(bool, getDataPath, char8_t *Path)
{
#if defined(_WIN_PLATFORM_)
	std::u8string _Path(Iconv::UnicodeToUtf8(DataPath));
#endif

#if defined(_LINUX_PLATFORM_)
	std::u8string _Path((char8_t *)DataPath);
#endif

	_Path.append(Plugin.AuthCode2Name(AuthCode));

#if defined(_WIN_PLATFORM_)
	_Path.append(u8"\\");

#endif

#if defined(_LINUX_PLATFORM_)
	_Path.append(u8"/");
#endif

	if (_Path.length() <= MAX_PATH)
	{
		memcpy(Path, _Path.c_str(), _Path.length());
		return true;
	}
	else
		return false;
}

FUNC(uint32_t, getUin)
{
	return Sdk.QQ_Get_Account();
};

FUNC(char8_t *, getCookies, const char8_t *Host)
{
	if (Plugin.VieryAuth(AuthCode, 1))
		return (char8_t *)Sdk.QQ_GetCookies((char *)Host);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getCookies which it don't have right.");
		return nullptr;
	}
};

FUNC(bool, sendLike, const uint32_t QQ, const int Times)
{
	if (Plugin.VieryAuth(AuthCode, 2))
		return Sdk.QQ_SendLike(QQ, Times);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendLike which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupLeave, const uint32_t group_code)

{
	if (Plugin.VieryAuth(AuthCode, 3))
		return Sdk.QQ_KickGroupMember(group_code, Sdk.QQ_Get_Account(), false);
	else
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupLeave which it don't have right.");
	return false;
};

FUNC(bool, sendPrivateMsg, const uint32_t QQ, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 4))
		return Sdk.QQ_SendMsg(QQ, 2, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendPrivateMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, sendGroupMsg, const uint32_t Group, const Message::Msg *Msg)
{
	if (Plugin.VieryAuth(AuthCode, 5))
		return Sdk.QQ_SendMsg(Group, 1, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called sendGroupMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, drawPrivateMsg, const uint32_t QQ, const uint64_t MsgID_)
{
	if (Plugin.VieryAuth(AuthCode, 6))
	{
		auto [MsgID, MsgRand] = Database::GetPrivateMsg(MsgID_);
		return Sdk.QQ_DrawPrivateMsg(QQ, MsgID, MsgRand);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called drawPrivateMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, drawGroupMsg, const uint32_t Group, const uint64_t MsgID_)
{
	if (Plugin.VieryAuth(AuthCode, 6))
	{
		auto [MsgID, MsgRand] = Database::GetGroupMsg(MsgID_);
		return Sdk.QQ_DrawGroupMsg(Group, MsgID, MsgRand);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called drawGroupMsg which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupBan, const uint32_t Group, const uint32_t QQ, const uint32_t Time)
{
	if (Plugin.VieryAuth(AuthCode, 7))
	{
		if (QQ == 0)
			return Sdk.QQ_SetGroupBan(Group, Time);
		else
			return Sdk.QQ_SetGroupMemberBan(Group, QQ, Time);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupBan which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupKick, const uint32_t Group, const uint32_t QQ, const bool Forever)
{
	if (Plugin.VieryAuth(AuthCode, 8))
		return Sdk.QQ_KickGroupMember(Group, QQ, Forever);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupKick which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupAdmin, const uint32_t Group, const uint32_t QQ, const bool Set)
{
	if (Plugin.VieryAuth(AuthCode, 9))
		return Sdk.QQ_SetGroupAdmin(Group, QQ, Set);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupAdmin which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupMemberTitle, const uint32_t Group, const uint32_t QQ, const char8_t *Title)
{
	if (Plugin.VieryAuth(AuthCode, 10))
		return Sdk.QQ_SetGroupMemberTitle(Group, QQ, (char*)Title);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberTitle which it don't have right.");
		return false;
	}
};

FUNC(bool, setGroupMemberCard, const uint32_t Group, const uint32_t QQ, const char8_t *Card)
{
	if (Plugin.VieryAuth(AuthCode, 11))
		return Sdk.QQ_SetGroupMemberCard(Group, QQ, (char*)Card);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
		return false;
	}
};

FUNC(void, getGroupMemberInfo, const uint32_t Group, const uint32_t QQ){
	/*
	if (Plugin.VieryAuth(AuthCode, 12)) Sdk.QQ_GetGroupMemberInfo(Group, QQ);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(void, getStrangerInfo, const uint32_t QQ){
	/*
	if (Plugin.VieryAuth(AuthCode, 13)) Sdk.QQ_GetStrangerInfo(QQ);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(void, getGroupInfo, const uint32_t Group){
	/*
	if (Plugin.VieryAuth(AuthCode, 14)) Sdk.QQ_GetGroupInfo(Group);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called setGroupMemberCard which it don't have right.");
	}*/
};

FUNC(LPBYTE, getFriendList)
{
	if (Plugin.VieryAuth(AuthCode, 15))
	{
		const std::vector<QQ::FriendInfo> *FriendList = Sdk.QQ_GetFriendList();
		Pack Pack(FriendList->size() * 40 + 8, true);
		Pack.SetInt(FriendList->size());
		for (size_t i = 0; i < FriendList->size(); i++)
		{
			Pack.SetInt((*FriendList)[i].QQ);
			Pack.SetInt(strlen((const char *)((*FriendList)[i].Nick)));
			Pack.SetStr((*FriendList)[i].Nick);
			Pack.SetInt((*FriendList)[i].status);
			Pack.SetInt(strlen((const char *)((*FriendList)[i].Remark)));
			Pack.SetStr((*FriendList)[i].Remark);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getFriendList which it don't have right.");
		return 0;
	}
};

FUNC(LPBYTE, getGroupList)
{
	if (Plugin.VieryAuth(AuthCode, 16))
	{
		const std::vector<QQ::GroupInfo> *GroupList = Sdk.QQ_GetGroupList();
		Pack Pack(GroupList->size() * 30 + 8, true);
		Pack.SetInt(GroupList->size());
		for (size_t i = 0; i < GroupList->size(); i++)
		{
			Pack.SetInt((*GroupList)[i].GroupCode);
			Pack.SetInt(strlen((const char *)((*GroupList)[i].GroupName)));
			Pack.SetStr((*GroupList)[i].GroupName);
			Pack.SetInt((*GroupList)[i].MasterQQ);
			Pack.SetShort((*GroupList)[i].MemberCount);
			Pack.SetByte((*GroupList)[i].SelfIdentity);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getGroupList which it don't have right.");
		return 0;
	}
};

FUNC(LPBYTE, getGroupMemberList, uint32_t group_code)
{
	if (Plugin.VieryAuth(AuthCode, 17))
	{
		const std::vector<QQ::GroupMemberInfo> *GroupMemberList = Sdk.QQ_GetGroupMemberList(group_code);
		if (GroupMemberList == nullptr)
			return 0;

		Pack Pack(GroupMemberList->size() * 15 + 8, true);
		Pack.SetInt(GroupMemberList->size());
		for (size_t i = 0; i < GroupMemberList->size(); i++)
		{
			Pack.SetInt((*GroupMemberList)[i].QQ);
			Pack.SetInt(strlen((const char *)((*GroupMemberList)[i].Nick)));
			Pack.SetStr((*GroupMemberList)[i].Nick);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getGroupMemberList which it don't have right.");
		return 0;
	}
};

FUNC(LPBYTE, getGroupAdminList, uint32_t group_code)
{
	if (Plugin.VieryAuth(AuthCode, 18))
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
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called getGroupList which it don't have right.");
		return 0;
	}
};

FUNC(void, addLog, const Log::LogType LogType, const char8_t *Type, const char8_t *Msg)
{
	Log::AddLog(LogType, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Type: %s, Msg: %s.", true, Type, Msg);
};

FUNC(void *, function, const uint64_t id, ...)
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
		return 0;
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PLUGIN, Plugin.AuthCode2Name(AuthCode), u8"Plugin called function which it don't have right.");
		return 0;
	}
};
