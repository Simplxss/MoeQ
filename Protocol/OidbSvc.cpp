#include "OidbSvc.h"

/// <summary>
/// 设置管理员
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Set"></param>
LPBYTE OidbSvc::_0x55c_1(const uint Group, const uint QQ, const bool Set)
{
    Pack Pack(13, true);
    Pack.SetInt(Group);
    Pack.SetInt(QQ);
    Pack.SetByte(Set);
    Pack.SetLength();

    ProtobufStruct::TreeNode Node4{nullptr, nullptr, 4, ProtobufStruct::ProtobufStructType::LENGTH, Pack.GetAll()};
    ProtobufStruct::TreeNode Node2{nullptr, &Node4, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)1372};

    Protobuf PB;
    return PB.Pack(&Node1);
}

/// <summary>
/// 群禁言(Time为0时解除禁言)
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Time">单位:秒</param>
LPBYTE OidbSvc::_0x570_8(const uint Group, const uint QQ, const uint Time)
{
    Pack Pack(19, true);
    Pack.SetInt(Group);
    Pack.SetBin((byte *)"\x20\0\1", 3);
    Pack.SetInt(QQ);
    Pack.SetInt(Time);
    Pack.SetLength();
    
    ProtobufStruct::TreeNode Node4{nullptr, nullptr, 4, ProtobufStruct::ProtobufStructType::LENGTH, Pack.GetAll()};
    ProtobufStruct::TreeNode Node3{nullptr, &Node4, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node2{nullptr, &Node3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)8};
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)1392};

    Protobuf PB;
    return PB.Pack(&Node1);
}

/// <summary>
/// 取管理员列表(包括群主)
/// </summary>
/// <param name="Group"></param>
LPBYTE OidbSvc::_0x899_0(const uint Group)
{
    ProtobufStruct::TreeNode Node4_5_3{nullptr, nullptr, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node4_5_1{nullptr, &Node4_5_3, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node4_5{
        &Node4_5_1,
        nullptr,
        5,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node4_3{nullptr, &Node4_5, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)2};
    ProtobufStruct::TreeNode Node4_2{nullptr, &Node4_3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node4_1{nullptr, &Node4_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)Group};
    ProtobufStruct::TreeNode Node4{
        &Node4_1,
        nullptr,
        4,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node2{nullptr, &Node4, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)2201};

    Protobuf PB;
    return PB.Pack(&Node1);
}

/// <summary>
/// 全体禁言(解禁)
/// </summary>
/// <param name="Group"></param>
/// <param name="Ban"></param>
LPBYTE OidbSvc::_0x89a_0(const uint Group, const bool Ban)
{
    ProtobufStruct::TreeNode Node4_2_17{nullptr, nullptr, 17, ProtobufStruct::ProtobufStructType::VARINT, (void *)(Ban ? 268435455 : 0)};
    ProtobufStruct::TreeNode Node4_2{
        &Node4_2_17,
        nullptr,
        2,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node4_1{nullptr, &Node4_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)Group};
    ProtobufStruct::TreeNode Node4{
        &Node4_1,
        nullptr,
        4,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node3{nullptr, &Node4, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node2{nullptr, &Node3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)2202};

    Protobuf PB;
    return PB.Pack(&Node1);
}

/// <summary>
/// 群踢人
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Forever">不再接收加群申请</param>
LPBYTE OidbSvc::_0x8a0_0(const uint Group, const uint QQ, const bool Forever)
{
    ProtobufStruct::TreeNode Node4_2_3{nullptr, nullptr, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)Forever};
    ProtobufStruct::TreeNode Node4_2_2{nullptr, &Node4_2_3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)QQ};
    ProtobufStruct::TreeNode Node4_2_1{nullptr, &Node4_2_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)5};
    ProtobufStruct::TreeNode Node4_2{
        &Node4_2_1,
        nullptr,
        2,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node4_1{nullptr, &Node4_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)Group};
    ProtobufStruct::TreeNode Node4{
        &Node4_1,
        nullptr,
        4,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node3{nullptr, &Node4, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node2{nullptr, &Node3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)2208};

    Protobuf PB;
    return PB.Pack(&Node1);
}

/// <summary>
/// 设置专属头衔
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Title">为空即收回</param>
LPBYTE OidbSvc::_0x8fc_2(const uint Group, const uint QQ, const char *Title)
{
    uint len = strlen(Title);
    LPBYTE T = new byte[len + 4];
    memcpy(T, XBin::Int2Bin(len + 4), 4);
    memcpy(T + 4, Title, len);

    ProtobufStruct::TreeNode Node4_3_7{
        nullptr,
        nullptr,
        7,
        ProtobufStruct::ProtobufStructType::LENGTH,T
    };
    ProtobufStruct::TreeNode Node4_3_6{nullptr, &Node4_3_7, 6, ProtobufStruct::ProtobufStructType::VARINT, (void *)-1};
    ProtobufStruct::TreeNode Node4_3_5{nullptr, &Node4_3_6, 5, ProtobufStruct::ProtobufStructType::LENGTH, T};
    ProtobufStruct::TreeNode Node4_3_1{nullptr, &Node4_3_5, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)QQ};
    ProtobufStruct::TreeNode Node4_3{
        &Node4_3_1,
        nullptr,
        3,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node4_1{nullptr, &Node4_3, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)Group};
    ProtobufStruct::TreeNode Node4{
        &Node4_1,
        nullptr,
        4,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node2{nullptr, &Node4, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)2};
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)2300};

    Protobuf PB;
    return PB.Pack(&Node1);
}
