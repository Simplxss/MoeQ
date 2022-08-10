#pragma once

#include "Definition.h"
#include "../Utils/Protobuf.h"
#include "../Utils/JceStruct.h"

class OnlinePush
{
private:
    QQ::QQ *QQ;

public:
    OnlinePush(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

private:
    virtual LPBYTE Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char *sServantName, const char *sFuncName, byte *sBuffer, uint Bufferlen) { return LPBYTE(); };

public:
    LPBYTE RespPush(const int sso_seq, const int del_infos, const std::vector<std::tuple<int, LPBYTE>> info)
};
