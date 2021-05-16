#pragma once

#include "Defined.h"
#include "../Utils/Protobuf.h"

class OidbSvc
{
private:
    QQ::QQ *QQ;

public:
    OidbSvc(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    LPBYTE _0x55c_1(const uint Group, const uint QQ, const bool Set);
    LPBYTE _0x570_8(const uint Group, const uint QQ, const uint Time);
    LPBYTE _0x899_0(const uint Group);
    LPBYTE _0x89a_0(const uint Group, const bool Ban);
    LPBYTE _0x8a0_0(const uint Group, const uint QQ, const bool Forever);
    LPBYTE _0x8fc_2(const uint Group, const uint QQ, const char *Title);
};
