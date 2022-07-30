#include "MessageSvc.h"

namespace Message
{
    void Pack1(Protobuf &PB, const char8_t *Text, const uint AtQQ)
    {
        if (Text == nullptr)
        {
            byte *B = new byte[13];
            if (AtQQ == 0)
            {
                memcpy(B, "\0\1\0\0\0\5\1\0\0\0\0\0\0", 13);
                Text = u8"@全体成员";
            }
            else
            {
                memcpy(B, "\0\1\0\0\0\5\0\0\0\0\0\0\0", 13);
                memcpy(B + 7, XBin::Int2Bin(AtQQ), 4);
                Text = u8"@nick";
                // Todo 获取昵称
                // strcat(Text,)
            }
            PB.StepIn(1);
            PB.WriteStr(1, Text);
            PB.WriteBin_(3, B, 13);
            PB.StepOut();
        }
        else
        {
            PB.StepIn(1);
            PB.WriteStr(1, Text);
            PB.StepOut();
        }
    }
    void Pack2(Protobuf &PB, const byte id)
    {
        PB.StepIn(2);
        PB.WriteVarint(1, id);
        PB.StepOut();
    }
    void Pack6(Protobuf &PB, const byte id)
    {
        PB.StepIn(6);
        PB.StepOut();
    }
    void Pack8(Protobuf &PB, char8_t *ImageName, const byte *ImageMD5, const uint ImageID, const uint ImageLength, const uint ImageWidth, const uint ImageHeight)
    {
        PB.StepIn(8);
        PB.WriteStr_(2, ImageName);
        PB.WriteVarint(7, ImageID);
        PB.WriteVarint(8, 2073511832);
        PB.WriteVarint(9, 80);
        PB.WriteVarint(10, 66);
        PB.WriteBin(11, {}, 0);
        PB.WriteVarint(12, 1);
        PB.WriteBin(13, ImageMD5, 16);
        PB.WriteVarint(17, 5);
        PB.WriteVarint(20, 1000);
        PB.WriteVarint(22, ImageWidth);
        PB.WriteVarint(23, ImageHeight);
        PB.WriteVarint(24, 103);
        PB.WriteVarint(25, ImageLength);
        PB.WriteVarint(26, 0);
        PB.WriteVarint(29, 0);
        PB.WriteVarint(30, 0);
        PB.StepIn(34);
        PB.WriteVarint(1, 1);
        PB.WriteVarint(2, 0);
        PB.WriteBin(6, {}, 0);
        PB.WriteVarint(10, 0);
        PB.WriteVarint(15, 5);
        PB.StepOut();
        PB.StepOut();
    }
    void Pack37(Protobuf &PB)
    {
        PB.StepIn(37);
        PB.WriteVarint(17, 2177);
        PB.StepIn(19);
        PB.WriteVarint(15, 131072);
        PB.WriteVarint(31, 0);
        PB.WriteVarint(41, 0);
        PB.StepOut();
        PB.StepOut();
    }
    void Pack51(Protobuf &PB, const char8_t *Json)
    {
        Pack Pack(500);
        Pack.SetByte(1); //压缩
        LPBYTE bin = Utils::ZlibCompress((char *)Json);
        Pack.SetBin(bin + 4, XBin::Bin2Int(bin) - 4);
        delete[] bin;

        PB.StepIn(51);
        PB.WriteBin_(1, Pack.GetAll(), Pack.Length());
        PB.StepOut();
    }
}

LPBYTE MessageSvc::PbGetMsg()
{
    Protobuf PB;
    PB.WriteVarint(1, 0);
    PB.StepIn(2);
    PB.WriteVarint(1, std::time(0));
    PB.WriteVarint(2, std::time(0));
    PB.WriteVarint(3, 1787282332);
    PB.WriteVarint(4, 3414434724);
    PB.WriteVarint(5, 562530569);
    PB.WriteVarint(9, 2346412847);
    PB.WriteVarint(11, 1885270429);
    PB.WriteVarint(12, 41);
    PB.WriteVarint(13, std::time(0));
    PB.WriteVarint(14, 0);
    PB.StepOut();
    PB.WriteVarint(3, 0);
    PB.WriteVarint(4, 20);
    PB.WriteVarint(6, 3);
    PB.WriteVarint(7, 1);
    PB.WriteVarint(9, 1);
    PB.WriteBin(12, {}, 0);
    return PB.Pack();
}

