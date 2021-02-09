#pragma once
#include "Utils.h"

#include <sstream>
#include <thread>
#include <queue>
#include <codecvt>
#include <condition_variable>

namespace Message
{
	std::u8string ParseMsg(Message::Msg* Msg);
	void DestoryMsg(Message::Msg* Msg);
}

namespace Database
{
	void Init();
	void UnInit();
	uint AddPrivateMsg(const Event::PrivateMsg* PrivateMsg);
	uint AddGroupMsg(const Event::GroupMsg* GroupMsg);
	void AddPicture(const char MD5[16], const char* Url, const unsigned short Length, const unsigned short Width, const unsigned short Height);
	void AddVoice(const char MD5[16], const char* Url);
	void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg);
	::Event::PrivateMsg* GetPrivateMsg(const uint MsgID);
	::Event::GroupMsg* GetGroupMsg(const uint MsgID);
	std::string GetPictureUrl(const char MD5[16]);
	std::string GetVoiceUrl(const char MD5[16]);
}

namespace Log
{
	void DesplayThread();
	void Init(HANDLE Handle);
	void AddLog(const LogType LogType, const MsgType MsgType, const char* Type, const char* Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const char* Type, const wchar_t* Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const char* Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const wchar_t* Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent* NoticeEvent);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent* RequestEvent);
};