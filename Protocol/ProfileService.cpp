#include "ProfileService.h"


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

//ProfileService.Pb.ReqSystemMsgNew.Group
    return PB.Pack();
}
