#pragma once

#include <thread>
#include <queue>
#include <condition_variable>

#include "Database.h"

namespace Message
{
	std::u8string ParseMsg(Message::Msg *Msg);
	void DestoryMsg(Message::Msg *Msg);
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

	void AddLog(const LogType LogType, const MsgType MsgType, const char8_t *Type, const char8_t *MsgFormat, const bool Format = false, ...);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent *NoticeEvent);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent *RequestEvent);
};