#pragma once

#include "../Utils/JceStruct.h"
#include "../Utils/ThreadPool.h"
#include "../PluginSystem/PluginSystem.h"

#include "wtlogin.h"
#include "StatSvc.h"
#include "friendlist.h"
#include "OidbSvc.h"
#include "MessageSvc.h"
#include "PbMessageSvc.h"
#include "OnlinePush.h"
#include "ImgStore.h"
#include "LongConn.h"
#include "pttTrans.h"
#include "PicUp.h"
#include "SQQzoneSvc.h"
#include "VisitorSvc.h"
#include "ProfileService.h"

#include <ctime>

#define LOGIN_SUCCESS 0
#define LOGIN_VERIY 2
#define LOGIN_VERIY_SMS 160

class Android : private wtlogin, private StatSvc, private friendlist, private OidbSvc, private MessageSvc, private PbMessageSvc, private OnlinePush, private ImgStore, private LongConn, private pttTrans, private PicUp, private SQQzoneSvc, private VisitorSvc, private ProfileService
{
private:
    struct SenderInfo
    {
        std::condition_variable cv;
        std::condition_variable *condition_variable;
        LPBYTE BodyBin;
    };

private:
    QQ::QQ QQ;
    QQ::Device Device;
    Socket TCP;
    ThreadPool HandleThreads;
    SenderInfo SendList[64]; // 0x3F

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
        return R();
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
    
private:
    void Un_Tlv_Get(const unsigned short cmd, const byte *bin, const uint len);
    void Unpack_Body_Request_Packet(const LPBYTE BodyBin, LPBYTE &sBuffer);
    void Unpack_wtlogin(const LPBYTE BodyBin, const uint sso_seq);
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
    void QQ_SetOnlineType(const byte Type = 0);
    void QQ_Heart_Beat();
    void QQ_SyncCookie();
    void QQ_SyncFriendList(int startIndex);
    void QQ_SyncGroupList();
    void QQ_SyncGroupMemberList(uint Group);
    void QQ_SyncGroupAdminList(uint Group);
    bool QQ_Status();
    const char8_t *QQ_GetErrorMsg();
    void QQ_Set_Token(QQ::Token *_Token);
    const QQ::Token *QQ_Get_Token();
    std::tuple<bool, char8_t *, char8_t *> QQ_UploadImage_Private(const uint QQ, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight, const byte *Image = nullptr);
    uint QQ_UploadImage_Group(const uint Group, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight, const byte *Image = nullptr);
    void QQ_UploadPtt_Private(const uint QQ_, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Image);
    void QQ_UploadPtt_Group(const uint Group, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Image);
    void QQ_TranslatePtt_Private(const uint QQ_, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Image);
    void QQ_TranslatePtt_Group(const uint Group, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Image);
    uint QQ_Get_Account();
    char *QQ_GetCookies(const char *Host);
    bool QQ_SendLike(const uint QQ, const int Times);
    bool QQ_SendMsg(const int ToNumber, const uint ToType, const Message::Msg *Msg);
    bool QQ_DrawGroupMsg(const uint Group, const uint MsgId, const uint MsgRand);
    bool QQ_DrawPrivateMsg(const uint Group, const uint MsgId, const uint MsgRand);
    bool QQ_KickGroupMember(const uint Group, const uint QQ, const bool Forever);
    bool QQ_SetGroupAdmin(const uint Group, const uint QQ, const bool Set);
    bool QQ_SetGroupMemberTitle(const uint Group, const uint QQ, const char8_t *Title);
    bool QQ_SetGroupMemberCard(const uint Group, const uint QQ, const char *Card);
    bool QQ_SetGroupMemberBan(const uint Group, const uint QQ, const uint Time);
    bool QQ_SetGroupBan(const uint Group, const bool Ban);
    const std::vector<QQ::FriendInfo> *QQ_GetFriendList();
    const std::vector<QQ::GroupInfo> *QQ_GetGroupList();
    const std::vector<QQ::GroupMemberInfo> *QQ_GetGroupMemberList(uint Group);
    const std::vector<uint> *QQ_GetGroupAdminList(const uint Group);
};