#pragma once

#include "../Protocol/Definition.h"
#include "../Utils/Utils.h"

namespace Database
{
	void Init();
	void UnInit();
	uint64_t AddPrivateMsg(const Event::PrivateMsg *PrivateMsg);
	uint64_t AddGroupMsg(const Event::GroupMsg *GroupMsg);
	uint64_t AddRequestMsg(const Event::RequestEvent::RequestEvent *RequestMsg, const int64_t MsgSeq);
	void AddPicture(const char MD5[16], const char8_t *Url, const unsigned short Length, const unsigned short Width, const unsigned short Height);
	void AddVoice(const char MD5[16], const char8_t *Url);
	void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg);
	std::tuple<uint, uint> GetPrivateMsg(const uint64_t MsgID);
	std::tuple<uint, uint> GetGroupMsg(const uint64_t MsgID);
	uint64_t UpdataPrivateMsgState(uint MsgID, uint MsgRand);
	uint64_t UpdataGroupMsgState(uint MsgID, uint MsgRand);
	std::tuple<uint, uint> GetFriendRequestMsg(const uint64_t ResponseFlag);
	std::tuple<uint, uint, uint, uint> GetGroupRequestMsg(const uint64_t ResponseFlag);
	std::u8string GetPictureUrl(const char MD5[16]);
	std::u8string GetVoiceUrl(const char MD5[16]);
}
