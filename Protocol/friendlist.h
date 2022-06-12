#pragma once

#include "Definition.h"
#include "../Utils/JceStruct.h"

class friendlist
{
private:
    QQ::QQ *QQ;

public:
    friendlist(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    virtual LPBYTE Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char *sServantName, const char *sFuncName, byte *sBuffer, uint Bufferlen) { return LPBYTE(); };

public:
    LPBYTE getFriendGroupList(const int StartIndex);
    LPBYTE GetTroopListReqV2();
    LPBYTE getTroopMemberList(const uint Group);
    LPBYTE ModifyGroupCardReq(const uint Group, const uint QQ, const char *NewGroupCard);
};