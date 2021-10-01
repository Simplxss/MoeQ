#include "MessageSvc.h"

namespace Message
{
    LPBYTE Pack1(const char8_t *Text, const uint AtQQ)
    {
        if (Text == nullptr)
        {
            byte B[17];
            if (AtQQ == 0)
            {
                memcpy(B, "\0\0\0\x11\0\1\0\0\0\5\1\0\0\0\0\0\0", 17);
                Text = u8"@全体成员";
            }
            else
            {
                memcpy(B, "\0\0\0\x11\0\1\0\0\0\5\0\0\0\0\0\0\0", 17);
                memcpy(B + 11, XBin::Int2Bin(AtQQ), 4);
                Text = u8"@";
                //Todo
                //strcat(Text,)
            }
            uint len = strlen((char *)Text);
            LPBYTE T = new byte[len + 4];
            memcpy(T, XBin::Int2Bin(len + 4), 4);
            memcpy(T + 4, Text, len);
            ProtobufStruct::TreeNode Node1_3{nullptr, nullptr, 3, ProtobufStruct::ProtobufStructType::LENGTH, B};
            ProtobufStruct::TreeNode Node1_1{nullptr, &Node1_3, 1, ProtobufStruct::ProtobufStructType::LENGTH, T};
            ProtobufStruct::TreeNode Node1{
                &Node1_1,
                nullptr,
                1,
                ProtobufStruct::ProtobufStructType::LENGTH,
            };
            Protobuf PB;
            LPBYTE bin = PB.Pack(&Node1);
            delete[] T;
            return bin;
        }
        else
        {
            uint len = strlen((char *)Text);
            LPBYTE T = new byte[len + 4];
            memcpy(T, XBin::Int2Bin(len + 4), 4);
            memcpy(T + 4, Text, len);
            ProtobufStruct::TreeNode Node1_1{nullptr, nullptr, 1, ProtobufStruct::ProtobufStructType::LENGTH, T};
            ProtobufStruct::TreeNode Node1{
                &Node1_1,
                nullptr,
                1,
                ProtobufStruct::ProtobufStructType::LENGTH,
            };
            Protobuf PB;
            return PB.Pack(&Node1);
        }
    }
    LPBYTE Pack2(const byte id)
    {
        ProtobufStruct::TreeNode Node2_1{nullptr, nullptr, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)id};
        ProtobufStruct::TreeNode Node2{
            &Node2_1,
            nullptr,
            2,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        Protobuf PB;
        return PB.Pack(&Node2);
    }
    LPBYTE Pack6(const byte id)
    {
        ProtobufStruct::TreeNode Node2_1{nullptr, nullptr, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)id};
        ProtobufStruct::TreeNode Node2{
            &Node2_1,
            nullptr,
            2,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        Protobuf PB;
        return PB.Pack(&Node2);
    }
    LPBYTE Pack8(const LPBYTE ImageName, const LPBYTE ImageMD5, const uint ImageID, const uint ImageLength, const uint ImageWidth, const uint ImageHeight)
    {
        ProtobufStruct::TreeNode Node8_34_15{nullptr, nullptr, 15, ProtobufStruct::ProtobufStructType::VARINT, (void *)5};
        ProtobufStruct::TreeNode Node8_34_10{nullptr, &Node8_34_15, 10, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node8_34_6{nullptr, &Node8_34_10, 6, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\4"};
        ProtobufStruct::TreeNode Node8_34_2{nullptr, &Node8_34_6, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node8_34_1{nullptr, &Node8_34_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
        ProtobufStruct::TreeNode Node8_34{
            &Node8_34_1,
            nullptr,
            34,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        ProtobufStruct::TreeNode Node8_30{nullptr, &Node8_34, 30, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node8_29{nullptr, &Node8_30, 29, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node8_26{nullptr, &Node8_29, 26, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node8_25{nullptr, &Node8_26, 25, ProtobufStruct::ProtobufStructType::VARINT, (void *)ImageLength};
        ProtobufStruct::TreeNode Node8_24{nullptr, &Node8_25, 24, ProtobufStruct::ProtobufStructType::VARINT, (void *)103};
        ProtobufStruct::TreeNode Node8_23{nullptr, &Node8_24, 23, ProtobufStruct::ProtobufStructType::VARINT, (void *)ImageHeight};
        ProtobufStruct::TreeNode Node8_22{nullptr, &Node8_23, 22, ProtobufStruct::ProtobufStructType::VARINT, (void *)ImageWidth};
        ProtobufStruct::TreeNode Node8_20{nullptr, &Node8_22, 20, ProtobufStruct::ProtobufStructType::VARINT, (void *)1000};
        ProtobufStruct::TreeNode Node8_17{nullptr, &Node8_20, 17, ProtobufStruct::ProtobufStructType::VARINT, (void *)5};
        ProtobufStruct::TreeNode Node8_13{nullptr, &Node8_17, 13, ProtobufStruct::ProtobufStructType::LENGTH, ImageMD5};
        ProtobufStruct::TreeNode Node8_12{nullptr, &Node8_13, 12, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
        ProtobufStruct::TreeNode Node8_11{nullptr, &Node8_12, 11, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\4"}; //Unknown
        ProtobufStruct::TreeNode Node8_10{nullptr, &Node8_11, 10, ProtobufStruct::ProtobufStructType::VARINT, (void *)66};
        ProtobufStruct::TreeNode Node8_9{nullptr, &Node8_10, 9, ProtobufStruct::ProtobufStructType::VARINT, (void *)80};
        ProtobufStruct::TreeNode Node8_8{nullptr, &Node8_9, 8, ProtobufStruct::ProtobufStructType::VARINT, (void *)2073511832};
        ProtobufStruct::TreeNode Node8_7{nullptr, &Node8_8, 7, ProtobufStruct::ProtobufStructType::VARINT, (void *)ImageID};
        ProtobufStruct::TreeNode Node8_2{nullptr, &Node8_7, 2, ProtobufStruct::ProtobufStructType::LENGTH, ImageName};
        ProtobufStruct::TreeNode Node8{
            &Node8_2,
            nullptr,
            8,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };

        Protobuf PB;
        return PB.Pack(&Node8);
    }
    LPBYTE Pack37()
    {
        ProtobufStruct::TreeNode Node37_19_41{nullptr, nullptr, 41, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node37_19_31{nullptr, &Node37_19_41, 31, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node37_19_15{nullptr, &Node37_19_31, 15, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node37_19{
            &Node37_19_15,
            nullptr,
            19,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        ProtobufStruct::TreeNode Node37_17{nullptr, &Node37_19, 17, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        ProtobufStruct::TreeNode Node37{
            &Node37_17,
            nullptr,
            37,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };

        Protobuf PB;
        return PB.Pack(&Node37);
    }
    LPBYTE Pack51(const char8_t *Json)
    {
        Pack Pack(500, true);
        Pack.SetByte(1); //压缩
        LPBYTE bin = Utils::ZlibCompress((char *)Json);
        Pack.SetBin(bin + 4, XBin::Bin2Int(bin) - 4);
        Pack.SetLength();
        ProtobufStruct::TreeNode Node51_1{nullptr, nullptr, 1, ProtobufStruct::ProtobufStructType::LENGTH, Pack.GetAll()};
        ProtobufStruct::TreeNode Node51{
            &Node51_1,
            nullptr,
            51,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };

        Protobuf PB;
        bin = PB.Pack(&Node51);
        delete[] Pack.GetAll();
        return bin;
    }
}

LPBYTE MessageSvc::PbGetMsg()
{
    ProtobufStruct::TreeNode Node12{nullptr, nullptr, 12, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\4"};
    ProtobufStruct::TreeNode Node9{nullptr, &Node12, 9, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node7{nullptr, &Node9, 7, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node6{nullptr, &Node7, 6, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node5{nullptr, &Node6, 5, ProtobufStruct::ProtobufStructType::VARINT, (void *)3};
    ProtobufStruct::TreeNode Node4{nullptr, &Node5, 4, ProtobufStruct::ProtobufStructType::VARINT, (void *)20};
    ProtobufStruct::TreeNode Node3{nullptr, &Node4, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node2_14{nullptr, nullptr, 14, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node2_13{&Node2_14, nullptr, 13, ProtobufStruct::ProtobufStructType::VARINT, (void *)std::time(0)};
    ProtobufStruct::TreeNode Node2_12{&Node2_13, nullptr, 12, ProtobufStruct::ProtobufStructType::VARINT, (void *)41};
    ProtobufStruct::TreeNode Node2_11{&Node2_12, nullptr, 11, ProtobufStruct::ProtobufStructType::VARINT, (void *)1885270429};
    ProtobufStruct::TreeNode Node2_9{&Node2_11, nullptr, 9, ProtobufStruct::ProtobufStructType::VARINT, (void *)2346412847};
    ProtobufStruct::TreeNode Node2_5{&Node2_9, nullptr, 5, ProtobufStruct::ProtobufStructType::VARINT, (void *)562530569};
    ProtobufStruct::TreeNode Node2_4{&Node2_5, nullptr, 4, ProtobufStruct::ProtobufStructType::VARINT, (void *)3414434724};
    ProtobufStruct::TreeNode Node2_3{&Node2_4, nullptr, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)1787282332};
    ProtobufStruct::TreeNode Node2_2{&Node2_3, nullptr, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)std::time(0)};
    ProtobufStruct::TreeNode Node2_1{&Node2_2, nullptr, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)std::time(0)};
    ProtobufStruct::TreeNode Node2{
        &Node2_1,
        &Node3,
        2,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};

    Protobuf PB;
    return PB.Pack(&Node1);
}

/// <summary>
/// 发送消息(群聊,私聊)
/// </summary>
/// <param name="ToNumber"></param>
/// <param name="ToType">接收者类型 0 Friend 1 Group</param>
/// <param name="Msg"></param>
/// <returns></returns>
LPBYTE MessageSvc::PbSendMsg(const uint ToNumber, const byte ToType, const Message::Msg *Msg)
{
    ProtobufStruct::TreeNode Node8{nullptr, nullptr, 8, ProtobufStruct::ProtobufStructType::VARINT, (void *)(ToType == 0 ? 2 : 1)};
    ProtobufStruct::TreeNode Node5, Node6, Node6_1, Node6_2, Node6_3, Node6_4, Node6_5, Node6_9, Node6_11, Node6_12, Node6_13, Node6_14;
    if (ToType == 0)
    {
        Node6_14 = ProtobufStruct::TreeNode{nullptr, nullptr, 14, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
        Node6_13 = ProtobufStruct::TreeNode{nullptr, &Node6_14, 13, ProtobufStruct::ProtobufStructType::VARINT, (void *)std::time(0)};
        Node6_12 = ProtobufStruct::TreeNode{nullptr, &Node6_13, 12, ProtobufStruct::ProtobufStructType::VARINT, (void *)41};
        Node6_11 = ProtobufStruct::TreeNode{nullptr, &Node6_12, 11, ProtobufStruct::ProtobufStructType::VARINT, (void *)1885270429};
        Node6_9 = ProtobufStruct::TreeNode{nullptr, &Node6_11, 9, ProtobufStruct::ProtobufStructType::VARINT, (void *)2346412847};
        Node6_5 = ProtobufStruct::TreeNode{nullptr, &Node6_9, 5, ProtobufStruct::ProtobufStructType::VARINT, (void *)562530569};
        Node6_4 = ProtobufStruct::TreeNode{nullptr, &Node6_5, 4, ProtobufStruct::ProtobufStructType::VARINT, (void *)3414434724};
        Node6_3 = ProtobufStruct::TreeNode{nullptr, &Node6_4, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)1787282332};
        Node6_2 = ProtobufStruct::TreeNode{nullptr, &Node6_3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)std::time(0)};
        Node6_1 = ProtobufStruct::TreeNode{nullptr, &Node6_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)std::time(0)};
        Node6 = ProtobufStruct::TreeNode{
            &Node6_1,
            &Node8,
            6,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        Node5 = ProtobufStruct::TreeNode{nullptr, &Node6, 5, ProtobufStruct::ProtobufStructType::VARINT, (void *)Utils::GetRandom(0, 2147483647)};
    }
    else
        Node5 = ProtobufStruct::TreeNode{nullptr, &Node8, 5, ProtobufStruct::ProtobufStructType::VARINT, (void *)Utils::GetRandom(0, 2147483647)};
    ProtobufStruct::TreeNode Node4{nullptr, &Node5, 4, ProtobufStruct::ProtobufStructType::VARINT, (void *)Utils::GetRandom(0, 2147483647)};
    ProtobufStruct::TreeNode *Node3_1_2 = nullptr;
    do
    {
        switch (Msg->MsgType)
        {
        case Message::MsgType::text:
            Node3_1_2 = new ProtobufStruct::TreeNode{nullptr, Node3_1_2, 2, ProtobufStruct::ProtobufStructType::LENGTH, Message::Pack1(((Message::text *)Msg->Message)->text, ((Message::text *)Msg->Message)->AtQQ)};
            break;
        case Message::MsgType::classcal_face:
            Node3_1_2 = new ProtobufStruct::TreeNode{nullptr, Node3_1_2, 2, ProtobufStruct::ProtobufStructType::LENGTH, Message::Pack2(((Message::classcal_face *)Msg->Message)->id)};
            break;
        case Message::MsgType::expression:
            Node3_1_2 = new ProtobufStruct::TreeNode{nullptr, Node3_1_2, 2, ProtobufStruct::ProtobufStructType::LENGTH, Message::Pack6(((Message::expression *)Msg->Message)->id)};
            break;
        case Message::MsgType::picture:
        {
            LPBYTE B = new byte[20];
            memcpy(B, XBin::Int2Bin(20), 4);
            memcpy(B + 4, ((Message::picture *)Msg->Message)->MD5, 16);

            //name is not important
            LPBYTE T = new byte[40];
            memcpy(T, XBin::Int2Bin(36), 4);
            memcpy(T + 4, XBin::Bin2HexEx(((Message::picture *)Msg->Message)->MD5, 16), 32);
            memcpy(T + 36, ".gif", 4);

            uint ImageID = QQ_UploadImage(ToType == 1 ? ToNumber : 0, T, B, ((Message::picture *)Msg->Message)->Data.Length, ((Message::picture *)Msg->Message)->Width, ((Message::picture *)Msg->Message)->Height, ((Message::picture *)Msg->Message)->Data.Contain);
            if (ImageID != 0)
                Node3_1_2 = new ProtobufStruct::TreeNode{nullptr, Node3_1_2, 2, ProtobufStruct::ProtobufStructType::LENGTH, Message::Pack8(T, B, ImageID, ((Message::picture *)Msg->Message)->Data.Length, ((Message::picture *)Msg->Message)->Width, ((Message::picture *)Msg->Message)->Height)};
            delete T, B;
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
            Node3_1_2 = new ProtobufStruct::TreeNode{nullptr, Node3_1_2, 2, ProtobufStruct::ProtobufStructType::LENGTH, Message::Pack51(((Message::json *)Msg->Message)->text)};
            break;
        default:
            break;
        }
    } while ((Msg = Msg->NextPoint) != nullptr);
    Node3_1_2 = new ProtobufStruct::TreeNode{nullptr, Node3_1_2, 2, ProtobufStruct::ProtobufStructType::LENGTH, Message::Pack37()};
    ProtobufStruct::TreeNode Node3_1{
        Node3_1_2,
        nullptr,
        1,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node3{
        &Node3_1,
        &Node4,
        3,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node2_3{nullptr, nullptr, 3, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node2_2{nullptr, &Node2_3, 2, ProtobufStruct::ProtobufStructType::VARINT, (void *)0};
    ProtobufStruct::TreeNode Node2_1{nullptr, &Node2_2, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)1};
    ProtobufStruct::TreeNode Node2{
        &Node2_1,
        &Node3,
        2,
        ProtobufStruct::ProtobufStructType::LENGTH,
    };
    ProtobufStruct::TreeNode Node1_1_1, Node1_1, Node1_2_1, Node1_2, Node1;

    switch (ToType)
    {
    case 0:
        Node1_1_1 = ProtobufStruct::TreeNode{nullptr, nullptr, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)ToNumber};
        Node1_1 = ProtobufStruct::TreeNode{
            &Node1_1_1,
            nullptr,
            1,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        Node1 = ProtobufStruct::TreeNode{
            &Node1_1,
            &Node2,
            1,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        break;
    case 1:
        Node1_2_1 = ProtobufStruct::TreeNode{nullptr, nullptr, 1, ProtobufStruct::ProtobufStructType::VARINT, (void *)ToNumber};
        Node1_2 = ProtobufStruct::TreeNode{
            &Node1_2_1,
            nullptr,
            2,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        Node1 = ProtobufStruct::TreeNode{
            &Node1_2,
            &Node2,
            1,
            ProtobufStruct::ProtobufStructType::LENGTH,
        };
        break;
    default:
        throw "ToType not exist";
        break;
    }

    Protobuf PB;
    LPBYTE result = PB.Pack(&Node1);

    ProtobufStruct::TreeNode *tmp;
    do
    {
        delete[] (LPBYTE)Node3_1_2->Data;
        tmp = Node3_1_2->brother;
        delete Node3_1_2;
    } while ((Node3_1_2 = tmp) != nullptr);
    return result;
}