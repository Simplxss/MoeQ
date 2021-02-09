#pragma once

#include "Log.h"

#include <fstream>
#include <io.h>
#include <libloaderapi.h>

namespace Event
{
	void OnGroupMsg(const GroupMsg* GroupMsg);
	void OnPrivateMsg(const PrivateMsg* PrivateMsg);
	void OnNoticeMsg(const NoticeEvent::NoticeEvent* NoticeEvent);
	void OnRequestMsg(const RequestEvent::RequestEvent* RequestEvent);
}

class PluginSystem
{
private:
	struct Event
	{
		char type;
		void* function;
		char subevent;
		byte priority;
	};

	struct Menu
	{
		typedef void(__stdcall* Munu)(const uint ID);
		Munu function;
		std::vector<char*> CaptionList;
	};

	struct Plugin
	{
		char* Name;
		char* Appid;
		char* Version;
		char* Author;
		char* Description;

		std::vector<PluginSystem::Event> EventList;
		PluginSystem::Menu Menu;
		uint Auth;

		uint64_t AuthCode;
		bool Enable = false;
	};

	std::vector<Plugin> PluginList;

	typedef void(__stdcall* LifeCycleEvent)(const ::Event::LifeCycleEvent::LifeCycleEventType);
	std::vector<LifeCycleEvent>LifeCycleEventList[4]; //4 subevents

	typedef ::Event::ReturnType(__stdcall* MessageEvent)(const ::Target::Target*, const ::Message::Msg*, const uint);
	std::vector<MessageEvent>MessageEventList[3]; //3 subevents

	typedef ::Event::ReturnType(__stdcall* NoticeEvent)(const ::Event::NoticeEvent::NoticeEvent*);
	std::vector<NoticeEvent>NoticeEventList[4]; //4 subevents

	typedef ::Event::RequestEvent::ReturnType(__stdcall* RequestEvent)(const ::Event::RequestEvent::RequestEvent* RequestEvent, const uint responseFlag);
	std::vector<RequestEvent>RequestEventList[2]; //2 subevents
public:
	void Load(char* szFilePath);
	void LoadEvent();
	bool VieryAuth(const uint64_t auth_code, const int auth);
	const char* AuthCode2Name(const uint64_t auth_code);
	void BroadcastLifeCycleEvent(const ::Event::LifeCycleEvent::LifeCycleEventType LifeCycleEventType);
	void BroadcastMessageEvent(const ::Target::Target* Target, const ::Message::Msg* Msg, const uint MsgID);
	void BroadcastNoticeEvent(const ::Event::NoticeEvent::NoticeEvent* NoticeEvent);
	void BroadcastRequestEvent(const ::Event::RequestEvent::RequestEvent* RequestEvent, const uint responseFlag);
};
