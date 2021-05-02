#pragma once

#include "../Utils/JceStruct.h"
#include "Tlv.h"
#include "../Utils/ThreadPool.h"
#include "../PluginSystem/PluginSystem.h"

#include <ctime>

#define QQ_APPID 537066978
#define QQ_VERSION "8.5.5"
#define QQ_VERSION_ "A8.5.5.de12fadd"
#define QQ_APKID "com.tencent.mobileqq"
#define QQ_ASIG (const byte *)"\xA6\xB7\x45\xBF\x24\xA2\xC2\x77\x52\x77\x16\xF6\xF3\x6E\xB6\x8D" // A6B745BF24A2C277527716F6F36EB68D
#define QQ_SDK_VERSION "6.0.0.2463"
#define QQ_BUILDTIME 1612895972

#define LOGIN_SUCCESS 0
#define LOGIN_VERIY 2
#define LOGIN_VERIY_SMS 160

class Android
{
public:
    struct Token
    {
        byte *A2 = nullptr; //64
        byte *A5 = nullptr;
        byte *A8 = nullptr;
        byte *D2Key = nullptr;              //16
        byte *wtSessionTicket = nullptr;    //48
        byte *wtSessionTicketKey = nullptr; //16
        byte *StSig = nullptr;
        byte *StKey = nullptr;
        byte *token_16A = nullptr; //56
        byte *md5 = nullptr;       //16
        byte *md52 = nullptr;      //16
        byte *TGT = nullptr;       //72
        byte *TGTkey = nullptr;    //16
        byte *ksid = nullptr;      //16
    };
    struct FriendInfo
    {
        uint QQ;
        char *Nick;
        int status;
        char *Remark;
    };
    struct GroupMemberInfo
    {
        uint QQ;
        char *Nick;
    };
    struct GroupInfo
    {
        uint GroupCode;
        char *GroupName;
        uint MasterQQ;
        short MemberCount;
        byte SelfIdentity;
    };

private:
    struct Login
    {
        Utils::ECDHKEY ECDH;
        byte *RandKey = nullptr;
        byte *VieryToken1 = nullptr;
        byte *VieryToken2 = nullptr;
        byte *ClientPow = nullptr;
        byte *token_402 = nullptr; //8
        byte *token_403 = nullptr; //8
        byte *Viery_Image = nullptr;
        char *Viery_Ticket = nullptr;
        char *PhoneNumber = nullptr;
        char *SmsToken = nullptr;
        int state = 0;
    };
    struct p_skey
    {
        char *host;
        char *p_skey;
    };
    struct Cookie
    {
        byte *StWebSig = nullptr;
        byte *sid = nullptr;
        char *skey = nullptr;
        char *vkey = nullptr;
        char *superKey = nullptr;
        std::vector<Android::p_skey> p_skey;
    };
    struct QQ
    {
        uint QQ;
        char *QQ_Str = nullptr;
        char8_t *Nick = nullptr;
        byte Status = 21;
        char8_t *ErrorMsg = nullptr;
        std::atomic_int SsoSeq;
        unsigned char *MsgCookie = nullptr; //4
        LPBYTE SyncCookies = nullptr;
        char Version[33] = "|\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0|" QQ_VERSION_;
        Android::Login *Login = nullptr;
        Android::Token Token;
        Android::Cookie Cookie;

