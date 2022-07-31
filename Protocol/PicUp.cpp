#include "PicUp.h"

/// <summary>
/// 上传文件
/// </summary>
/// <param name="TotalData"></param>
/// <param name="TotalDataLength"></param>
/// <param name="TotalDataMD5"></param>
/// <param name="DataType">friend image=1, group image=2, friendPtt=26, groupPtt=29</param>
/// <param name="IP"></param>
/// <param name="Port"></param>
/// <param name="sig"></param>
/// <returns></returns>
bool PicUp::DataUp(const byte *TotalData, const uint TotalDataLength, const byte *TotalDataMD5, const int DataType, const uint IP, const uint Port, const LPBYTE sig)
{
    Socket TCP;

    char *ip = XBin::Int2IP(IP);
    if (!TCP.Connect(ip, 80))
    {
        delete[] ip;
        throw "Connect upload server false";
    };
    delete[] ip;

    uint32_t size;
    if (TotalDataLength > 0x100000)
        size = 0x40000;
    else
        size = 0x2000;

    //文件分片发送
    uint Offset = 0, DataLength, Length, i = Utils::GetRandom(1000, 10000);
    Protobuf PB;
    byte *Bin;
    Pack Pack(size + 0x100, false);
    while ((DataLength = TotalDataLength - Offset) > 0)
    {
        if (DataLength > size)
            DataLength = size;

        PB.StepIn(1);
        PB.WriteVarint(1, 1);
        PB.WriteStr(2, (char8_t *)QQ->QQ_Str);
        PB.WriteStr(3, u8"PicUp.DataUp");
        PB.WriteVarint(4, ++i);
        PB.WriteVarint(5, 0);
        PB.WriteVarint(6, AndroidQQ_APPID);
        PB.WriteVarint(7, 4096);
        PB.WriteVarint(8, DataType);
        PB.WriteVarint(10, 2052);
        PB.StepOut();
        PB.StepIn(2);
        PB.WriteVarint(2, TotalDataLength);
        PB.WriteVarint(3, Offset);
        PB.WriteVarint(4, DataLength);
        PB.WriteBin(6, sig);
        PB.WriteBin_(8, Utils::MD5(TotalData + Offset, DataLength), 16);
        PB.WriteBin(9, TotalDataMD5, 16);
        PB.WriteVarint(10, 0);
        PB.WriteVarint(13, 0);
        PB.StepOut();
        Length = PB.Pack(Bin);

        Pack.SetByte(0x28);
        Pack.SetInt(Length);
        Pack.SetInt(DataLength);
        Pack.SetBin(Bin, Length);
        Pack.SetBin(TotalData + Offset, DataLength);
        Pack.SetByte(0x29);

        if (TCP.Send(Pack.GetAll(), Pack.Length()) <= 0)
        {
            throw "upload fail";
            return false;
        }

        byte Receive[200];
        try
        {
            TCP.Receive(Receive, 200);
        }
        catch (int e)
        {
            std::cerr << e << '\n';
        }

        // ...

        Offset += DataLength;
    }
    delete[] Bin;
    delete[] Pack.GetAll();
    delete[] sig;
    return true;
}
