#pragma once

#include "Definition.h"
#include "../Utils/Protobuf.h"

class pttTrans
{
private:
    QQ::QQ *QQ;

public:
    pttTrans(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    LPBYTE TransC2CPttReq(const uint QQ_, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime);
    LPBYTE TransGroupPttReq(const uint Group, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime);
};