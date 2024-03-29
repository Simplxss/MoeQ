#include "ProfileService.h"

LPBYTE ProfileService::Pb_ReqSystemMsgNew_Friend()
{
    Protobuf PB;
    PB.WriteVarint(1, 20);
    PB.WriteVarint(2, 1633136467000000);
    PB.WriteVarint(3, 1659594208305346);
    PB.WriteVarint(4, 1000);
    PB.WriteVarint(5, 2);
    PB.StepIn(6);
    PB.WriteVarint(4, 1);
    PB.WriteVarint(7, 1);
    PB.WriteVarint(9, 1);
    PB.WriteVarint(10, 1);
    PB.WriteVarint(17, 1);
    PB.StepOut();
    PB.WriteVarint(8, 0);
    PB.WriteVarint(9, 0);
    PB.WriteVarint(10, 1);
    PB.WriteVarint(11, 1);

    return PB.Pack();
}

LPBYTE ProfileService::Pb_ReqSystemMsgNew_Group()
{
    Protobuf PB;
    PB.WriteVarint(1, 20);
    PB.WriteVarint(2, 1590834830000000);
    PB.WriteVarint(3, 1597344360637873);
    PB.WriteVarint(4, 1000);
    PB.WriteVarint(5, 3);
    PB.StepIn(6);
    PB.WriteVarint(1, 1);
    PB.WriteVarint(2, 1);
    PB.WriteVarint(3, 1);
    PB.WriteVarint(5, 1);
    PB.WriteVarint(6, 1);
    PB.WriteVarint(7, 1);
    PB.WriteVarint(8, 1);
    PB.WriteVarint(9, 1);
    PB.WriteVarint(11, 1);
    PB.WriteVarint(12, 1);
    PB.WriteVarint(13, 1);
    PB.WriteVarint(14, 1);
    PB.WriteVarint(15, 1);
    PB.WriteVarint(16, 1);
    PB.WriteVarint(17, 1);
    PB.StepOut();
    PB.WriteVarint(8, 0);
    PB.WriteVarint(9, 0);
    PB.WriteVarint(10, 1);
    PB.WriteVarint(11, 1);

    return PB.Pack();
}

LPBYTE ProfileService::Pb_ReqSystemMsgAction_Friend(int64_t msgSeq, uint32_t reqUin, int ReturnType)
{
    Protobuf PB;
    PB.WriteVarint(1, 1); //msgType
    PB.WriteVarint(2, msgSeq);
    PB.WriteVarint(3, reqUin);
    PB.WriteVarint(4, 1); //subType
    PB.WriteVarint(5, 6); //srcId
    PB.WriteVarint(6, 7); //subSrcId
    PB.WriteVarint(7, 0); //groupMsgType
    PB.StepIn(8);
    PB.WriteVarint(1, ReturnType == 0 ? 2 : 3);
    if (ReturnType == 0)
    {
        PB.WriteVarint(51, 0);
        PB.WriteStr(52, u8""); // remark
        PB.StepIn(54);
        PB.WriteVarint(1, 0); // notSeeDynamic
        PB.WriteVarint(2, 0); // setSn
        PB.StepOut();
    }
    else if (ReturnType == 2)
    {
        PB.WriteBool(53, true); //blacklist
    }
    PB.StepOut();
    PB.WriteVarint(9, 1000);
    return PB.Pack();
}

LPBYTE ProfileService::Pb_ReqSystemMsgAction_Group(int64_t msgSeq, uint32_t reqUin, uint32_t groupCode, bool IsInvited, int ReturnType)
{
    Protobuf PB;
    PB.WriteVarint(1, 2);
    PB.WriteVarint(2, msgSeq);
    PB.WriteVarint(3, reqUin);
    PB.WriteVarint(4, 1);
    PB.WriteVarint(5, 3);
    PB.WriteVarint(6, 30013);
    PB.WriteVarint(7, IsInvited ? 2 : 1);
    PB.StepIn(8);
    PB.WriteVarint(1, ReturnType == 0 ? 11 : 12);
    PB.WriteVarint(2, groupCode);
    PB.WriteBool(53, ReturnType == 2);
    PB.StepOut();
    PB.WriteVarint(9, 1000);
    return PB.Pack();
}
