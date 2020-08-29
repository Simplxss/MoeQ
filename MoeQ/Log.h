#pragma once
#include "Utils.h"
#include "Event.h"

#include <iostream>

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
	void AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const wchar_t* Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const wchar_t* Type, const Message::Msg* Msg);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::NoticeEvent::NoticeEvent* NoticeEvent);
	void AddLog(const LogType LogType, const MsgType MsgType, const Event::RequestEvent::RequestEvent* RequestEvent);
};

