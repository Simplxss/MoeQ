#include "PbMessageSvc.h"

LPBYTE PbMessageSvc::PbMsgWithDraw(const uint Target, const uint MsgId, const uint MsgRand)
{
    Protobuf PB;
    PB.StepIn(2);
    PB.WriteVarint(1, 1);
    PB.WriteVarint(2, 0);
    PB.WriteVarint(3, Target);
    PB.StepIn(4);
    PB.WriteVarint(1, MsgId);
    PB.WriteVarint(2, MsgRand);
    PB.StepOut();
    PB.StepIn(5);
    PB.WriteVarint(1, 0);
    PB.StepOut();
    PB.StepOut();
    return PB.Pack();
}