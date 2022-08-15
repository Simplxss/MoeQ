#include "OnlinePush.h"

LPBYTE OnlinePush::RespPush(const int sso_seq, const int del_infos, const std::vector<std::tuple<int, int, LPBYTE>> info)
{
    std::vector<::Jce *> list;
    for (auto [from_uin, msg_seq, msg_cookies] : info)
    {
        Jce *Jce = new ::Jce;
        Jce->Write(from_uin, 0);      // lFromUin
        Jce->Write(0, 1);           // uMsgTime
        Jce->Write(msg_seq, 2);    // shMsgSeq
        Jce->Write(msg_cookies, 3); // vMsgCookies
        Jce->Write(0, 4);           // wCmd
        Jce->Write(0, 5);           // uMsgType
        Jce->Write(0, 6);           // uAppId
        Jce->Write(0, 7);           // lSendTime
        Jce->Write(0, 8);           // ssoSeq
        Jce->Write(0, 9);           // ssoIp
        Jce->Write(0, 10);          // clientIp
        list.emplace_back(Jce);
    }

    ::Jce Jce;
    Jce.Write(QQ->QQ, 0);
    Jce.Write(&list, 1);
    Jce.Write(del_infos, 2);
    Jce.Write(0, 4);

    Jce.Write(&Jce, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"resp", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;
    
    for (size_t i = 0; i < list.size(); i++)
        delete list[i];


    uint len = Jce.GetAll(bin);
    return Make_Body_Request_Packet(3, sso_seq, "OnlinePush", "SvcRespPushMsg", bin, len);
}