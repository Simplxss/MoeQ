#include "OnlinePush.h"

LPBYTE OnlinePush::RespPush(const int sso_seq, const int del_infos, const std::vector<std::tuple<int, LPBYTE>> info)
{
    std::vector<::Jce *> list;
    for (auto [shMsgSeq, vMsgCookies] : info)
    {
        Jce *Jce = new ::Jce;
        Jce->Write(QQ->QQ, 0);      // lFromUin
        Jce->Write(0, 1);           // uMsgTime
        Jce->Write(shMsgSeq, 2);    // shMsgSeq
        Jce->Write(vMsgCookies, 3); // vMsgCookies
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

    ::Jce Jce_;
    Jce_.Write(&Jce, 0);
    LPBYTE bin = Jce_.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"resp", bin}};
    Jce.Write(&JceMap, 0);
    for (size_t i = 0; i < list.size(); i++)
        delete list[i];

    delete[] bin;

    uint len = Jce.GetAll(bin);
    return Make_Body_Request_Packet(2, sso_seq, "OnlinePush", "SvcRespPushMsg", bin, len);
}