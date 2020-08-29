#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include "Socket.h"
#include "JceStruct.h"
#include "Protobuf.h"
#include "Tlv.h"
#include "Tea.h"
#include "ThreadPool.h"
#include "Log.h"

#include <ctime>
#include <atomic>

#define QQ_APPID 537064985
#define QQ_VERSION "8.4.1"
#define QQ_APKID "com.tencent.mobileqq"
#define QQ_ASIG (const byte*)"\xA6\xB7\x45\xBF\x24\xA2\xC2\x77\x52\x77\x16\xF6\xF3\x6E\xB6\x8D"
#define QQ_SDK_VERSION "6.0.0.2432"
#define QQ_BUILDTIME 1593489106

#define LOGIN_ERROR 0
#define LOGIN_SUCCESS 1
#define LOGIN_VERIY 2
#define LOGIN_VERIY_SMS 160

class Android
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
		byte* token_16A = nullptr;//48
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
		char Version[33] = "|\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0|A8.4.1.2703aac4";
		Android::Login* Login = nullptr;
		Android::Token Token;
		Android::Cookie Cookie;

		std::vector<Android::FriendInfo> FriendList;
		std::vector<Android::GroupInfo> GroupList;//����������Ⱥ
	};
	struct Device
	{
		char* IMEI = nullptr;
		const char* QIMEI = nullptr;//�㷨δ֪ ��so����
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
	SenderInfo SendList[64]; //6λ 0x3F
private:
	bool Fun_Connect();
	void Fun_Send(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer);
	LPBYTE Fun_Send_Sync(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer);
	void Fun_Msg_Loop();
	void Fun_Receice(LPBYTE bin);
	void Fun_Handle(char* serviceCmd, const LPBYTE BodyBin, const uint sso_seq);
private:
	LPBYTE Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char* sServantName, const char* sFuncName, byte* sBuffer, uint Bufferlen);
	LPBYTE Make_Body_PC(byte* Buffer, const uint BufferLen, const bool emp);
private:
	void wtlogin_login();
	void wtlogin_login_Send_Sms();
	void wtlogin_login_Viery_Ticket(const char* Ticket);
	void wtlogin_login_Viery_Sms(const char* SmsCode);
	void wtlogin_login_Viery_204();
	void wtlogin_exchange_emp();
	void StatSvc_Register(const byte state = NULL);
	void StatSvc_SetStatusFromClient(const byte state);
	void friendlist_getFriendGroupList(const int StartIndex);
	void friendlist_GetTroopListReqV2();
	void friendlist_getTroopMemberList(const uint Group);
	bool friendlist_ModifyGroupCardReq(const uint Group, const uint QQ, const char* NewGroupCard);
	void SQQzoneSvc_getUndealCount();
	void OnlinePush_RespPush(const uint sso_seq, const LPBYTE protobuf, const int a);
	bool VisitorSvc_ReqFavorite(const uint QQ, const int Times);
	void MessageSvc_PbGetMsg();
	bool MessageSvc_PbSendMsg(const uint ToNumber, const byte ToType, const Message::Msg* Msg);
	bool PbMessageSvc_PbMsgWithDraw(const uint Group, const uint MsgId, const uint MsgId_);
	void ProfileService_Pb_ReqSystemMsgNew_Group();
	void ImgStore_GroupPicUp(const uint Group, const byte ImageMD5[16], const uint ImageLength, const uint ImageWidth, const uint ImageHeight);
	void OidbSvc_0x55c_1(const uint Group, const  uint QQ, const  bool Set);
	void OidbSvc_0x570_8(const uint Group, const  uint QQ, const  uint Time);
	std::vector<uint>* OidbSvc_0x899_0(const uint Group);
	void OidbSvc_0x89a_0(const uint Group, const  bool Ban);
	void OidbSvc_0x8a0_0(const uint Group, const  uint QQ, const  bool Forever);
	void OidbSvc_0x8fc_2(const uint Group, const  uint QQ, const  char* Title);
private:
	void Un_Tlv_Get(const unsigned short cmd, const byte* bin, const uint len);
	void Un_Pack_Body_Request_Packet(const LPBYTE BodyBin, LPBYTE& sBuffer);
	void Un_Pack_wtlogin_login(const LPBYTE BodyBin);
	void Un_Pack_OnlinePush_PbPushGroupMsg(const LPBYTE BodyBin, const uint sso_seq);
	void Un_Pack_OnlinePush_PbC2CMsgSync(const LPBYTE BodyBin, const uint sso_seq);
	void Un_Pack_OnlinePush_ReqPush(const LPBYTE BodyBin, const uint sso_seq);
	void Un_Pack_OnlinePush_PbPushTransMsg(const LPBYTE BodyBin, const uint sso_seq);
	void Un_Pack_MessageSvc_PushNotify(const LPBYTE BodyBin, const uint sso_seq);
	void Un_Pack_MessageSvc_PushForceOffline(const LPBYTE BodyBin, const uint sso_seq);
	void Un_Pack_StatSvc_SvcReqMSFLoginNotify(const LPBYTE BodyBin, const uint sso_seq);
	void Un_Pack_ConfigPushSvc_PushReq(const LPBYTE BodyBin, const uint sso_seq);
public:
	Android(const char* IMEI, const char IMSI[16], const byte GUID[16], const byte MAC[6], const char* _device, const char* Brand);
public:
	void QQ_Init(const char* Account);
	byte QQ_Login(const char* Password);
	byte QQ_Login_Second();
	byte QQ_Send_Sms();
	byte QQ_Viery_Ticket(const char* Ticket);
	byte QQ_Viery_Sms(const char* SmsCode);
	void QQ_Login_Finish();
	char* QQ_Get_Viery_Ticket();
	char* QQ_Get_Viery_PhoneNumber();
	void QQ_Online();
	void QQ_Offline();
	void QQ_SetOnlineType(const byte Type);
	void QQ_Heart_Beat();
	bool QQ_Status();
	const char* QQ_GetErrorMsg();
	void QQ_Set_Token(Android::Token* _Token);
	const Android::Token* QQ_Get_Token();
	char* QQ_GetCookies(const char* Host);
	bool QQ_SendLike(const uint QQ, const int Times);
	bool QQ_SendGroupMsg(const uint Group, const Message::Msg* Msg);
	bool QQ_DrawGroupMsg(const uint Group, const uint MsgId, const uint MsgRand);
	bool QQ_SendPrivateMsg(const uint QQ, const Message::Msg* Msg);
	bool QQ_DrawPrivateMsg(const uint Group, const uint MsgId, const uint MsgRand);
	bool QQ_KickGroupMember(const uint Group, const uint QQ, const bool Forever);
	bool QQ_SetGroupAdmin(const uint Group, const uint QQ, const bool Set);
	bool QQ_SetGroupMemberTitle(const uint Group, const uint QQ, const char* Title);
	bool QQ_SetGroupMemberCard(const uint Group, const uint QQ, const char* Card);
	bool QQ_SetGroupMemberBan(const uint Group, const uint QQ, const uint Time);
	bool QQ_SetGroupBan(const uint Group, const bool Ban);
	const std::vector<uint>* QQ_GetGroupAdminList(const uint Group);
	const std::vector<Android::FriendInfo>* QQ_GetFriendList();
	const std::vector<Android::GroupInfo>* QQ_GetGroupList();
	const std::vector<Android::GroupMemberInfo>* QQ_GetGroupMemberList(uint Group);
};