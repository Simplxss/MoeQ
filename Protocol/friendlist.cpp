#include "friendlist.h"

LPBYTE friendlist::getFriendGroupList(const int StartIndex)
{
    Jce Jce;
    Jce.Write(3, 0);
    Jce.Write(1, 1);
    Jce.Write(QQ->QQ, 2);
    Jce.Write(StartIndex, 3); //开始数
    Jce.Write(20, 4);         //获取个数
    Jce.Write(0, 5);
    Jce.Write(1, 6);
    Jce.Write(0, 7);
    Jce.Write(0, 8);
    Jce.Write(0, 9);
    Jce.Write(1, 10);
    Jce.Write(5, 11);

    Jce.Write(&Jce, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"FL", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce.GetAll(bin);

    return Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "GetFriendListReq", bin, len);
}

LPBYTE friendlist::GetTroopListReqV2()
{
    Jce Jce;
    Jce.Write(QQ->QQ, 0);
    Jce.Write(0, 1);
    Jce.Write(1, 4);
    Jce.Write(5, 5);

    Jce.Write(&Jce, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"GetTroopListReqV2Simplify", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce.GetAll(bin);

    return Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "GetTroopListReqV2Simplify", bin, len);
}

LPBYTE friendlist::getTroopMemberList(const uint Group)
{
    Jce Jce;
    Jce.Write(QQ->QQ, 0);
    Jce.Write(Group, 1);
    Jce.Write(0, 2);
    Jce.Write(Group, 3);
    Jce.Write(2, 4);
    Jce.Write(1, 5);
    Jce.Write(0, 6);
    Jce.Write(1, 7);

    Jce.Write(&Jce, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"GTML", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce.GetAll(bin);

    return Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "GetFriendListReq", bin, len);
}

LPBYTE friendlist::ModifyGroupCardReq(const uint Group, const uint QQ, const char *NewGroupCard)
{
    Jce Jce,Jce_;
    Jce.Write(QQ, 0);
    Jce.Write(1, 1);
    Jce.Write(NewGroupCard, 2);
    Jce.Write(255, 3);
    Jce.Write("", 4);
    Jce.Write("", 5);
    Jce.Write("", 6);

    const std::vector<::Jce *> list{&Jce};
    
    Jce_.Write(0, 0);
    Jce_.Write(Group, 1);
    Jce_.Write(0, 2);
    Jce_.Write(&list, 3);

    Jce.Write(&Jce_, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"MGCREQ", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce.GetAll(bin);
    return Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "ModifyGroupCardReq", bin, len);
}