/// <summary>
/// 发送消息(群聊,私聊)
/// </summary>
/// <param name="ToNumber"></param>
/// <param name="ToType">接收者类型 2 Friend 1 Group</param>
/// <param name="Msg"></param>
/// <returns></returns>
LPBYTE MessageSvc::PbSendMsg(const uint ToNumber, const byte ToType, const Message::Msg *Msg)
{
    Protobuf PB;
    PB.StepIn(1);
    switch (ToType)
    {
    case 0:
        PB.StepIn(1);
        PB.WriteVarint(1, ToNumber);
        PB.StepOut();
        break;
    case 1:
        PB.StepIn(2);
        PB.WriteVarint(1, ToNumber);
        PB.StepOut();
        break;
    default:
        throw "ToType not exist";
        break;
    }
    PB.StepOut();
    PB.StepIn(2);
    PB.WriteVarint(1, 1);
    PB.WriteVarint(2, 0);
    PB.WriteVarint(3, 0);
    PB.StepOut();
    PB.StepIn(3);
    PB.StepIn(1);
    while (Msg != nullptr)
    {
        PB.StepIn(2);
        switch (Msg->MsgType)
        {
        case Message::MsgType::text:
            Message::Pack1(PB, ((Message::text *)Msg->Message)->text, ((Message::text *)Msg->Message)->AtQQ);
            break;
        case Message::MsgType::classcal_face:
            Message::Pack2(PB, ((Message::classcal_face *)Msg->Message)->id);
            break;
        case Message::MsgType::expression:
            Message::Pack6(PB, ((Message::expression *)Msg->Message)->id);
            break;
        case Message::MsgType::picture:
        {
            // name is not important
            char8_t *T = new char8_t[37];
            memcpy(T, XBin::Bin2HexEx(((Message::picture *)Msg->Message)->MD5, 16), 32);
            memcpy(T + 32, ".jpg", 5);

            uint ImageID = QQ_UploadImage(ToType == 1 ? ToNumber : 0, T, ((Message::picture *)Msg->Message)->MD5, ((Message::picture *)Msg->Message)->Data.Length, ((Message::picture *)Msg->Message)->Width, ((Message::picture *)Msg->Message)->Height, ((Message::picture *)Msg->Message)->Data.Contain);
            if (ImageID != 0)
                Message::Pack8(PB, T, ((Message::picture *)Msg->Message)->MD5, ImageID, ((Message::picture *)Msg->Message)->Data.Length, ((Message::picture *)Msg->Message)->Width, ((Message::picture *)Msg->Message)->Height);
        }
        break;
        case Message::MsgType::xml:
            break;
        case Message::MsgType::reply:
        {
            Message::Msg *ReplyMsg = ((Message::reply *)Msg->Message)->Msg;
            while (ReplyMsg != nullptr)
            {
            }
        }
        break;
        case Message::MsgType::json:
            Message::Pack51(PB, ((Message::json *)Msg->Message)->text);
            break;
        default:
            break;
        }
        Msg = Msg->NextPoint;
        PB.StepOut();
    }

    PB.StepIn(2);
    Message::Pack37(PB);
    PB.StepOut();

    PB.StepOut();
    PB.StepOut();
    PB.WriteVarint(4, Utils::GetRandom(0, 2147483647));
    PB.WriteVarint(5, Utils::GetRandom(0, 2147483647));
    if (ToType == 0)
    {
        PB.StepIn(6);
        PB.WriteVarint(1, std::time(0));
        PB.WriteVarint(2, std::time(0));
        PB.WriteVarint(3, 1787282332);
        PB.WriteVarint(4, 3414434724);
        PB.WriteVarint(5, 562530569);
        PB.WriteVarint(9, 2346412847);
        PB.WriteVarint(11, 1885270429);
        PB.WriteVarint(12, 41);
        PB.WriteVarint(13, std::time(0));
        PB.WriteVarint(14, 0);
        PB.StepOut();
    }
    PB.WriteVarint(8, ToType == 0 ? 2 : 1);
    return PB.Pack();
}