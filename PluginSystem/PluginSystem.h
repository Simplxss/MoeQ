#pragma once

#include <fstream>

#if defined(_WIN_PLATFORM_)
#include <io.h>
#endif

#if defined(_LINUX_PLATFORM_)
#include <regex>
#include <dirent.h>
#include <dlfcn.h>
#endif

#include "../Protocol/Log.h"
#include "../Utils/Socket.h"

namespace Event
{
	void OnGroupMsg(const GroupMsg *GroupMsg);
	void OnPrivateMsg(const PrivateMsg *PrivateMsg);
	void OnNoticeMsg(const NoticeEvent::NoticeEvent *NoticeEvent);
	void OnRequestMsg(const RequestEvent::RequestEvent *RequestEvent);
}

class PluginSystem
{
private:
	struct Event
	{
		char type;
		void *function;
		char subevent;
		byte priority;
	};

	struct Menu
	{
#if defined(_WIN_PLATFORM_)
		typedef void(__stdcall *Munu)(const uint ID);
#endif
#if defined(_LINUX_PLATFORM_)
		typedef void (*Munu)(const uint ID);
#endif
		Munu function;
		std::vector<char8_t *> CaptionList;
	};

	struct Plugin
	{
		char8_t *Name;
		char8_t *Appid;
		char8_t *Version;
		char8_t *Author;
		char8_t *Description;

		std::vector<PluginSystem::Event> EventList;
		PluginSystem::Menu Menu;
		uint Auth;

		uint64_t AuthCode;
		bool Enable = false;
	};

	std::vector<Plugin> PluginList;

#if defined(_WIN_PLATFORM_)
	typedef void(__stdcall *LifeCycleEvent)(const ::Event::LifeCycleEvent::LifeCycleEventType);
	std::vector<LifeCycleEvent> LifeCycleEventList[4]; //4 subevents

	typedef ::Event::ReturnType(__stdcall *MessageEvent)(const ::Target::Target *, const ::Message::Msg *, const uint64_t);
	std::vector<MessageEvent> MessageEventList[3]; //3 subevents

	typedef ::Event::ReturnType(__stdcall *NoticeEvent)(const ::Event::NoticeEvent::NoticeEvent *);
	std::vector<NoticeEvent> NoticeEventList[4]; //4 subevents

	typedef ::Event::RequestEvent::ReturnType(__stdcall *RequestEvent)(const ::Event::RequestEvent::RequestEvent *RequestEvent, const uint64_t responseFlag);
	std::vector<RequestEvent> RequestEventList[2]; //2 subevents
#endif
#if defined(_LINUX_PLATFORM_)
	typedef void (*LifeCycleEvent)(const ::Event::LifeCycleEvent::LifeCycleEventType);
	std::vector<LifeCycleEvent> LifeCycleEventList[4]; //4 subevents

	typedef ::Event::ReturnType (*MessageEvent)(const ::Target::Target *, const ::Message::Msg *, const uint64_t);
	std::vector<MessageEvent> MessageEventList[3]; //3 subevents

	typedef ::Event::ReturnType (*NoticeEvent)(const ::Event::NoticeEvent::NoticeEvent *);
	std::vector<NoticeEvent> NoticeEventList[4]; //4 subevents

	typedef ::Event::RequestEvent::ReturnType (*RequestEvent)(const ::Event::RequestEvent::RequestEvent *, const uint64_t);
	std::vector<RequestEvent> RequestEventList[2]; //2 subevents
#endif
public:
	void Load(
#if defined(_WIN_PLATFORM_)
		const wchar_t *
#endif
#if defined(_LINUX_PLATFORM_)
		const char *
#endif
			szFilePath);
	void LoadEvent();
	bool VieryAuth(const uint64_t auth_code, const int auth);
	const char8_t *AuthCode2Name(const uint64_t auth_code);
	void BroadcastLifeCycleEvent(const ::Event::LifeCycleEvent::LifeCycleEventType LifeCycleEventType);
	void BroadcastMessageEvent(const ::Target::Target *Target, const ::Message::Msg *Msg, const uint64_t MsgID);
	void BroadcastNoticeEvent(const ::Event::NoticeEvent::NoticeEvent *NoticeEvent);
	void BroadcastRequestEvent(const ::Event::RequestEvent::RequestEvent *RequestEvent, const uint64_t responseFlag);
};
