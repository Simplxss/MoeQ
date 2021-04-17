#pragma once
/*
#include "Socket.h"
#include "JceStruct.h"
#include "Protobuf.h"
#include "Tlv.h"
#include "Tea.h"
#include "ThreadPool.h"
#include "Log.h"

#include <ctime>

#define QQ_APPID 
#define QQ_VERSION "3.3.1"
#define QQ_APKID ""
#define QQ_ASIG (const byte*)"\xA6\xB7\x45\xBF\x24\xA2\xC2\x77\x52\x77\x16\xF6\xF3\x6E\xB6\x8D"
#define QQ_SDK_VERSION "6.0.0.2432"
#define QQ_BUILDTIME 1593489106

#define LOGIN_ERROR 0
#define LOGIN_SUCCESS 1
#define LOGIN_VERIY 2
#define LOGIN_VERIY_SMS 160

class Tim
{
public:
	struct Token
	{
		byte* A2 = nullptr;//64
		byte* A5 = nullptr;
		byte* A8 = nullptr;
		byte* D2Key = nullptr;//16
		byte* wtSessionTicket = nullptr;//48
		byte* wtSessionTicketKey = nullptr;//16
		byte* StSig = nullptr;
		byte* StKey = nullptr;
		byte* token_16A = nullptr;//56
		byte* md5 = nullptr;//16
		byte* md52 = nullptr;//16
		byte* TGT = nullptr;//72
		byte* TGTkey = nullptr;//16
		byte* ksid = nullptr;//16
	};
	struct FriendInfo
	{
		uint QQ;
		char* Nick;
		int status;
		char* Remark;
	};
	struct GroupMemberInfo
	{
		uint QQ;
		char* Nick;
	};
	struct GroupInfo
	{
		uint GroupCode;
		char* GroupName;
		uint MasterQQ;
		short MemberCount;
		byte SelfIdentity;
	};
private:
	struct Login
	{
		Utils::ECDHKEY ECDH;
		byte* RandKey = nullptr;
		byte* VieryToken1 = nullptr;
		byte* VieryToken2 = nullptr;
		byte* ClientPow = nullptr;
		byte* token_402 = nullptr;//8
		byte* token_403 = nullptr;//8
		byte* Viery_Image = nullptr;
		char* Viery_Ticket = nullptr;
		char* PhoneNumber = nullptr;
		char* SmsToken = nullptr;
		byte state;
	};
	struct p_skey
	{
		char* host;
		char* p_skey;
	};
	struct Cookie
	{
		byte* StWebSig = nullptr;
		byte* sid = nullptr;
		char* skey = nullptr;
		char* vkey = nullptr;
		char* superKey = nullptr;
		std::vector<p_skey> p_skey;
	};
	struct QQ
	{
		uint QQ;
		char* QQ_Str = nullptr;
		char* Nick = nullptr;//utf8
		byte Status = 21;
		char* ErrorMsg = nullptr;
		std::atomic_int SsoSeq;
		unsigned char* MsgCookie = nullptr;//4
		LPBYTE SyncCookies = nullptr;
		char Version[33] = "|\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0|";
		Tim::Login* Login = nullptr;
		Tim::Token Token;
		Tim::Cookie Cookie;

		std::vector<Tim::FriendInfo> FriendList;
		std::vector<Tim::GroupInfo> GroupList;//不包含被封群
	};
	struct Device
	{
		char* IMEI = nullptr;
		const char* QIMEI = nullptr;//算法未知 在so层中
		char* IMSI = nullptr;
		byte* MAC = nullptr;
		const char* BSSID = nullptr;
		byte* GUID = nullptr;
		char* _device = nullptr;
		char* Brand = nullptr;
		const char* os_type = nullptr;
		const char* os_version = nullptr;
		unsigned short _network_type;
		const char* _apn = nullptr;
		const char* NetworkName = nullptr;
		const char* WiFiName = nullptr;
	};
	struct SenderInfo
	{
		std::condition_variable cv;
		LPBYTE BodyBin;
	};
private:
	QQ QQ;
	Device Device;
	Socket TCP;
	ThreadPool HandleThreads;
	SenderInfo SendList[64]; // 0x3F
	bool Connected;
public:
		Tim(const char* IMEI, const char IMSI[16], const byte GUID[16], const byte MAC[6], const char* _device, const char* Brand);
private:
	bool Fun_Connect(const char* IP = nullptr, const unsigned short Port = 0);
	int Fun_Send(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer);
	LPBYTE Fun_Send_Sync(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer);
	void Fun_Msg_Loop();
	void Fun_Receice(LPBYTE bin);
	void Fun_Handle(char* serviceCmd, const LPBYTE BodyBin, const uint sso_seq);
	void Fun_Life_Event();
private:
	LPBYTE Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char* sServantName, const char* sFuncName, byte* sBuffer, uint Bufferlen);
	LPBYTE Make_Body_PC(byte* Buffer, const uint BufferLen, const bool emp);
};
*/