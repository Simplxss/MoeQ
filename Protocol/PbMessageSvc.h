#pragma once

#include "Definition.h"
#include "../Utils/Protobuf.h"

class PbMessageSvc
{
private:
    QQ::QQ *QQ;

public:
    PbMessageSvc(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    LPBYTE PbMsgWithDraw(const uint Target, const uint MsgId, const uint MsgRand);
};
