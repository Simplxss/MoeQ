#include "OnlinePush.h"

LPBYTE OnlinePush::RespPush(const LPBYTE vMsgCookies, const int del_infos)
{
    Jce Jce;
    Jce.Write(QQ->QQ, 0);    // lFromUin
    Jce.Write(0, 1);        // uMsgTime
    Jce.Write(24042, 2);    // shMsgSeq
    Jce.Write(vMsgCookies, 3); // vMsgCookies
    Jce.Write(0, 4);        // wCmd
    Jce.Write(0, 5);        // uMsgType
    Jce.Write(0, 6);        // uAppId
    Jce.Write(0, 7);        // lSendTime
    Jce.Write(0, 8);        // ssoSeq
    Jce.Write(0, 9);        // ssoIp
    Jce.Write(0, 10);       // clientIp

    const std::vector<::Jce *> list{&Jce};

    ::Jce Jce_;
    Jce_.Write(QQ->QQ, 0);
    Jce_.Write(&list, 1);
    Jce_.Write(del_infos, 2); // unknow
    Jce_.Write(0, 4);

    Jce.Write(&Jce_, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"resp", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce.GetAll(bin);
    return Make_Body_Request_Packet(3, 0, "OnlinePush", "SvcRespPushMsg", bin, len);
}