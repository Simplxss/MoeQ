#pragma once

#include "Defined.h"
#include "../Utils/JceStruct.h"

class StatSvc
{
private:
    QQ::QQ *QQ;
    QQ::Device *Device;

public:
    StatSvc(QQ::QQ *_QQ, QQ::Device *_Device)
    {
        QQ = _QQ;
        Device = _Device;
    };

public:
    virtual LPBYTE Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char *sServantName, const char *sFuncName, byte *sBuffer, uint Bufferlen) { return LPBYTE(); };

public:
    LPBYTE Register(const byte state = 0);
    LPBYTE SimpleGet();
    LPBYTE SetStatusFromClient(const byte state);
};