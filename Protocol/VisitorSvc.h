#pragma once

#include "Definition.h"
#include "../Utils/JceStruct.h"

class VisitorSvc
{
private:
    QQ::QQ *QQ;

public:
    VisitorSvc(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };
    
private:
    virtual LPBYTE Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char *sServantName, const char *sFuncName, byte *sBuffer, uint Bufferlen) { return LPBYTE(); };

public:
    LPBYTE ReqFavorite(const uint QQ, const int Times);
};
