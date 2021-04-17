#pragma once

#include <thread>
#include <queue>
#include <atomic>
#include <condition_variable>

#include "Utils.h"

namespace Message
{
	std::u8string ParseMsg(Message::Msg *Msg);
	void DestoryMsg(Message::Msg *Msg);
}

namespace Database
{
	void Init();
	void UnInit();
	uint64_t AddPrivateMsg(const Event::PrivateMsg *PrivateMsg);
	uint64_t AddGroupMsg(const Event::GroupMsg *GroupMsg);
	void AddPicture(const char MD5[16], const char8_t *Url, const unsigned short Length, const unsigned short Width, const unsigned short Height);
	void AddVoice(const char MD5[16], const char8_t *Url);
	void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg);
	std::tuple<uint, uint> GetPrivateMsg(const uint64_t MsgID);
	std::tuple<uint, uint> GetGroupMsg(const uint64_t MsgID);
	std::u8string GetPictureUrl(const char MD5[16]);
	std::u8string GetVoiceUrl(const char MD5[16]);
}

namespace Log
{
	void DesplayThread();
	void Init();

	#if defined(_WIN_PLATFORM_)

	void AddLog(const LogType LogType, const MsgType MsgType, const char *Type, const char *Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const char *Type, const char8_t *Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const char8_t *Type, const char *Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const wchar_t *Type, const wchar_t *Msg);

	#endif

	void AddLog(const LogType LogType, const MsgType MsgType, const char8_t* Type, const char8_t* MsgFormat, ...);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent *NoticeEvent);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent *RequestEvent);
};