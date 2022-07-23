#include "ImgStore.h"

LPBYTE ImgStore::GroupPicUp(const uint Group, const LPBYTE ImageName, const LPBYTE ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight)
{
    LPBYTE V = new byte[strlen(AndroidQQ_VERSION) + 4];
    memcpy(V, XBin::Int2Bin(strlen(AndroidQQ_VERSION) + 4), 4);
    memcpy(V + 4, AndroidQQ_VERSION, strlen(AndroidQQ_VERSION));

    ProtobufStruct::TreeNode Node3_19{nullptr, nullptr, 19, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node3_16{nullptr, &Node3_19, 15, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node3_15{nullptr, &Node3_16, 15, ProtobufStruct::ProtobufStructType::VARINT, (void *)1052};
    ProtobufStruct::TreeNode Node3_13{nullptr, &Node3_15, 13, ProtobufStruct::ProtobufStructType::LENGTH, V};
    ProtobufStruct::TreeNode Node3_12{nullptr, &Node3_13, 12, ProtobufStruct::ProtobufStructType::VARINT, (void *)1000};
    ProtobufStruct::TreeNode Node3_11{nullptr, &Node3_12, 11, ProtobufStruct::ProtobufStructType::VARINT, (void *)ImageHeight};
    ProtobufStruct::TreeNode Node3_10{nullptr, &Node3_11, 10, ProtobufStruct::ProtobufStructType::VARINT, (void *)ImageWidth};
    ProtobufStruct::TreeNode Node3_9{nullptr, &Node3_10, 9, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node3_8{nullptr, &Node3_9, 8, ProtobufStruct::ProtobufStructType::VARINT, (void *)9};
    ProtobufStruct::TreeNode Node3_7{nullptr, &Node3_8, 7, ProtobufStruct::ProtobufStructType::VARINT, (void *)5};
    ProtobufStruct::TreeNode Node3_6{nullptr, &Node3_7, 6, ProtobufStruct::ProtobufStructType::LENGTH, ImageName};
    ProtobufStruct::TreeNode Node3_5{nullptr, &Node3_6, 5, ProtobufStruct::ProtobufStructType::VARINT, (void *)ImageLength};
    ProtobufStruct::TreeNode Node3_4{nullptr, &Node3_5, 4, ProtobufStruct::ProtobufStructType::LENGTH, ImageMD5};
    ProtobufStruct::TreeNode Node3_3{nullptr, &Node3_4, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node3_2{nullptr, &Node3_3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)QQ->QQ};
    ProtobufStruct::TreeNode Node3_1{nullptr, &Node3_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)Group};
    ProtobufStruct::TreeNode Node3{
        &Node3_1,
        nullptr,
        3,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node2{nullptr, &Node3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)3};

    Protobuf PB;
    LPBYTE Ret = PB.Pack(&Node1);

    delete V;

    return Ret;
}