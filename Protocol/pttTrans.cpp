#include "pttTrans.h"

LPBYTE pttTrans::TransC2CPttReq(const uint QQ_, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime)
{
    Protobuf PB;
    PB.WriteVarint(1, 2);
    PB.StepIn(2);
    PB.WriteVarint(1, );
    PB.WriteVarint(2, QQ_);
    PB.WriteVarint(3, QQ->QQ);
    PB.WriteStr(4, );
    PB.WriteVarint(5, PttTime);
    PB.WriteVarint(6, PttLength);
    PB.WriteVarint(7, 1);
    PB.WriteVarint(8, 2);
    PB.WriteStr(9, (char8_t *)XBin::Bin2HexEx(PttMD5, 16));
    PB.WriteVarint(10, 0);
    PB.WriteVarint(11, 0);
    PB.StepOut();
    PB.WriteVarint(10, 1);
    return PB.Pack();
}

LPBYTE pttTrans::TransGroupPttReq(const uint Group, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime)
{
    Protobuf PB;
    PB.WriteVarint(1, 1);
    PB.StepIn(2);
    PB.WriteVarint(1, );
    PB.WriteVarint(2, QQ->QQ);
    PB.WriteVarint(3, Group);
    PB.WriteVarint(4, 1);
    PB.WriteStr(5, PttMD5);
    PB.WriteVarint(6, PttTime);
    PB.WriteVarint(7, PttLength);
    PB.WriteVarint(8, 1);
    PB.WriteStr(9, );
    PB.WriteVarint(10, 2);
    PB.WriteVarint(11, 0);
    PB.WriteVarint(12, 0);
    PB.StepOut();
    PB.WriteVarint(10, 1);
    return PB.Pack();
}