        std::vector<Android::FriendInfo> FriendList;
        std::vector<Android::GroupInfo> GroupList; //不包含被封群
    };
    struct Device
    {
        char *IMEI = nullptr;
        char *IMSI = nullptr;
        byte *MAC = nullptr;
        char *IP = nullptr;
        byte *GUID = nullptr;
        char *_device = nullptr;
        char *Brand = nullptr;
        unsigned short _network_type;
        const char *QIMEI = nullptr; //算法未知 在so层中
        const char *BSSID = nullptr;
        const char *os_type = nullptr;
        const char *os_version = nullptr;
        const char *_apn = nullptr;
        const char *NetworkName = nullptr;
        const char *WiFiName = nullptr;
    };
    struct SenderInfo
    {
        std::condition_variable cv;
        std::condition_variable *condition_variable;
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
    Android(const char *IMEI, const char IMSI[16], const byte GUID[16], const byte MAC[6], const char *_device, const char *Brand);

private:
    bool Fun_Connect(const char *IP = nullptr, const unsigned short Port = 0);
    int Fun_Send(const uint PacketType, const byte EncodeType, const char *ServiceCmd, LPBYTE Buffer);
    /// <summary>
    /// Send package synchronously
    /// </summary>
    /// <typeparam name="R"></typeparam>
    /// <param name="PacketType"></param>
    /// <param name="EncodeType"></param>
    /// <param name="ServiceCmd"></param>
    /// <param name="Buffer">会自动销毁</param>
    /// <param name="Function"></param>
    /// <returns></returns>
    template <typename R>
    std::enable_if<!std::is_void<R>::value, R>::type Fun_Send_Sync(const uint PacketType, const byte EncodeType, const char *ServiceCmd, LPBYTE Buffer, std::function<R(uint, LPBYTE)> Function)
    {
        std::mutex lock;
        std::unique_lock<std::mutex> ulock(lock);

        int SsoSeq = Fun_Send(PacketType, EncodeType, ServiceCmd, Buffer);

        SendList[SsoSeq & 0x3F].cv.wait(ulock);
        std::condition_variable *condition_variable = SendList[SsoSeq & 0x3F].condition_variable;
        try
        {
            R ret = Function(SsoSeq, SendList[SsoSeq & 0x3F].BodyBin);

            condition_variable->notify_one();
            return ret;
        }
        catch (std::exception e)
        {
            condition_variable->notify_one();
        }
    };
    void Fun_Send_Sync(const uint PacketType, const byte EncodeType, const char *ServiceCmd, LPBYTE Buffer, std::function<void(uint, LPBYTE)> Function)
    {
        std::mutex lock;
        std::unique_lock<std::mutex> ulock(lock);

        int SsoSeq = Fun_Send(PacketType, EncodeType, ServiceCmd, Buffer);

        SendList[SsoSeq & 0x3F].cv.wait(ulock);
        std::condition_variable *condition_variable = SendList[SsoSeq & 0x3F].condition_variable;
        try
        {
            Function(SsoSeq, SendList[SsoSeq & 0x3F].BodyBin);
        }
        catch (std::exception e)
        {
        }
        condition_variable->notify_one();
    };
    void Fun_Msg_Loop();
    void Fun_Receice(LPBYTE bin);
    void Fun_Handle(char *serviceCmd, const LPBYTE BodyBin, const uint sso_seq);
    void Fun_Life_Event();

private:
    LPBYTE Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char *sServantName, const char *sFuncName, byte *sBuffer, uint Bufferlen);
    LPBYTE Make_Body_PC(byte *Buffer, const uint BufferLen, const bool emp);

private:
    void wtlogin_login();
    void wtlogin_login_Send_Sms();
    void wtlogin_login_Viery_Ticket(const char *Ticket);
    void wtlogin_login_Viery_Sms(const char *SmsCode);
    void wtlogin_login_Viery_204();
    void wtlogin_exchange_emp();
    void StatSvc_Register(const byte state = 0);
    void StatSvc_SimpleGet();
    void StatSvc_SetStatusFromClient(const byte state);
    void friendlist_getFriendGroupList(const int StartIndex);
    void friendlist_GetTroopListReqV2();
    void friendlist_getTroopMemberList(const uint Group);
    bool friendlist_ModifyGroupCardReq(const uint Group, const uint QQ, const char *NewGroupCard);
    void SQQzoneSvc_getUndealCount();
    void OnlinePush_RespPush(const LPBYTE protobuf, const int a);
    bool VisitorSvc_ReqFavorite(const uint QQ, const int Times);
    void MessageSvc_PbGetMsg();
    bool MessageSvc_PbSendMsg(const uint ToNumber, const byte ToType, const Message::Msg *Msg);
    bool PbMessageSvc_PbMsgWithDraw(const uint Group, const uint MsgId, const uint MsgId_);
    void ProfileService_Pb_ReqSystemMsgNew_Group();
    std::tuple<uint, uint, uint, LPBYTE> ImgStore_GroupPicUp(const uint Group, const LPBYTE ImageName, const LPBYTE ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight);
    bool PicUp_DataUp(const uint Group, const byte *TotalData, const uint TotalDataLength, const LPBYTE TotalDataMD5, const int DataType, const uint IP, const uint Port, const LPBYTE sig);
    void OidbSvc_0x55c_1(const uint Group, const uint QQ, const bool Set);
    void OidbSvc_0x570_8(const uint Group, const uint QQ, const uint Time);
    std::vector<uint> *OidbSvc_0x899_0(const uint Group);
    void OidbSvc_0x89a_0(const uint Group, const bool Ban);
    void OidbSvc_0x8a0_0(const uint Group, const uint QQ, const bool Forever);
    void OidbSvc_0x8fc_2(const uint Group, const uint QQ, const char *Title);

private:
    void Un_Tlv_Get(const unsigned short cmd, const byte *bin, const uint len);
    void Unpack_Body_Request_Packet(const LPBYTE BodyBin, LPBYTE &sBuffer);
    void Unpack_wtlogin_login(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_OnlinePush_PbPushGroupMsg(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_OnlinePush_PbC2CMsgSync(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_OnlinePush_ReqPush(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_OnlinePush_PbPushTransMsg(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_MessageSvc_PushNotify(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_MessageSvc_PushForceOffline(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_StatSvc_SvcReqMSFLoginNotify(const LPBYTE BodyBin, const uint sso_seq);
    void Unpack_ConfigPushSvc_PushReq(const LPBYTE BodyBin, const uint sso_seq);

public:
    void QQ_Init(const char *Account);
    int QQ_Login(const char *Password);
    int QQ_Login_Second();
    void QQ_Login_Finish();
    byte QQ_Send_Sms();
    byte QQ_Viery_Ticket(const char *Ticket);
    byte QQ_Viery_Sms(const char *SmsCode);
    char *QQ_Get_Viery_Ticket();
    char *QQ_Get_Viery_PhoneNumber();
    void QQ_Online();
    void QQ_Offline();
    void QQ_SetOnlineType(const byte Type);
    void QQ_Heart_Beat();
    void QQ_SyncCookie();
    bool QQ_Status();
    const char8_t *QQ_GetErrorMsg();
    void QQ_Set_Token(Android::Token *_Token);
    const Android::Token *QQ_Get_Token();
    const uint QQ_Get_Account();
    char *QQ_GetCookies(const char *Host);
    bool QQ_SendLike(const uint QQ, const int Times);
    bool QQ_SendGroupMsg(const uint Group, const Message::Msg *Msg);
    bool QQ_DrawGroupMsg(const uint Group, const uint MsgId, const uint MsgRand);
    bool QQ_SendPrivateMsg(const uint QQ, const Message::Msg *Msg);
    bool QQ_DrawPrivateMsg(const uint Group, const uint MsgId, const uint MsgRand);
    bool QQ_SendDisscussMsg(const uint Disscuss, const Message::Msg *Msg);
    bool QQ_KickGroupMember(const uint Group, const uint QQ, const bool Forever);
    bool QQ_SetGroupAdmin(const uint Group, const uint QQ, const bool Set);
    bool QQ_SetGroupMemberTitle(const uint Group, const uint QQ, const char *Title);
    bool QQ_SetGroupMemberCard(const uint Group, const uint QQ, const char *Card);
    bool QQ_SetGroupMemberBan(const uint Group, const uint QQ, const uint Time);
    bool QQ_SetGroupBan(const uint Group, const bool Ban);
    const std::vector<uint> *QQ_GetGroupAdminList(const uint Group);
    const std::vector<Android::FriendInfo> *QQ_GetFriendList();
    const std::vector<Android::GroupInfo> *QQ_GetGroupList();
    const std::vector<Android::GroupMemberInfo> *QQ_GetGroupMemberList(uint Group);
};