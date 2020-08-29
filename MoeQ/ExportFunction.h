#pragma once
#include "Android.h"
#include "PluginSystem.h"

extern Android Sdk;
extern PluginSystem Plugin;

extern "C" __declspec(dllexport) char* __stdcall getCookies(const uint64_t AuthCode, const char* Host)
{
	if (Plugin.VieryAuth(AuthCode, 1)) return Sdk.QQ_GetCookies(Host);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called getCookies which it don't have right.");
	}
};

extern "C" __declspec(dllexport) bool __stdcall sendLike(const uint64_t AuthCode, const uint QQ, const int Times)
{
	if (Plugin.VieryAuth(AuthCode, 2)) return Sdk.QQ_SendLike(QQ, Times);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called sendLike which it don't have right.");
		return false;
	}
};


extern "C" __declspec(dllexport) bool __stdcall setGroupLeave(const uint64_t AuthCode, const uint group_code)
{
	if (Plugin.VieryAuth(AuthCode, 2))
	{
		return false;
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called setGroupLeave which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall sendPrivateMsg(const uint64_t AuthCode, const uint QQ, const Message::Msg * Msg)
{
	if (Plugin.VieryAuth(AuthCode, 5)) return Sdk.QQ_SendPrivateMsg(QQ, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called sendPrivateMsg which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall sendGroupMsg(const uint64_t AuthCode, const uint Group, const Message::Msg * Msg)
{
	if (Plugin.VieryAuth(AuthCode, 6)) return Sdk.QQ_SendGroupMsg(Group, Msg);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called sendGroupMsg which it don't have right.");
		return false;
	}
};


extern "C" __declspec(dllexport) bool __stdcall drawPrivateMsg(const uint64_t AuthCode, const uint QQ, const uint MsgID)
{
	if (Plugin.VieryAuth(AuthCode, 8))
	{
		//
		//return Sdk.QQ_DrawPrivateMsg(QQ, Msg);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called drawPrivateMsg which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall drawGroupMsg(const uint64_t AuthCode, const uint Group, const uint MsgID)
{
	if (Plugin.VieryAuth(AuthCode, 8))
	{
		//
		//return Sdk.QQ_DrawGroupMsg(Group, Msg);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called drawGroupMsg which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall setGroupBan(const uint64_t AuthCode, const uint Group, const uint QQ, const uint Time)
{
	if (Plugin.VieryAuth(AuthCode, 9))
	{
		if (QQ == 0) return Sdk.QQ_SetGroupBan(Group, Time);
		else Sdk.QQ_SetGroupMemberBan(Group, QQ, Time);
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called setGroupBan which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall setGroupKick(const uint64_t AuthCode, const uint Group, const uint QQ, const bool Forever)
{
	if (Plugin.VieryAuth(AuthCode, 10))	return Sdk.QQ_KickGroupMember(Group,QQ, Forever);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called setGroupKick which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall setGroupAdmin(const uint64_t AuthCode, const uint Group, const uint QQ, const bool Set)
{
	if (Plugin.VieryAuth(AuthCode, 11))	return Sdk.QQ_SetGroupAdmin(Group, QQ, Set);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called setGroupAdmin which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall setGroupMemberTitle(const uint64_t AuthCode, const uint Group, const uint QQ, const char* Title)
{
	if (Plugin.VieryAuth(AuthCode, 12)) return Sdk.QQ_SetGroupMemberTitle(Group, QQ, Title);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called setGroupMemberTitle which it don't have right.");
		return false;
	}
};

extern "C" __declspec(dllexport) bool __stdcall setGroupMemberCard(const uint64_t AuthCode, const uint Group, const uint QQ, const char* Card)
{
	if (Plugin.VieryAuth(AuthCode, 13)) Sdk.QQ_SetGroupMemberCard(Group,QQ, Card);
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called setGroupMemberCard which it don't have right.");
		return false;
	}
};


extern "C" __declspec(dllexport) LPBYTE __stdcall getFriendList(const uint64_t AuthCode)
{
	if (Plugin.VieryAuth(AuthCode, 17))
	{
		const std::vector<Android::FriendInfo>* FriendList = Sdk.QQ_GetFriendList();
		Pack Pack(FriendList->size() * 24 + 8, true);
		Pack.SetInt(FriendList->size());
		for (size_t i = 0; i < FriendList->size(); i++)
		{
			Pack.SetInt((*FriendList)[i].QQ);
#if _WIN64
			Pack.SetLong((long long)(*FriendList)[i].Nick);
#else
			Pack.SetLong((int)(*FriendList)[i].Nick);
#endif
			Pack.SetInt((*FriendList)[i].status);
#if _WIN64
			Pack.SetLong((long long)(*FriendList)[i].Remark);
#else
			Pack.SetLong((int)(*FriendList)[i].Remark);
#endif
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called getFriendList which it don't have right.");
		return (LPBYTE)"\0\0\0\0";
	}
};

extern "C" __declspec(dllexport) LPBYTE __stdcall getGroupList(const uint64_t AuthCode)
{
	if (Plugin.VieryAuth(AuthCode, 18))
	{
		const std::vector<Android::GroupInfo>* GroupList = Sdk.QQ_GetGroupList();
		Pack Pack(GroupList->size() * 19 + 8, true);
		Pack.SetInt(GroupList->size());
		for (size_t i = 0; i < GroupList->size(); i++)
		{
			Pack.SetInt((*GroupList)[i].GroupCode);
#if _WIN64
			Pack.SetLong((long long)(*GroupList)[i].GroupName);
#else
			Pack.SetLong((int)(*GroupList)[i].GroupName);
#endif
			Pack.SetInt((*GroupList)[i].MasterQQ);
			Pack.SetShort((*GroupList)[i].MemberCount);
			Pack.SetByte((*GroupList)[i].SelfIdentity);
		}
		Pack.SetLength();
		return Pack.GetAll();
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called getGroupList which it don't have right.");
		return (LPBYTE)"\0\0\0\0";
	}
};

extern "C" __declspec(dllexport) LPBYTE __stdcall getGroupMemberList(const uint64_t AuthCode, const uint group_code)
{
	if (Plugin.VieryAuth(AuthCode, 19))
	{
		/*
		const std::vector<Android::GroupMemberInfo>* GroupMemberList = Sdk.QQ_GetGroupMemberList(group_code);
		Pack Pack(GroupMemberList->size() *  + 8, true);
		Pack.SetInt(GroupMemberList->size());
		for (size_t i = 0; i < GroupMemberList->size(); i++)
		{
			//
		}
		Pack.SetLength();
		return Pack.GetAll();
		*/
	}
	else
	{
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called getGroupMemberList which it don't have right.");
		return (LPBYTE)"\0\0\0\0";
	}
};

extern "C" __declspec(dllexport) LPBYTE __stdcall getGroupAdminList(const uint64_t AuthCode, const uint group_code)
{
	if (Plugin.VieryAuth(AuthCode, 20))
	{
		const std::vector<uint>* AdminList = Sdk.QQ_GetGroupAdminList(group_code);
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
		Log::AddLog(Log::LogType::WARNING, Log::MsgType::PROGRAM, Iconv::Ansi2Unicode(Plugin.AuthCode2Name(AuthCode)), L"Plugin called getGroupList which it don't have right.");
		return (LPBYTE)"\0\0\0\0";
	}
};


extern "C" __declspec(dllexport) void __stdcall addLog(const uint64_t AuthCode, const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
	Log::AddLog(LogType, MsgType, Type, Msg);
};