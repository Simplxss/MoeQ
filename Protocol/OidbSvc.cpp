#include "OidbSvc.h"

/// <summary>
/// 设置管理员
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Set"></param>
LPBYTE OidbSvc::_0x55c_1(const uint Group, const uint QQ, const bool Set)
{
    Pack Pack(9);
    Pack.SetInt(Group);
    Pack.SetInt(QQ);
    Pack.SetByte(Set);

    Protobuf PB;
    PB.WriteVarint(1, 1372);
    PB.WriteVarint(2, 1);
    PB.WriteBin_(4, Pack.GetAll(), 9);
    return PB.Pack();
    ;
    ;
}

/// <summary>
/// 群禁言(Time为0时解除禁言)
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Time">单位:秒</param>
LPBYTE OidbSvc::_0x570_8(const uint Group, const uint QQ, const uint Time)
{
    Pack Pack(15);
    Pack.SetInt(Group);
    Pack.SetBin((byte *)"\x20\0\1", 3);
    Pack.SetInt(QQ);
    Pack.SetInt(Time);

    Protobuf PB;
    PB.WriteVarint(1, 1392);
    PB.WriteVarint(2, 8);
    PB.WriteVarint(3, 0);
    PB.WriteBin_(4, Pack.GetAll(), 15);
    return PB.Pack();
}

/// <summary>
/// 取管理员列表(包括群主)
/// </summary>
/// <param name="Group"></param>
LPBYTE OidbSvc::_0x899_0(const uint Group)
{
    Protobuf PB;
    PB.WriteVarint(1, 2201);
    PB.WriteVarint(2, 0);
    PB.StepIn(4);
    PB.WriteVarint(1, Group);
    PB.WriteVarint(2, 0);
    PB.WriteVarint(3, 2);
    PB.StepIn(5);
    PB.WriteVarint(1, 0);
    PB.WriteVarint(3, 1);
    PB.StepOut();
    PB.StepOut();
    return PB.Pack();
}

/// <summary>
/// 全体禁言(解禁)
/// </summary>
/// <param name="Group"></param>
/// <param name="Ban"></param>
LPBYTE OidbSvc::_0x89a_0(const uint Group, const bool Ban)
{
    Protobuf PB;
    PB.WriteVarint(1, 2202);
    PB.WriteVarint(2, 0);
    PB.WriteVarint(3, 0);
    PB.StepIn(4);
    PB.WriteVarint(1, Group);
    PB.StepIn(2);
    PB.WriteVarint(17, Ban ? 268435455 : 0);
    PB.StepOut();
    PB.StepOut();
    return PB.Pack();
}

/// <summary>
/// 群踢人
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Forever">不再接收加群申请</param>
LPBYTE OidbSvc::_0x8a0_0(const uint Group, const uint QQ, const bool Forever)
{
    Protobuf PB;
    PB.WriteVarint(1, 2208);
    PB.WriteVarint(2, 0);
    PB.WriteVarint(3, 0);
    PB.StepIn(4);
    PB.WriteVarint(1, Group);
    PB.StepIn(2);
    PB.WriteVarint(1, 5);
    PB.WriteVarint(2, QQ);
    PB.WriteVarint(3, Forever);
    PB.StepOut();
    PB.StepOut();
    return PB.Pack();
}

/// <summary>
/// 设置专属头衔
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Title">为空即收回</param>
LPBYTE OidbSvc::_0x8fc_2(const uint Group, const uint QQ, const char8_t *Title)
{
    Protobuf PB;
    PB.WriteVarint(1, 2300);
    PB.WriteVarint(2, 2);
    PB.StepIn(4);
    PB.WriteVarint(1, Group);
    PB.StepIn(3);
    PB.WriteVarint(1, QQ);
    PB.WriteStr(5, Title);
    PB.WriteVarint(6, -1);
    PB.WriteStr(7, Title);
    PB.StepOut();
    PB.StepOut();
    return PB.Pack();
}
