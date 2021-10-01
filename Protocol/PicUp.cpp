#include "PicUp.h"

/// <summary>
/// 上传文件
/// </summary>
/// <param name="Group">如不是群聊,此参数填NULL</param>
/// <param name="TotalData"></param>
/// <param name="TotalDataLength"></param>
/// <param name="TotalDataMD5"></param>
/// <param name="DataType">Image 2, Voice 29</param>
/// <param name="IP"></param>
/// <param name="Port"></param>
/// <param name="sig"></param>
/// <returns></returns>
bool PicUp::DataUp(const uint Group, const byte *TotalData, const uint TotalDataLength, const LPBYTE TotalDataMD5, const int DataType, const uint IP, const uint Port, const LPBYTE sig)
{
    Socket TCP;

    char *ip = XBin::Int2IP(IP);
    if (!TCP.Connect(ip, Port))
    {
        Log::AddLog(Log::LogType::NOTICE, Log::MsgType::OTHER, u8"Upload", u8"Connect upload server false");
        return false;
    };
    delete[] ip;

    //文件分片发送
    uint Offset = 0, DataLength, Length;
    Protobuf PB;
    LPBYTE Bin;
    Pack Pack(8500, false);
    while ((DataLength = TotalDataLength - Offset) > 0)
    {
        if (DataLength > 0x2000)
            DataLength = 0x2000;

        ProtobufStruct::TreeNode Node2_9{nullptr, nullptr, 9, ProtobufStruct::ProtobufStructType::LENGTH, TotalDataMD5};
        ProtobufStruct::TreeNode Node2_8{nullptr, &Node2_9, 8, ProtobufStruct::ProtobufStructType::LENGTH, Utils::MD5EX(TotalData + Offset, DataLength)};
        ProtobufStruct::TreeNode Node2_6{nullptr, &Node2_8, 6, ProtobufStruct::ProtobufStructType::LENGTH, sig};
        ProtobufStruct::TreeNode Node2_4{nullptr, &Node2_6, 4, ProtobufStruct::ProtobufStructType::VARINT, (void *)DataLength};
        ProtobufStruct::TreeNode Node2_3{nullptr, &Node2_4, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node2_2{nullptr, &Node2_3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)TotalDataLength};
        ProtobufStruct::TreeNode Node2{
            &Node2_2,
            nullptr,
            2,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        ProtobufStruct::TreeNode Node1_10{nullptr, nullptr, 10, ProtobufStruct::ProtobufStructType::VARINT, (void *)2052};
        ProtobufStruct::TreeNode Node1_8{nullptr, &Node1_10, 8, ProtobufStruct::ProtobufStructType::VARINT, (void *)DataType};
        ProtobufStruct::TreeNode Node1_7{nullptr, &Node1_8, 7, ProtobufStruct::ProtobufStructType::VARINT, (void *)4096};
        ProtobufStruct::TreeNode Node1_6{nullptr, &Node1_7, 6, ProtobufStruct::ProtobufStructType::VARINT, (void *)AndroidQQ_APPID};
        ProtobufStruct::TreeNode Node1_5{nullptr, &Node1_6, 5, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node1_4{nullptr, &Node1_5, 4, ProtobufStruct::ProtobufStructType::VARINT, (void *)83048};
        ProtobufStruct::TreeNode Node1_3{nullptr, &Node1_4, 3, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x10PicUp.DataUp"};
        ProtobufStruct::TreeNode Node1_2{nullptr, &Node1_3, 2, ProtobufStruct::ProtobufStructType::LENGTH, QQ->QQ_Str};
        ProtobufStruct::TreeNode Node1_1{nullptr, &Node1_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
        ProtobufStruct::TreeNode Node1{
            &Node1_1,
            &Node2,
            1,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        Bin = PB.Pack(&Node1);
        Length = XBin::Bin2Int(Bin) - 4;

        Pack.SetByte(0x28);
        Pack.SetInt(Length);
        Pack.SetInt(DataLength);
        Pack.SetBin(Bin + 4, Length);
        Pack.SetBin(TotalData + Offset, DataLength);
        Pack.SetByte(0x29);

        TCP.Send(Pack.GetAll(), Pack.Length());

        delete Bin;
        Offset += DataLength;
    }
    delete Pack.GetAll();

    UnPack UnPack(TCP.Receive());
    UnPack.GetByte();
    Length = UnPack.GetInt();
    UnPack.GetInt();
    UnProtobuf UnPB(UnPack.GetBin(), Length);
    return true;
}
