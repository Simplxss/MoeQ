#include "Android.h"

namespace Message
{
#define FUNC(id) void UnPack##id(UnProtobuf *UnPB, Msg *&Msg)

    FUNC(1)
    {
        UnPB->StepIn(1);
        Msg = new Message::Msg{Message::MsgType::text, nullptr, new Message::text};
        ((Message::text *)Msg->Message)->text = UnPB->GetStr(1);
        if (UnPB->GetField() == 3)
        {
            delete[] ((Message::text *)Msg->Message)->text;
            ((Message::text *)Msg->Message)->text = nullptr;
            UnPack UnPack(UnPB->GetBin(3));
            UnPack.Skip(7);
            ((Message::text *)Msg->Message)->AtQQ = UnPack.GetInt();
        }
        UnPB->StepOut();
    }
    FUNC(2)
    {
        UnPB->StepIn(2);
        Msg = new Message::Msg{Message::MsgType::classcal_face, nullptr, new Message::classcal_face};
        ((Message::classcal_face *)Msg->Message)->id = UnPB->GetVarint(1);
        UnPB->StepOut();
    }
    FUNC(4)
    {
        UnPB->StepIn(4);
        Msg = new Message::Msg{Message::MsgType::picture, nullptr, new Message::picture};
        ((Message::picture *)Msg->Message)->Data.Length = UnPB->GetVarint(2);
        UnPB->GetBin(((Message::picture *)Msg->Message)->MD5, 7);
        ((Message::picture *)Msg->Message)->Data.URL = UnPB->GetStr(15);
        ((Message::picture *)Msg->Message)->Width = UnPB->GetVarint(21);
        ((Message::picture *)Msg->Message)->Height = UnPB->GetVarint(22);
        UnPB->StepOut();
        Database::AddPicture((char *)((Message::picture *)Msg->Message)->MD5, ((Message::picture *)Msg->Message)->Data.URL, ((Message::picture *)Msg->Message)->Width, ((Message::picture *)Msg->Message)->Height, ((Message::picture *)Msg->Message)->Data.Length);
    }
    FUNC(5)
    {
    }
    FUNC(6)
    {
        UnPB->StepIn(6);
        Msg = new Message::Msg{Message::MsgType::expression, nullptr, new Message::expression};
        UnPB->GetBin(((Message::expression *)Msg->Message)->MD5, 4);
        ((Message::expression *)Msg->Message)->id = UnPB->GetVarint(5);
        UnPB->StepOut();
    }
    FUNC(8)
    {
        UnPB->StepIn(8);
        Msg = new Message::Msg{Message::MsgType::picture, nullptr, new Message::picture};
        UnPB->GetBin(((Message::picture *)Msg->Message)->MD5, 13);
        ((Message::picture *)Msg->Message)->Data.URL = UnPB->GetStr(16);
        ((Message::picture *)Msg->Message)->Width = UnPB->GetVarint(22);
        ((Message::picture *)Msg->Message)->Height = UnPB->GetVarint(23);
        ((Message::picture *)Msg->Message)->Data.Length = UnPB->GetVarint(25);
        UnPB->StepOut();
        Database::AddPicture((char *)((Message::picture *)Msg->Message)->MD5, ((Message::picture *)Msg->Message)->Data.URL, ((Message::picture *)Msg->Message)->Width, ((Message::picture *)Msg->Message)->Height, ((Message::picture *)Msg->Message)->Data.Length);
    }
    FUNC(9)
    {
        /*
         * 4a 04 08 00 40 03
         * [
         * 9 {
         * 1: 0
         * 8: 3
         * }
         * ]
         */
    }
    FUNC(12)
    {
        UnPB->StepIn(12);
        Msg = new Message::Msg{Message::MsgType::xml, nullptr, new Message::xml};
        {
            LPBYTE Bin = UnPB->GetBin(1);
            if (Bin[4] == 1)
            {
                ((Message::xml *)Msg->Message)->text = (char8_t *)Utils::ZlibUnCompress(Bin + 5, XBin::Bin2Int(Bin) - 5);
                delete Bin;
            }
            else
            {
                uint len = XBin::Bin2Int(Bin) - 4;
                ((Message::xml *)Msg->Message)->text = new char8_t[len];
                memcpy(((Message::xml *)Msg->Message)->text, Bin + 5, len - 1);
                ((Message::xml *)Msg->Message)->text[len] = 0;
                delete Bin;
            }
        }
        UnPB->StepOut();
    }
    FUNC(16)
    {
        /*
         * 82 01 0b 0a 05 65 6d 6d 6d 63 18 01 28 01
         * [
         * 16 {
         * 1 {
         *  12: emmmc //发送人群名片
         * }
         * 3: 1
         * 5: 1
         * }
         * ]
         */
    }
    FUNC(24)
    {
        UnPB->StepIn(24);
        UnPB->StepIn(1);

        char8_t *listid = UnPB->GetStr(9);
        char8_t *authkey = UnPB->GetStr(10);
        uint channel = UnPB->GetVarint(19);
        delete[] listid;
        delete[] authkey;

        UnPB->StepOut();
        UnPB->StepOut();
    }
    FUNC(33)
    {
    }
    FUNC(37)
    {
        /*
         * aa 02 3e 50 00 60 00 68 00 9a 01 35 08 07 20 cb
         * 50 c8 01 00 f0 01 00 f8 01 00 90 02 00 98 03 00
         * a0 03 00 b0 03 00 c0 03 00 d0 03 00 e8 03 00 8a
         * 04 02 10 02 90 04 80 40 b8 04 00 c0 04 00 ca 04
         * 00
         * [
         * 37 {
         * 10: 0
         * 12: 0
         * 13: 0
         * 19 {
         *  1: 7
         *  4: 10315
         *  25: 0
         *  30: 0
         *  31: 0
         *  34: 0
         *  51: 0
         *  52: 0
         *  54: 0
         *  56: 0
         *  58: 0
         *  61: 0
         *  65 {
         *    2: 2
         *  }
         *  66: 8192
         *  71: 0
         *  72: 0
         *  73: ""
         * }
         * }
         * ]
         */
    }
    FUNC(45)
    {
        UnPB->StepIn(45);
        Msg = new Message::Msg{Message::MsgType::reply, nullptr, new Message::reply};
        ((Message::reply *)Msg->Message)->MsgId = UnPB->GetVarint(1);
        ((Message::reply *)Msg->Message)->QQ = UnPB->GetVarint(2);
        ((Message::reply *)Msg->Message)->Time = UnPB->GetVarint(3);
        UnPB->GetVarint(4);
        {
            Message::Msg *ReplyMsg = nullptr;
            while (UnPB->GetField() == 5)
            {
                UnPB->StepIn(5);
                if (ReplyMsg != nullptr)
                    ReplyMsg = ReplyMsg->NextPoint = new Message::Msg;
                else
                    ((Message::reply *)Msg->Message)->Msg = ReplyMsg = new Message::Msg;
                switch (UnPB->GetField())
                {
                case 1:
                    ReplyMsg->MsgType = Message::MsgType::text;
                    ReplyMsg->Message = new Message::text;
                    UnPB->StepIn(1);
                    ((Message::text *)ReplyMsg->Message)->text = UnPB->GetStr(1);
                    UnPB->StepOut();
                    break;
                case 2:
                    ReplyMsg->MsgType = Message::MsgType::classcal_face;
                    ReplyMsg->Message = new Message::classcal_face;
                    UnPB->StepIn(2);
                    ((Message::classcal_face *)ReplyMsg->Message)->id = UnPB->GetVarint(1);
                    UnPB->StepOut();
                    break;
                }
                UnPB->StepOut();
            }
        }
        UnPB->StepOut();
    }
    FUNC(51)
    {
        UnPB->StepIn(51);
        Msg = new Message::Msg{Message::MsgType::json, nullptr, new Message::json};
        {
            LPBYTE Bin = UnPB->GetBin(1);
            if (Bin[4] == 1)
            {
                ((Message::json *)Msg->Message)->text = (char8_t *)Utils::ZlibUnCompress(Bin + 5, XBin::Bin2Int(Bin) - 5);
                delete Bin;
            }
            else
            {
                uint len = XBin::Bin2Int(Bin) - 4;
                ((Message::json *)Msg->Message)->text = new char8_t[len];
                memcpy(((Message::json *)Msg->Message)->text, Bin + 5, len - 1);
                ((Message::json *)Msg->Message)->text[len] = 0;
                delete Bin;
            }
        }
        UnPB->StepOut();
    }
    FUNC(53)
    {
        UnPB->StepIn(53);
        UnPB->GetVarint(1);
        /* Todo */
        UnPB->StepOut();
    }

#undef FUNC
}

Android::Android(const char *IMEI, const char IMSI[16], const byte GUID[16], const byte MAC[6], const char *_device, const char *Brand) : wtlogin(&QQ, &Device), StatSvc(&QQ, &Device), friendlist(&QQ), OidbSvc(&QQ), MessageSvc(&QQ), PbMessageSvc(&QQ), OnlinePush(&QQ), ImgStore(&QQ), LongConn(&QQ), pttTrans(&QQ), PicUp(&QQ), SQQzoneSvc(&QQ, &Device), VisitorSvc(&QQ), ProfileService(&QQ)
{
    Device.IMEI = new char[strlen(IMEI)];
    Device.IMSI = new char[16];
    Device.GUID = new byte[16];
    Device.MAC = new byte[6];
    Device._device = new char[strlen(_device)];
    Device.Brand = new char[strlen(Brand)];
    memcpy(Device.IMEI, IMEI, strlen(IMEI) + 1);
    memcpy(Device.IMSI, IMSI, 16);
    memcpy(Device.GUID, GUID, 16);
    memcpy(Device.MAC, MAC, 6);
    memcpy(Device._device, _device, strlen(_device) + 1);
    memcpy(Device.Brand, Brand, strlen(Brand) + 1);
    memcpy(QQ.Version + 1, IMSI, 15);
    Device.os_type = "android";
    Device.os_version = "12";
    Device._network_type = 2;
    Device._apn = "wifi";
    Device.NetworkName = "China Mobile";
    Device.WiFiName = "my wifi";
    Device.BSSID = "a";
    QQ.SsoSeq = Utils::GetRandom(1123, 9999);
    QQ.MsgCookie = Utils::GetRandomBin(4);

    QQ.sig.sync_const1 = Utils::GetRandom(0x10000000, 0xffffffff);
    QQ.sig.sync_const2 = Utils::GetRandom(0x10000000, 0xffffffff);
    QQ.sig.sync_const3 = Utils::GetRandom(0x10000000, 0xffffffff);

#if defined(_WIN_PLATFORM_)
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    HandleThreads.init(sysInfo.dwNumberOfProcessors * 2);
    HandleThreads.start();
#endif

#if defined(_LINUX_PLATFORM_)
    HandleThreads.init(sysconf(_SC_NPROCESSORS_CONF) * 2);
    HandleThreads.start();
#endif
}

bool Android::Fun_Connect(const char *IP, const unsigned short Port)
{
    if (IP == nullptr || Port == 0)
    {
        try
        {
#if defined(_WIN_PLATFORM_)
            wchar_t *IP;
            TCP.DomainGetIP(L"msfwifi.3g.qq.com", IP);
            if (!TCP.Connect(Iconv::UnicodeToAnsi(IP).c_str(), 8080))
            {
                delete[] IP;
                throw "Connect failed";
            };
            delete[] IP;
#endif
#if defined(_LINUX_PLATFORM_)
            char *IP;
            TCP.DomainGetIP("msfwifi.3g.qq.com", IP);
            if (!TCP.Connect(IP, 8080))
            {
                delete[] IP;
                return (false);
            };
            delete[] IP;
#endif
        }
        catch (...)
        {
            if (!TCP.Connect("113.96.13.79", 8080))
            {
                return (false);
            };
        }
    }
    else
    {
        if (!TCP.Connect(IP, Port))
            return (false);
    }
    std::thread MsgLoop(&Android::Fun_Msg_Loop, this);
    MsgLoop.detach();
    return (true);
}

void Android::Fun_Send(const uint PacketType, const byte EncodeType, const char *ServiceCmd, LPBYTE Buffer, int SsoSeq)
{
    ::Pack Pack(XBin::Bin2Int(Buffer) + 100, true);

    switch (PacketType)
    {
    case 10:
        Pack.SetInt(SsoSeq);
        Pack.SetInt(AndroidQQ_SUB_APPID);
        Pack.SetInt(AndroidQQ_SUB_APPID);
        Pack.SetBin((byte *)"\1\0\0\0\0\0\0\0\0\0\0\0", 12);
        if (EncodeType == 1)
        {
            Pack.SetInt(76);
            Pack.SetBin(QQ.Token.TGT, 72);
        }
        else
        {
            Pack.SetInt(4);
        }
        Pack.SetInt(strlen(ServiceCmd) + 4);
        Pack.SetStr(ServiceCmd);
        Pack.SetInt(8); /* MsgCookie len + 4 */
        Pack.SetBin(QQ.MsgCookie, 4);
        Pack.SetInt(strlen(Device.IMEI) + 4); /* IMEI len + 4 */
        Pack.SetStr(Device.IMEI);
        Pack.SetInt(4);
        Pack.SetShort(34); /* Version len + 2 */
        Pack.SetStr(QQ.Version);
        Pack.SetInt(4);
        break;
    case 11:
        Pack.SetInt(strlen(ServiceCmd) + 4);
        Pack.SetStr(ServiceCmd);
        Pack.SetInt(8);
        Pack.SetBin(QQ.MsgCookie, 4);
        Pack.SetInt(4);
        break;
    }
    Pack.SetLength(); /* 这里利用了个bug, 就不用 Pack.SetBin_(Pack.GetAll_(false)) 了 */
    Pack.SetBin_(Buffer);
    byte *bin;
    uint bin_len = Pack.GetAll_(bin, true);

    Pack.SetInt(PacketType);
    Pack.SetByte(EncodeType);
    switch (PacketType)
    {
    case 10:
        if (EncodeType == 1)
        {
            Pack.SetInt(68);
            Pack.SetBin(QQ.Token.A2, 64);
        }
        else
        {
            Pack.SetInt(4);
        }
        break;
    case 11:
        Pack.SetInt(SsoSeq);
        break;
    }

    Pack.SetByte(0);
    Pack.SetInt(strlen(QQ.QQ_Str) + 4);
    Pack.SetStr(QQ.QQ_Str);

    switch (EncodeType)
    {
    case 0:
        Pack.SetBin(bin, bin_len);
        break;
    case 1:
    {
        std::vector<byte> data;
        Tea::encrypt(QQ.Token.D2Key, bin, bin_len, data);
        Pack.SetBin(&data);
        break;
    }
    case 2:
    {
        std::vector<byte> data;
        Tea::encrypt((byte *)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", bin, bin_len, data);
        Pack.SetBin(&data);
        break;
    }
    }
    delete[] bin;
    Pack.SetLength();
    TCP.Send(Pack.GetAll());
    delete[] Pack.GetAll();
}

void Android::Fun_Send_PB(const uint PacketType, const byte EncodeType, const char *ServiceCmd, LPBYTE Buffer, int SsoSeq)
{
    Protobuf PB;
    PB.WriteVarint(1, SsoSeq);
    PB.WriteStr(2, (const char8_t *)ServiceCmd);
    PB.WriteVarint(3, 0x80);
    PB.WriteBin(4, Buffer);
    PB.WriteVarint(5, 0);
    Fun_Send(PacketType, EncodeType, ServiceCmd, PB.Pack(), SsoSeq);
}

void Android::Fun_Msg_Loop()
{
    while (true)
    {
        LPBYTE bin;
        try
        {
            bin = TCP.Receive();
        }
        catch (const int e)
        {
            try
            {
                Fun_Connect();
                Log::AddLog(Log::LogType::WARNING, Log::MsgType::OTHER, u8"Connection", u8"Connected");
                QQ_Online();
            }
            catch (const char *e)
            {
                Log::AddLog(Log::LogType::WARNING, Log::MsgType::OTHER, u8"Connection", u8"Receive error, code: %d", e);
            }
        }
        HandleThreads.exec(std::bind(&Android::Fun_Receice, this, bin), bin);
    }
}

void Android::Fun_Receice(const LPBYTE bin)
{
    ::UnPack UnPack(bin);
    const uint PacketType = UnPack.GetInt();
    const byte EncodeType = UnPack.GetByte();
    uint CompressType;
    UnPack.GetByte();
    const char* uin = UnPack.GetStr(UnPack.GetInt() - 4);

    std::vector<byte> buffer;
    switch (EncodeType)
    {
    case 0:
        UnPack.Reset(UnPack.GetCurrentPoint(), UnPack.GetLeftLength());
        break;
    case 1:
        if (!Tea::decrypt(QQ.Token.D2Key, UnPack.GetCurrentPoint(), UnPack.GetLeftLength(), buffer))
            return;
        UnPack.Reset(&buffer);
        break;
    case 2:
        if (!Tea::decrypt((byte *)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", UnPack.GetCurrentPoint(), UnPack.GetLeftLength(), buffer))
            return;
        UnPack.Reset(&buffer);
        break;
    default:
        throw "unknown EncodeType";
        delete[] bin;
        return;
    }

    LPBYTE HeadBin = nullptr, BodyBin = nullptr;
    HeadBin = UnPack.GetBin();
    BodyBin = UnPack.GetBin();
    UnPack.Reset(HeadBin);
    int sso_seq;
    char *ServiceCmd;
    switch (PacketType)
    {
        uint len;
    case 10:
        sso_seq = UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetBin();
        len = UnPack.GetInt();
        ServiceCmd = new char[len - 3];
        ServiceCmd[len - 4] = '\0';
        memcpy(ServiceCmd, UnPack.GetStr(len - 4), len - 4);
        UnPack.GetBin();
        CompressType = UnPack.GetInt();
        UnPack.GetBin();
        break;
    case 11:
        sso_seq = UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetBin();
        len = UnPack.GetInt();
        ServiceCmd = new char[len - 3];
        ServiceCmd[len - 4] = '\0';
        memcpy(ServiceCmd, UnPack.GetStr(len - 4), len - 4);
        UnPack.GetBin();
        CompressType = UnPack.GetInt();
        break;
    default:
        throw "unknown PacketType";
        break;
    }

    if (ServiceCmd != nullptr)
    {
        if (strlen(ServiceCmd) == 0)
        {
            delete[] ServiceCmd;
            throw "ServiceCmd is empty";
            return;
        }
    }

    switch (CompressType)
    {
    case 0:
        break;
    case 1:
        BodyBin = Utils::ZlibUnCompress(BodyBin);
        break;
    default:
        throw "unknown CompressType";
        break;
    }

    Log::AddLog(Log::LogType::__DEBUG, Log::MsgType::OTHER, u8"serviceCmd", (char8_t *)ServiceCmd);
    if (sso_seq > 0)
    {
        std::mutex lock;
        std::unique_lock<std::mutex> ulock(lock);
        std::condition_variable condition_variable;

        SendList[sso_seq & 0x3F].BodyBin = BodyBin;
        SendList[sso_seq & 0x3F].condition_variable = &condition_variable;
        SendList[sso_seq & 0x3F].cv.notify_one();
        condition_variable.wait(ulock);
    }
    else
        try
        {
            Fun_Handle(ServiceCmd, BodyBin, sso_seq);
        }
        catch (...)
        {
        };
    delete[] ServiceCmd;
    delete[] bin;
    if (CompressType)
        delete[] BodyBin;
}

void Android::Fun_Handle(char *serviceCmd, const LPBYTE BodyBin, const uint sso_seq)
{
    char *buf;
#if defined(_WIN_PLATFORM_)
    char *first = strtok_s(serviceCmd, ".", &buf);
    char *second = strtok_s(NULL, ".", &buf);
#endif
#if defined(_LINUX_PLATFORM_)
    char *first = strtok_r(serviceCmd, ".", &buf);
    char *second = strtok_r(NULL, ".", &buf);
#endif
    if (!strcmp(first, "OnlinePush"))
    {
        if (!strcmp(second, "PbPushGroupMsg"))
            Unpack_OnlinePush_PbPushGroupMsg(BodyBin, sso_seq);
        if (!strcmp(second, "PbC2CMsgSync"))
            Unpack_OnlinePush_PbC2CMsgSync(BodyBin, sso_seq);
        if (!strcmp(second, "ReqPush"))
            Unpack_OnlinePush_ReqPush(BodyBin, sso_seq);
        if (!strcmp(second, "PbPushTransMsg"))
            Unpack_OnlinePush_PbPushTransMsg(BodyBin, sso_seq);
    }
    if (!strcmp(first, "MessageSvc"))
    {
        if (!strcmp(second, "PushNotify"))
            Unpack_MessageSvc_PushNotify(BodyBin, sso_seq);
        if (!strcmp(second, "PushForceOffline"))
            Unpack_MessageSvc_PushForceOffline(BodyBin, sso_seq);
    }
    if (!strcmp(first, "StatSvc"))
    {
        if (!strcmp(second, "QueryHB"))
            Unpack_StatSvc_QueryHB(BodyBin, sso_seq);
        if (!strcmp(second, "SvcReqMSFLoginNotify"))
            Unpack_StatSvc_SvcReqMSFLoginNotify(BodyBin, sso_seq);
    }
    if (!strcmp(first, "ConfigPushSvc"))
    {
        if (!strcmp(second, "PushReq"))
            Unpack_ConfigPushSvc_PushReq(BodyBin, sso_seq);
    }
}

void Android::Fun_Life_Event()
{
    uint time = 1;
    do
    {
#if defined(_WIN_PLATFORM_)
        Sleep(45000);
#endif

#if defined(_LINUX_PLATFORM_)
        sleep(45);
#endif
        QQ_Heart_Beat();
        if (!(time % 1919))
            QQ_SyncCookie(); /* 提前45s防止plugin正好取了失效的cookie */
        ++time;
    } while (QQ_Status());
}

/*
 * / <summary>
 * /
 * / </summary>
 * / <param name="iVersion"></param>
 * / <param name="sServantName"></param>
 * / <param name="sFuncName"></param>
 * / <param name="sBuffer">会自动销毁</param>
 * / <param name="Bufferlen"></param>
 * / <returns></returns>
 */
LPBYTE Android::Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char *sServantName, const char *sFuncName, byte *sBuffer, uint Bufferlen)
{
    Jce Jce(true);
    Jce.Write(iVersion, 1);
    Jce.Write(0, 2);
    Jce.Write(0, 3);
    Jce.Write(iRequestId, 4);
    Jce.Write(sServantName, 5);
    Jce.Write(sFuncName, 6);
    Jce.Write(sBuffer, Bufferlen, 7);
    Jce.Write(0, 8);
    std::vector<JceStruct::Map<const char *, const char *>> a;
    Jce.Write(&a, 9);
    Jce.Write(&a, 10);
    delete[] sBuffer;
    return (Jce.GetAll());
}

void Android::Un_Tlv_Get(const unsigned short cmd, const byte *bin, const uint len)
{
    ::UnPack UnPack(bin, len);
    switch (cmd)
    {
    case 0x103:
        if (QQ.Cookie.StWebSig != nullptr)
            delete[] QQ.Cookie.StWebSig;
        QQ.Cookie.StWebSig = new byte[len];
        memcpy(QQ.Cookie.StWebSig, bin, len);
        break;
    case 0x104:
        if (QQ.Login->VieryToken2 != nullptr)
            delete[] QQ.Login->VieryToken2;
        QQ.Login->VieryToken2 = new byte[len];
        memcpy(QQ.Login->VieryToken2, bin, len);
        break;
    case 0x105:
    {
        uint length = UnPack.GetShort();
        if (QQ.Login->VieryToken1 != nullptr)
            delete[] QQ.Login->VieryToken1;
        QQ.Login->VieryToken1 = new byte[len];
        memcpy(QQ.Login->VieryToken1, bin, len);
        length = UnPack.GetShort();
        if (QQ.Login->Viery_Image != nullptr)
            delete[] QQ.Login->Viery_Image;
        QQ.Login->Viery_Image = new byte[len];
        memcpy(QQ.Login->Viery_Image, bin, len);
    }
    break;
    case 0x106:
    {
        std::vector<byte> data;
        Tea::decrypt(QQ.Token.md52, bin, len, data);
        UnPack.Reset(&data);
        UnPack.GetShort();
        UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetLong();
        UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetByte();
        UnPack.GetBin(16);
        UnPack.GetBin(16);
        UnPack.GetInt();
        UnPack.GetByte();
        UnPack.GetBin(16);
        UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetBin(UnPack.GetShort());
        UnPack.GetShort();
    }
    break;
    case 0x108:
        if (QQ.Token.ksid != nullptr)
            delete[] QQ.Token.ksid;
        QQ.Token.ksid = new byte[len];
        memcpy(QQ.Token.ksid, bin, len);
        break;
    case 0x10A:
        if (QQ.Token.TGT != nullptr)
            delete[] QQ.Token.TGT;
        QQ.Token.TGT = new byte[len];
        memcpy(QQ.Token.TGT, bin, len);
        break;
    case 0x10C:
        if (QQ.Token.TGTkey != nullptr)
            delete[] QQ.Token.TGTkey;
        QQ.Token.TGTkey = new byte[16];
        memcpy(QQ.Token.TGTkey, UnPack.GetBin(16), 16);
        break;
    case 0x10D:
        if (QQ.Token.TGTkey != nullptr)
            delete[] QQ.Token.TGTkey;
        QQ.Token.TGTkey = new byte[16];
        memcpy(QQ.Token.TGTkey, UnPack.GetBin(16), 16);
        break;
    case 0x10E:
        if (QQ.Token.StKey != nullptr)
            delete[] QQ.Token.StKey;
        QQ.Token.StKey = new byte[len];
        memcpy(QQ.Token.StKey, bin, len);
        break;
    case 0x114:
        UnPack.GetShort();
        UnPack.GetInt();
        UnPack.GetBin(UnPack.GetShort());
        break;
    case 0x118:
        UnPack.GetBin(UnPack.GetInt());
        break;
    case 0x119:
    {
        std::vector<byte> data;
        Tea::decrypt(QQ.Token.TGTkey, bin, len, data);
        UnPack.Reset(&data);
        unsigned short Count = UnPack.GetShort();
        for (size_t i = 0; i < Count; i++)
        {
            unsigned short cmd = UnPack.GetShort();
            unsigned short binlen = UnPack.GetShort();
            Un_Tlv_Get(cmd, UnPack.GetBin(binlen), binlen);
        }
    }
    break;
    case 0x11A:
    {
        UnPack.GetShort();
        UnPack.GetByte();
        UnPack.GetByte();
        if (QQ.Nick != nullptr)
            delete[] QQ.Nick;
        byte length = UnPack.GetByte();
        QQ.Nick = new char8_t[length + 1];
        QQ.Nick[length] = 0;
        memcpy(QQ.Nick, UnPack.GetBin(length), length);
    }
    break;
    case 0x11d:
        break;
    case 0x11F:
        UnPack.GetInt();
        UnPack.GetInt();
        UnPack.GetShort();
        break;
    case 0x120:
        if (QQ.Cookie.skey != nullptr)
            delete[] QQ.Cookie.skey;
        QQ.Cookie.skey = new char[len + 1];
        QQ.Cookie.skey[len] = 0;
        memcpy(QQ.Cookie.skey, bin, len);
        break;
    case 0x130:
        UnPack.GetShort();
        UnPack.GetInt();  /* time */
        UnPack.GetBin(4); /* ip */
        break;
    case 0x133:
        if (QQ.Token.wtSessionTicket != nullptr)
            delete[] QQ.Token.wtSessionTicket;
        QQ.Token.wtSessionTicket = new byte[len];
        memcpy(QQ.Token.wtSessionTicket, bin, len);
        break;
    case 0x134:
        if (QQ.Token.wtSessionTicketKey != nullptr)
            delete[] QQ.Token.wtSessionTicketKey;
        QQ.Token.wtSessionTicketKey = new byte[len];
        memcpy(QQ.Token.wtSessionTicketKey, bin, len);
        break;
    case 0x136:
        if (QQ.Cookie.vkey != nullptr)
            delete[] QQ.Cookie.vkey;
        QQ.Cookie.vkey = new char[len + 1];
        QQ.Cookie.vkey[len] = 0;
        memcpy(QQ.Cookie.vkey, bin, len);
        break;
    case 0x138:
        for (size_t i = 0; i < UnPack.GetInt(); i++)
        {
            unsigned short tlv_cmd = UnPack.GetShort();
            uint time = UnPack.GetInt();
            UnPack.GetInt();
        }
        break;
    case 0x143:
        if (QQ.Token.A2 != nullptr)
            delete[] QQ.Token.A2;
        QQ.Token.A2 = new byte[len];
        memcpy(QQ.Token.A2, bin, len);
        break;
    case 0x146:
        UnPack.GetInt();
        UnPack.GetBin(UnPack.GetShort());
        {
            if (QQ.ErrorMsg != nullptr)
                delete[] QQ.ErrorMsg;
            int length = UnPack.GetShort();
            QQ.ErrorMsg = new char8_t[length + 1];
            memcpy(QQ.ErrorMsg, UnPack.GetBin(length), length);
            QQ.ErrorMsg[length] = 0;
        }
        break;
    case 0x161:
        UnPack.GetShort();
        break;
    case 0x163:
        /* 未知 */
        break;
    case 0x164:
        if (QQ.Cookie.sid != nullptr)
            delete[] QQ.Cookie.sid;
        QQ.Cookie.sid = new byte[len];
        memcpy(QQ.Cookie.sid, bin, len);
        break;
    case 0x165:
        /* 请输入图中字符，帮助我们完成安全测试 */
        break;
    case 0x16A:
        if (QQ.Token.token_16A != nullptr)
            delete[] QQ.Token.token_16A;
        QQ.Token.token_16A = new byte[len];
        memcpy(QQ.Token.token_16A, bin, len);
        break;
    case 0x16D:
        if (QQ.Cookie.superKey != nullptr)
            delete[] QQ.Cookie.superKey;
        QQ.Cookie.superKey = new char[len + 1];
        QQ.Cookie.superKey[len] = 0;
        memcpy(QQ.Cookie.superKey, bin, len);
        break;
    case 0x174:
        if (QQ.Login->SmsToken != nullptr)
            delete[] QQ.Login->SmsToken;
        QQ.Login->SmsToken = new char[len + 1];
        QQ.Login->SmsToken[len] = 0;
        memcpy(QQ.Login->SmsToken, bin, len);
        break;
    case 0x178:
    {
        UnPack.GetBin(UnPack.GetShort());
        uint length = UnPack.GetShort();
        if (QQ.Login->PhoneNumber != nullptr)
            delete[] QQ.Login->PhoneNumber;
        QQ.Login->PhoneNumber = new char[length + 1];
        QQ.Login->PhoneNumber[length] = 0;
        memcpy(QQ.Login->PhoneNumber, UnPack.GetBin(length), length);
    }
    break;
    case 0x179:
        UnPack.GetShort();
        break;
    case 0x17B:
        /* 未知 */
        break;
    case 0x17D:
        /* 网址 */
        break;
    case 0x17E:
        /* 为保障你的QQ帐号安全，当前设备需进行身份验证，通过后下次无需验证。 */
        break;
    case 0x192:
        if (QQ.Login->Viery_Ticket != nullptr)
            delete[] QQ.Login->Viery_Ticket;
        QQ.Login->Viery_Ticket = new char[len + 1];
        QQ.Login->Viery_Ticket[len] = 0;
        memcpy(QQ.Login->Viery_Ticket, bin, len);
        break;
    case 0x197:
        break;
    case 0x204:
        /* 网址,过设备锁方式 */
        break;
    case 0x305:
        if (QQ.Token.D2Key != nullptr)
            delete[] QQ.Token.D2Key;
        QQ.Token.D2Key = new byte[len];
        memcpy(QQ.Token.D2Key, bin, len);
        break;
    case 0x322:
        break;
    case 0x402:
        if (QQ.Login->token_402 != nullptr)
            delete[] QQ.Login->token_402;
        QQ.Login->token_402 = new byte[len];
        memcpy(QQ.Login->token_402, bin, len);
        break;
    case 0x403:
        if (QQ.Login->token_403 != nullptr)
            delete[] QQ.Login->token_403;
        QQ.Login->token_403 = new byte[len];
        memcpy(QQ.Login->token_403, bin, len);
        break;
    case 0x508:
        /* 懒得整 */
        break;
    case 0x512:
    {
        unsigned short length = UnPack.GetShort();
        QQ.Cookie.p_skey.resize(length);
        for (size_t i = 0; i < length; i++)
        {
            unsigned short l = UnPack.GetShort();
            QQ.Cookie.p_skey[i].host = new char[l + 1];
            QQ.Cookie.p_skey[i].host[l] = 0;
            memcpy(QQ.Cookie.p_skey[i].host, UnPack.GetBin(l), l);
            l = UnPack.GetShort();
            QQ.Cookie.p_skey[i].p_skey = new char[l + 1];
            QQ.Cookie.p_skey[i].p_skey[l] = 0;
            memcpy(QQ.Cookie.p_skey[i].p_skey, UnPack.GetBin(l), l);
            UnPack.GetShort();
        }
    }
    break;
    case 0x515:
        break;
    case 0x522:
        UnPack.GetInt();
        UnPack.GetInt();  /* QQ */
        UnPack.GetBin(4); /* IP */
        UnPack.GetInt();  /* Time */
        UnPack.GetInt();  /* SUB_APPID */
        break;
    case 0x528:
        /* {"QIM_invitation_bit":"1"} */
        break;
    case 0x537:
        UnPack.GetShort();
        UnPack.GetInt();
        UnPack.GetInt(); /* QQ */
        UnPack.GetByte();
        UnPack.GetBin(4); /* IP */
        UnPack.GetInt();  /* Time */
        UnPack.GetInt();  /* SUB_APPID */
        break;
    case 0x543:
        break;
    case 0x546:
        if (QQ.Login->ClientPow != nullptr)
            delete[] QQ.Login->ClientPow;
        QQ.Login->ClientPow = new byte[len];
        memcpy(QQ.Login->ClientPow, bin, len);
        break;
    case 0x550:

        break;
    default:
        /* throw "Unknown Tlv"; */
        break;
    }
}

void Android::Unpack_Body_Request_Packet(const LPBYTE BodyBin, LPBYTE &sBuffer)
{
    UnJce UnJce(BodyBin);
    UnJce.Read(sBuffer, 7);
}

void Android::Unpack_wtlogin(const LPBYTE BodyBin, const uint sso_seq)
{
    ::UnPack UnPack(BodyBin);
    UnPack.GetByte();
    const uint len = UnPack.GetShort() - 1 - 2 - 2 - 2 - 2 - 4 - 2 - 1 - 1;
    UnPack.GetShort(); /* version */
    UnPack.GetShort(); /* command */
    UnPack.GetShort(); /* 1 */
    UnPack.GetInt();   /* uin */
    UnPack.GetByte();
    byte encrypt_type = UnPack.GetByte();
    QQ.Login->state = UnPack.GetByte();

    const byte *Buffer = nullptr;
    Buffer = UnPack.GetBin(len);
    std::vector<byte> data;

    switch (encrypt_type)
    {
    case 0:
        if (QQ.Login->state == 180)
        {
            Tea::decrypt(QQ.Login->RandKey, Buffer, len, data);
        }
        else
        {
            byte *key = Utils::MD5(QQ.Login->ECDH.sharekey, 16);
            Tea::decrypt(key, Buffer, len, data);
            delete[] key;
        }
        break;
    case 3:
        Tea::decrypt(QQ.Token.wtSessionTicketKey, Buffer, len, data);
        break;
    case 4:
    {
        QQ.Login->ECDH.pubkeyLen = UnPack.GetShort();
        memcpy(QQ.Login->ECDH.pubkey, UnPack.GetBin(QQ.Login->ECDH.pubkeyLen), QQ.Login->ECDH.pubkeyLen);
        Utils::Ecdh_CountSharekey(QQ.Login->ECDH);
        byte *key = Utils::MD5(QQ.Login->ECDH.sharekey, QQ.Login->ECDH.sharekeyLen);
        std::vector<byte> buffer;
        Tea::decrypt(key, UnPack.GetCurrentPoint(), UnPack.GetLeftLength(), buffer);
        delete[] key;
        UnPack.Reset(&buffer);
    }
    break;
    default:
        break;
    }

    UnPack.Reset(&data);

    /*
     * 0 登录成功
     * 1 密码错误
     * 2 验证码
     * 32 被回收
     * 40 被冻结
     * 160 设备锁
     * 162 短信发送失败
     * 163 短信验证码错误
     * 180 回滚 (ecdh错误, ...)
     * 204 设备锁 验证
     * 235 版本过低
     * 237 上网环境异常
     * 239 设备锁
     * 243 非法来源禁止登录
     */
    switch (QQ.Login->state)
    {
    case 204:
        Fun_Send_Sync(10, 2, "wtlogin.login", wtlogin::login_Viery_204(),
                      [&](uint sso_seq, LPBYTE BodyBin)
                      {
                          Unpack_wtlogin(BodyBin, sso_seq);
                      });
        break;
    }
    UnPack.GetShort();
    UnPack.GetByte();
    unsigned short Count = UnPack.GetShort();
    for (size_t i = 0; i < Count; i++)
    {
        unsigned short cmd = UnPack.GetShort();
        unsigned short binlen = UnPack.GetShort();
        Un_Tlv_Get(cmd, UnPack.GetBin(binlen), binlen);
    }
}

void Android::Unpack_OnlinePush_PbPushGroupMsg(const LPBYTE BodyBin, const uint sso_seq)
{
    Event::GroupMsg GroupMsg;
    ::UnProtobuf UnPB(BodyBin);
    UnPB.StepIn(1);
    UnPB.StepIn(1);
    if ((GroupMsg.FromQQ = UnPB.GetVarint(1)) == QQ.QQ)
        return;
    GroupMsg.MsgType = UnPB.GetVarint(3);
    GroupMsg.MsgID = UnPB.GetVarint(5);
    GroupMsg.SendTime = UnPB.GetVarint(6);
    UnPB.StepIn(9);
    GroupMsg.FromGroup = UnPB.GetVarint(1);
    GroupMsg.FromQQName = UnPB.GetStr(4);
    GroupMsg.FromGroupName = UnPB.GetStr(8);
    UnPB.StepOut();
    UnPB.StepOut();
    UnPB.StepIn(3);
    UnPB.StepIn(1);
    UnPB.StepIn(1);
    GroupMsg.MsgRand = UnPB.GetVarint(3);
    UnPB.StepOut();
    Message::Msg *ThisMsg = nullptr;
    while (UnPB.GetField() == 2)
    {
        UnPB.StepIn(2);
        switch (UnPB.GetField())
        {
#define UnPack(id)                                 \
    case id:                                       \
        if (GroupMsg.Msg == nullptr)               \
        {                                          \
            UnPack##id(&UnPB, ThisMsg);            \
            GroupMsg.Msg = ThisMsg;                \
        }                                          \
        else                                       \
        {                                          \
            UnPack##id(&UnPB, ThisMsg->NextPoint); \
            if (ThisMsg->NextPoint != nullptr)     \
                ThisMsg = ThisMsg->NextPoint;      \
        }                                          \
        break;

            UnPack(1);  /* 文字和At */
            UnPack(2);  /* 小黄豆 */
            UnPack(5);  /* 文件 */
            UnPack(6);  /* 原创表情 */
            UnPack(8);  /* 图片 */
            UnPack(9);  /* 气泡消息 */
            UnPack(12); /* xml */
            UnPack(16);
            UnPack(24); /* 红包 */
            UnPack(33); /* 小视频 */
            UnPack(37);
            UnPack(45); /* 回复 */
            UnPack(51); /* json */
            UnPack(53); /* 吃瓜等新表情 */
        default:
            Log::AddLog(Log::LogType::NOTICE, Log::MsgType::_GROUP, u8"OnlinePush.PbPushGroupMsg", u8"unknown MsgType: %d", true, UnPB.GetField());
            break;
        }
        UnPB.StepOut();

#undef UnPack
    }
    UnPB.StepOut();
    UnPB.StepOut();
    UnPB.StepOut();

#ifdef DEBUG
    if (GroupMsg.FromGroup == 635275515)
    {
        if (GroupMsg.Msg->MsgType == Message::MsgType::text)
            if (!strcmp((char *)((Message::text *)GroupMsg.Msg->Message)->text, "pause"))
            {
                DebugBreak();
            }
            else
            {
                /* QQ_SetGroupAdmin(GroupMsgY.FromGroup, GroupMsg.FromQQ, true); */
                QQ_SendMsg(GroupMsg.FromGroup, 1, GroupMsg.Msg);
            }
    }
#endif

    if (GroupMsg.Msg != nullptr)
        Event::OnGroupMsg(&GroupMsg);
    Message::DestoryMsg(GroupMsg.Msg);
}

void Android::Unpack_OnlinePush_PbPushTransMsg(const LPBYTE BodyBin, const uint sso_seq)
{
    ::UnProtobuf UnPB(BodyBin);
    uint Type = UnPB.GetVarint(3);
    UnPack UnPack(UnPB.GetBin(10));
    ;
    byte SubType;
    switch (Type)
    {
    case 34:
    {
        Event::NoticeEvent::NoticeEvent NoticeEvent{Event::NoticeEvent::NoticeEventType::group_memberchange, new Event::NoticeEvent::group_memberchange};
        ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->FromGroup = UnPack.GetInt();
        UnPack.Skip(1);
        ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
        SubType = UnPack.GetByte();
        switch (SubType)
        {
        case 2:
            ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->Type = 2;
            break;
        case 3:
            ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->Type = 3;
            ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->OperateQQ = UnPack.GetInt();
            break;
        case 130:
            ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->Type = 2;
            break;
        case 131:
            ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->Type = 3;
            ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->OperateQQ = UnPack.GetInt();
            break;
        case 142:
            ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->Type = 4;
            break;
        default:
            Log::AddLog(Log::LogType::NOTICE, Log::MsgType::_GROUP, u8"OnlinePush.PbPushTransMsg", u8"unknown MsgType: %u", true, SubType);
            break;
        }
        Event::OnNoticeMsg(&NoticeEvent);
    }

    break;
    case 44:
    {
        Event::NoticeEvent::NoticeEvent NoticeEvent{Event::NoticeEvent::NoticeEventType::group_adminchange, new Event::NoticeEvent::group_adminchange};
        ((Event::NoticeEvent::group_adminchange *)NoticeEvent.Information)->FromGroup = UnPack.GetInt();
        UnPack.Skip(1);
        SubType = UnPack.GetByte();
        switch (SubType)
        {
        case 0: /* cancle */
            ((Event::NoticeEvent::group_adminchange *)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
            ((Event::NoticeEvent::group_adminchange *)NoticeEvent.Information)->Type = UnPack.GetByte();
            break;
        case 1: /* set */
            ((Event::NoticeEvent::group_adminchange *)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
            ((Event::NoticeEvent::group_adminchange *)NoticeEvent.Information)->Type = UnPack.GetByte();
            break;
        case 0xFF: /* transfer */
            ((Event::NoticeEvent::group_adminchange *)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
            ((Event::NoticeEvent::group_adminchange *)NoticeEvent.Information)->Type = 2;
            break;
        default:
            Log::AddLog(Log::LogType::NOTICE, Log::MsgType::_GROUP, u8"OnlinePush.PbPushTransMsg", u8"unknown SubType: %u", true, SubType);
            break;
            Event::OnNoticeMsg(&NoticeEvent);
        }
    }
    break;
    default:
        Log::AddLog(Log::LogType::NOTICE, Log::MsgType::_GROUP, u8"OnlinePush.PbPushTransMsg", u8"unknown SubType: %u", true, Type);
        break;
    }
}

void Android::Unpack_OnlinePush_PbC2CMsgSync(const LPBYTE BodyBin, const uint sso_seq)
{
}

void Android::Unpack_OnlinePush_ReqPush(const LPBYTE BodyBin, const uint sso_seq)
{
    LPBYTE sBuffer;
    Unpack_Body_Request_Packet(BodyBin + 4, sBuffer);

    UnJce UnJce(sBuffer);
    std::vector<JceStruct::Map<char *, std::vector<JceStruct::Map<char *, LPBYTE>>>> Map;
    UnJce.Read(Map, 0);
    for (size_t i = 0; i < Map.size(); i++)
    {
        for (size_t j = 0; j < Map[i].Value.size(); j++)
        {
            UnJce.Reset(Map[i].Value[j].Value);
            UnJce.Read(UnJce, 0);

            std::vector<::UnJce> list;
            int del_infos;
            UnJce.Read(list, 2);
            UnJce.Read(del_infos, 3);
            std::vector<std::tuple<int, int, LPBYTE>> infos;
            for (size_t k = 0; k < list.size(); k++)
            {
                int from_uin;
                int msg_type;
                int msg_seq;
                LPBYTE v_msg;
                LPBYTE msg_cookies;
                list[k].Read(from_uin, 0);
                list[k].Read(msg_type, 2);
                list[k].Read(msg_seq, 3);
                list[k].Read(v_msg, 8);
                list[k].Read(msg_cookies, 8);

                switch (msg_type)
                {
                case 528:
                {
                    int sub_msg_type;
                    LPBYTE v_protobuf;
                    ::UnJce UnJce(v_msg);
                    UnJce.Read(sub_msg_type, 0);
                    UnJce.Read(v_protobuf, 1);
                    UnProtobuf UnPB(v_protobuf);
                    switch (sub_msg_type)
                    {
                    case 0x27:
                        break;
                    case 0x44:
                        break;
                    case 0x8A:
                    case 0x8B:
                    {
                    }
                    break;
                    case 0xB3:
                        break;
                    case 0xD4:
                        break;
                    case 0x122:
                    case 0x123:
                        break;
                    }
                    delete[] v_protobuf;
                }
                break;
                case 732:
                {
                    UnPack UnPack(v_msg);
                    uint group_code = UnPack.GetInt();
                    byte i_type = UnPack.GetByte();
                    UnPack.GetByte();
                    switch (i_type)
                    {
                    case 0x10:
                    case 0x11: // 群消息撤回
                    case 0x14:
                    case 0x15:
                    {
                        int len = UnPack.GetByte();
                        UnProtobuf UnPB(UnPack.GetBin(len), len);
                        UnPB.StepIn(11);
                        uint uin = UnPB.GetVarint(1);
                        while (UnPB.GetField() == 3)
                        {
                            Event::GroupWithdrawMsg GroupWithdrawMsg;
                            GroupWithdrawMsg.FromGroup = group_code;
                            GroupWithdrawMsg.OperateQQ = uin;
                            UnPB.StepIn(3);
                            GroupWithdrawMsg.MsgID = UnPB.GetVarint(1);
                            GroupWithdrawMsg.SendTime = UnPB.GetVarint(2);
                            GroupWithdrawMsg.MsgRand = UnPB.GetVarint(3);
                            GroupWithdrawMsg.MsgType = UnPB.GetVarint(4);
                            GroupWithdrawMsg.FromQQ = UnPB.GetVarint(6);
                            UnPB.StepOut();

                            Event::NoticeEvent::NoticeEvent NoticeEvent{Event::NoticeEvent::NoticeEventType::group_recall, new Event::NoticeEvent::group_recall{GroupWithdrawMsg.FromGroup, GroupWithdrawMsg.FromQQ, GroupWithdrawMsg.OperateQQ, Database::UpdataGroupMsgState(GroupWithdrawMsg.MsgID, GroupWithdrawMsg.MsgRand), GroupWithdrawMsg.SendTime}};
                            Event::OnNoticeMsg(&NoticeEvent);
                        }
                        UnPB.StepOut();
                    }
                    break;
                    case 0x0c: // 全群禁言
                    {
                        Event::NoticeEvent::NoticeEvent NoticeEvent{Event::NoticeEvent::NoticeEventType::group_mute, new Event::NoticeEvent::group_mute};
                        ((Event::NoticeEvent::group_mute *)NoticeEvent.Information)->FromGroup = group_code;
                        ((Event::NoticeEvent::group_mute *)NoticeEvent.Information)->OperateQQ = UnPack.GetInt();
                        ((Event::NoticeEvent::group_mute *)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
                        ((Event::NoticeEvent::group_mute *)NoticeEvent.Information)->Duration = UnPack.GetInt();
                        Event::OnNoticeMsg(&NoticeEvent);
                    }
                    break;
                    default:
                        break;
                    }
                }
                break;
                default:
                    break;
                }
                infos.emplace_back(std::tuple(from_uin, msg_seq, msg_cookies));
            }
            Fun_Send(11, 1, "OnlinePush.RespPush", OnlinePush::RespPush(sso_seq, del_infos, infos));
        }
    }
}

void Android::Unpack_MessageSvc_PushNotify(const LPBYTE BodyBin, const uint sso_seq)
{
    LPBYTE sBuffer;
    Unpack_Body_Request_Packet(BodyBin + 4, sBuffer);

    UnJce UnJce(sBuffer);
    std::vector<JceStruct::Map<char *, std::vector<JceStruct::Map<char *, LPBYTE>>>> Map;
    UnJce.Read(Map, 0);
    for (size_t i = 0; i < Map.size(); i++)
    {
        for (size_t j = 0; j < Map[i].Value.size(); j++)
        {
            UnJce.Reset(Map[i].Value[j].Value);
            UnJce.Read(UnJce, 0);

            LPBYTE serverBuf = nullptr;
            UnJce.Read(serverBuf, 11);

            Fun_Send_Sync(11, 1, "MessageSvc.PbGetMsg", MessageSvc::PbGetMsg(serverBuf),
                          [&](uint sso_seq, LPBYTE BodyBin)
                          {
                              UnProtobuf UnPB(BodyBin);

                              UnPB.GetBin(3); /* SyncCookies */
                              UnPB.GetVarint(4);
                              while (UnPB.GetField() == 5)
                              {
                                  UnPB.StepIn(5);
                                  UnPB.GetVarint(3);
                                  while (UnPB.GetField() == 4)
                                  {
                                      Event::PrivateMsg PrivateMsg;
                                      UnPB.StepIn(4);
                                      UnPB.StepIn(1);
                                      PrivateMsg.FromQQ = UnPB.GetVarint(1);
                                      uint MsgType = UnPB.GetVarint(3);
                                      PrivateMsg.MsgType = UnPB.GetVarint(4);
                                      PrivateMsg.MsgID = UnPB.GetVarint(5);
                                      UnPB.StepOut();
                                      Log::AddLog(Log::LogType::NOTICE, Log::MsgType::OTHER, u8"MessageSvc.PbGetMsg", u8"MsgType: %u", true, MsgType);
                                      switch (MsgType)
                                      {
                                      case 33:
                                      {
                                          UnPB.StepIn(3);
                                          UnPack UnPack(UnPB.GetBin(2));
                                          Event::NoticeEvent::NoticeEvent NoticeEvent{Event::NoticeEvent::NoticeEventType::group_memberchange, new Event::NoticeEvent::group_memberchange};
                                          ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->FromGroup = UnPack.GetInt();
                                          UnPack.Skip(1);
                                          ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
                                          switch (UnPack.GetByte())
                                          {
                                          case 130:
                                              ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->Type = 0;
                                              break;
                                          case 131:
                                              ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->Type = 0;
                                              ((Event::NoticeEvent::group_memberchange *)NoticeEvent.Information)->OperateQQ = UnPack.GetInt();
                                              break;
                                          }
                                          UnPB.StepOut();
                                          Event::OnNoticeMsg(&NoticeEvent);
                                          Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &NoticeEvent);
                                      }
                                      break;
                                      case 35:
                                      case 36:
                                      case 37:
                                      case 45:
                                      case 46:
                                      case 84: // 申请进群
                                      case 85:
                                      case 86:
                                      case 87:
                                          Fun_Send_Sync(11, 1, "ProfileService.Pb.ReqSystemMsgNew.Group", ProfileService::Pb_ReqSystemMsgNew_Group(),
                                                        [&](uint sso_seq, LPBYTE BodyBin)
                                                        {
                                                            UnProtobuf UnPB(BodyBin);
                                                            UnPB.GetVarint(7);
                                                            while (UnPB.GetField() == 10)
                                                            {
                                                                UnPB.StepIn(10);
                                                                uint msgSeq = UnPB.GetVarint(3);
                                                                uint reqUin = UnPB.GetVarint(5);
                                                                UnPB.StepIn(50);
                                                                uint subType = UnPB.GetVarint(1);
                                                                char8_t *msgAdditional = UnPB.GetStr(4);
                                                                uint groupCode = UnPB.GetVarint(10);
                                                                uint actionUin = UnPB.GetVarint(11);
                                                                uint groupMsgType = UnPB.GetVarint(12);
                                                                char8_t *reqUinNick = UnPB.GetStr(51);
                                                                char8_t *groupName = UnPB.GetStr(52);
                                                                char8_t *actionUinQqNick = UnPB.GetStr(65);

                                                                switch (subType)
                                                                {
                                                                case 1: /* 进群申请 */
                                                                    switch (groupMsgType)
                                                                    {
                                                                    case 1:
                                                                    {
                                                                        Event::RequestEvent::RequestEvent RequestEvent{Event::RequestEvent::RequestEventType::other_join_group, new Event::RequestEvent::other_join_group};

                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromGroup = groupCode;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromQQ = reqUin;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromGroupName = groupName;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromQQName = reqUinNick;

                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->msg = msgAdditional;

                                                                        Event::OnRequestMsg(&RequestEvent, msgSeq);
                                                                        Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &RequestEvent);
                                                                    }
                                                                    break;
                                                                    case 2:
                                                                    {
                                                                        Event::RequestEvent::RequestEvent RequestEvent{Event::RequestEvent::RequestEventType::self_invited, new Event::RequestEvent::self_invited};

                                                                        ((Event::RequestEvent::self_invited *)RequestEvent.Information)->FromGroup = groupCode;
                                                                        ((Event::RequestEvent::self_invited *)RequestEvent.Information)->InvitorQQ = actionUin;
                                                                        ((Event::RequestEvent::self_invited *)RequestEvent.Information)->FromGroupName = groupName;
                                                                        ((Event::RequestEvent::self_invited *)RequestEvent.Information)->InvitorQQName = actionUinQqNick;

                                                                        Event::OnRequestMsg(&RequestEvent, msgSeq);
                                                                        Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &RequestEvent);
                                                                    }
                                                                    case 22:
                                                                    {
                                                                        Event::RequestEvent::RequestEvent RequestEvent{Event::RequestEvent::RequestEventType::other_join_group, new Event::RequestEvent::other_join_group};

                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromGroup = groupCode;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromQQ = reqUin;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromGroupName = groupName;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->FromQQName = reqUinNick;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->InvitorQQ = actionUin;
                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->InvitorQQName = actionUinQqNick;

                                                                        ((Event::RequestEvent::other_join_group *)RequestEvent.Information)->msg = msgAdditional;

                                                                        Event::OnRequestMsg(&RequestEvent, msgSeq);
                                                                        Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &RequestEvent);
                                                                    }
                                                                    default:
                                                                        break;
                                                                    }
                                                                    break;
                                                                case 2: /* 被邀请(<50人自动加入,不需要处理) */
                                                                    break;
                                                                case 5: /* 自身状态变更(管理员/加群退群) */
                                                                    break;
                                                                }
                                                                UnPB.StepOut();
                                                                UnPB.StepOut();
                                                            }
                                                        });
                                          break;
                                      case 166:
                                      {
                                          UnPB.StepIn(3);
                                          UnPB.StepIn(1);
                                          UnPB.StepIn(1);
                                          PrivateMsg.SendTime = UnPB.GetVarint(2);
                                          PrivateMsg.MsgRand = UnPB.GetVarint(3);
                                          UnPB.StepOut();
                                          Message::Msg *ThisMsg = nullptr;
                                          while (UnPB.GetField() == 2)
                                          {
                                              UnPB.StepIn(2);
                                              switch (UnPB.GetField())
                                              {

#define UnPack(id)                                 \
    case id:                                       \
        if (PrivateMsg.Msg == nullptr)             \
        {                                          \
            UnPack##id(&UnPB, ThisMsg);            \
            PrivateMsg.Msg = ThisMsg;              \
        }                                          \
        else                                       \
        {                                          \
            UnPack##id(&UnPB, ThisMsg->NextPoint); \
            if (ThisMsg->NextPoint != nullptr)     \
                ThisMsg = ThisMsg->NextPoint;      \
        }                                          \
        break;

                                                  UnPack(1);  /* 文字和At */
                                                  UnPack(2);  /* 小黄豆 */
                                                  UnPack(4);  /* 图片5 */
                                                  UnPack(5);  /* 文件 */
                                                  UnPack(6);  /* 原创表情 */
                                                  UnPack(8);  /* 图片 */
                                                  UnPack(9);  /* 气泡消息 */
                                                  UnPack(12); /* xml */
                                                  UnPack(16);
                                                  UnPack(24); /* 红包 */
                                                  UnPack(33); /* 小视频 */
                                                  UnPack(37);
                                                  UnPack(45); /* 回复 */
                                                  UnPack(51); /* json */
                                                  UnPack(53); /* 吃瓜等新表情 */

#undef UnPack
                                              }
                                              UnPB.StepOut();
                                          }
                                          UnPB.StepOut();
                                          UnPB.StepOut();

                                          if (PrivateMsg.Msg != nullptr)
                                              Event::OnPrivateMsg(&PrivateMsg);
                                          Message::DestoryMsg(PrivateMsg.Msg);
                                      }
                                      break;
                                      case 187: // 加好友
                                      case 188:
                                      case 189:
                                      case 190:
                                      case 191:
                                          Fun_Send_Sync(11, 1, "ProfileService.Pb.ReqSystemMsgNew.Friend", ProfileService::Pb_ReqSystemMsgNew_Friend(),
                                                        [&](uint sso_seq, LPBYTE BodyBin)
                                                        {
                                                            UnProtobuf UnPB(BodyBin);
                                                            UnPB.GetVarint(6);
                                                            while (UnPB.GetField() == 9)
                                                            {
                                                                UnPB.StepIn(9);
                                                                uint msgSeq = UnPB.GetVarint(3);
                                                                uint reqUin = UnPB.GetVarint(5);
                                                                UnPB.StepIn(50);
                                                                uint subType = UnPB.GetVarint(1);
                                                                char8_t *msgAdditional = UnPB.GetStr(4);
                                                                char8_t *reqUinNick = UnPB.GetStr(51);

                                                                switch (subType)
                                                                {
                                                                case 1: // 好友申请
                                                                {
                                                                    Event::RequestEvent::RequestEvent RequestEvent{Event::RequestEvent::RequestEventType::add_friend, new Event::RequestEvent::add_friend};

                                                                    ((Event::RequestEvent::add_friend *)RequestEvent.Information)->FromQQ = reqUin;
                                                                    ((Event::RequestEvent::add_friend *)RequestEvent.Information)->FromQQName = reqUinNick;

                                                                    ((Event::RequestEvent::add_friend *)RequestEvent.Information)->msg = msgAdditional;

                                                                    Event::OnRequestMsg(&RequestEvent, msgSeq);
                                                                    Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &RequestEvent);
                                                                }
                                                                break;
                                                                case 3: // 已同意
                                                                    break;
                                                                case 7: // 已拒绝
                                                                    break;
                                                                default:
                                                                    break;
                                                                }
                                                            }
                                                        });
                                          break;
                                      default:
                                          Log::AddLog(Log::LogType::NOTICE, Log::MsgType::OTHER, u8"MessageSvc.PbGetMsg", u8"unknown MsgType: %u", true, MsgType);
                                          break;
                                      }
                                      UnPB.StepOut();
                                  }
                                  UnPB.StepOut();
                              }
                          });

            delete serverBuf;

            delete[] Map[i].Value[j].Key;
            delete[] Map[i].Value[j].Value;
        }

        delete[] Map[i].Key;
    }
    delete[] sBuffer;
}

void Android::Unpack_MessageSvc_PushForceOffline(const LPBYTE BodyBin, const uint sso_seq)
{
    QQ_Offline();
    // QQ_Online();
}

void Android::Unpack_StatSvc_QueryHB(const LPBYTE BodyBin, const uint sso_seq)
{
    QQ_Online();
}

void Android::Unpack_StatSvc_SvcReqMSFLoginNotify(const LPBYTE BodyBin, const uint sso_seq)
{
    LPBYTE sBuffer;
    Unpack_Body_Request_Packet(BodyBin, sBuffer);

    UnJce UnJce(sBuffer);
    std::vector<JceStruct::Map<char *, std::vector<JceStruct::Map<char *, LPBYTE>>>> Map;
    UnJce.Read(Map, 0);

    for (size_t i = 0; i < Map.size(); i++)
    {
        for (size_t j = 0; j < Map[i].Value.size(); j++)
        {
            UnJce.Reset(Map[i].Value[j].Value);
            UnJce.Read(UnJce, 0);

            delete[] Map[i].Value[j].Key;
            delete[] Map[i].Value[j].Value;
        }

        delete[] Map[i].Key;
    }
    delete[] sBuffer;
}

void Android::Unpack_ConfigPushSvc_PushReq(const LPBYTE BodyBin, const uint sso_seq)
{
    LPBYTE sBuffer;
    Unpack_Body_Request_Packet(BodyBin + 4, sBuffer);

    UnJce UnJce(sBuffer);
    std::vector<JceStruct::Map<char *, std::vector<JceStruct::Map<char *, LPBYTE>>>> Map;
    UnJce.Read(Map, 0);

    for (size_t i = 0; i < Map.size(); i++)
    {
        for (size_t j = 0; j < Map[i].Value.size(); j++)
        {
            UnJce.Reset(Map[i].Value[j].Value);
            UnJce.Read(UnJce, 0);

            int type;
            UnJce.Read(type, 1);

            LPBYTE data;
            UnJce.Read(data, 2);
            UnJce.Reset(data);

            if (type == 1) /* need redirect */
            {
                Log::AddLog(Log::LogType::NOTICE, Log::MsgType::OTHER, u8"Online", u8"Need Redirect");
                std::vector<::UnJce> ipl;
                UnJce.Read(ipl, 0);

                char *IP;
                int Port;

                int r = Utils::GetRandom(0, ipl.size() - 1);
                ipl[r].Read(IP, 1);
                ipl[r].Read(Port, 2);

                Fun_Connect(IP, Port);
                QQ_Online();

                delete[] IP;
            }

            std::vector<::UnJce> ipl;
            UnJce.Read(ipl, 3);
            int r = Utils::GetRandom(0, ipl.size() - 1);
            if (QQ.sig.UploadVoice_IP != nullptr)
                delete[] QQ.sig.UploadVoice_IP;
            ipl[r].Read(QQ.sig.UploadVoice_IP, 1);
            ipl[r].Read(QQ.sig.UploadVoice_Port, 2);
            delete[] data;

            UnJce.Read(UnJce, 5);

            if (QQ.sig.UploadVoice_ukey != nullptr)
                delete[] QQ.sig.UploadVoice_ukey;
            UnJce.Read(QQ.sig.UploadVoice_ukey, 1);

            delete[] Map[i].Value[j].Key;
            delete[] Map[i].Value[j].Value;
        }

        delete[] Map[i].Key;
    }
    delete[] sBuffer;
}

void Android::QQ_Init(const char *Account)
{
    QQ.QQ = std::strtoll(Account, NULL, 0);
    if (QQ.QQ_Str != nullptr)
        delete[] QQ.QQ_Str;
    QQ.QQ_Str = new char[strlen(Account) + 1];
    memcpy(QQ.QQ_Str, Account, strlen(Account) + 1);
}

/*
 * / <summary>
 * / 登录
 * / </summary>
 * / <param name="Password">密码</param>
 * / <returns>LOGIN_</returns>
 */
int Android::QQ_Login(const char *Password)
{
    if (QQ.Token.md5 != nullptr)
        delete[] QQ.Token.md5;
    QQ.Token.md5 = Utils::MD5((byte *)Password, strlen(Password));
    byte tmp[24] = {0};
    memcpy(tmp, QQ.Token.md5, 16);
    byte *bin = XBin::Int2Bin(QQ.QQ);
    memcpy(tmp + 20, bin, 4);
    delete[] bin;
    if (QQ.Token.md52 != nullptr)
        delete[] QQ.Token.md52;
    QQ.Token.md52 = Utils::MD5(tmp, 24);
    QQ.Token.TGTkey = Utils::GetRandomBin(16);
    QQ.Login = new QQ::Login;
    QQ.Login->RandKey = Utils::GetRandomBin(16);

    /* secp192k1
     * byte PublicKey[] = {
     *  0x04, 0x92, 0x8D, 0x88, 0x50, 0x67, 0x30, 0x88, 0xB3, 0x43,
     *  0x26, 0x4E, 0x0C, 0x6B, 0xAC, 0xB8, 0x49, 0x6D, 0x69, 0x77,
     *  0x99, 0xF3, 0x72, 0x11, 0xDE, 0xB2, 0x5B, 0xB7, 0x39, 0x06,
     *  0xCB, 0x08, 0x9F, 0xEA, 0x96, 0x39, 0xB4, 0xE0, 0x26, 0x04,
     *  0x98, 0xB5, 0x1A, 0x99, 0x2D, 0x50, 0x81, 0x3D, 0xA8};
     * Utils::Ecdh_Crypt(QQ.Login->ECDH, PublicKey, 0x31);
     */
    /* prime256v1 */
    unsigned char PublicKey[] = {
        0x04, 0xEB, 0xCA, 0x94, 0xD7, 0x33, 0xE3, 0x99, 0xB2, 0xDB,
        0x96, 0xEA, 0xCD, 0xD3, 0xF6, 0x9A, 0x8B, 0xB0, 0xF7, 0x42,
        0x24, 0xE2, 0xB4, 0x4E, 0x33, 0x57, 0x81, 0x22, 0x11, 0xD2,
        0xE6, 0x2E, 0xFB, 0xC9, 0x1B, 0xB5, 0x53, 0x09, 0x8E, 0x25,
        0xE3, 0x3A, 0x79, 0x9A, 0xDC, 0x7F, 0x76, 0xFE, 0xB2, 0x08,
        0xDA, 0x7C, 0x65, 0x22, 0xCD, 0xB0, 0x71, 0x9A, 0x30, 0x51,
        0x80, 0xCC, 0x54, 0xA8, 0x2E};
    Utils::Ecdh_Crypt(QQ.Login->ECDH, PublicKey, 0x41);

    Fun_Connect();
    Fun_Send_Sync(10, 2, "wtlogin.login", wtlogin::login(),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      Unpack_wtlogin(BodyBin, sso_seq);
                  });
    return (QQ.Login->state);
}

int Android::QQ_Login_Second()
{
    byte tmp[24] = {0};
    memcpy(tmp, QQ.Token.md5, 16);
    byte *bin = XBin::Int2Bin(QQ.QQ);
    memcpy(tmp + 20, bin, 4);
    delete[] bin;
    if (QQ.Token.md52 != nullptr)
        delete[] QQ.Token.md52;
    QQ.Token.md52 = Utils::MD5(tmp, 24);
    QQ.Login = new QQ::Login;
    Fun_Connect();

    /* QQ_SyncCookie(); */
    return (QQ.Login->state);
}

void Android::QQ_Login_Finish()
{
    if (QQ.Login == nullptr)
        return;
    if (QQ.Login->RandKey != nullptr)
        delete[] QQ.Login->RandKey;
    if (QQ.Login->VieryToken1 != nullptr)
        delete[] QQ.Login->VieryToken1;
    if (QQ.Login->VieryToken2 != nullptr)
        delete[] QQ.Login->VieryToken2;
    if (QQ.Login->token_402 != nullptr)
        delete[] QQ.Login->token_402;
    if (QQ.Login->token_403 != nullptr)
        delete[] QQ.Login->token_403;
    if (QQ.Login->Viery_Image != nullptr)
        delete[] QQ.Login->Viery_Image;
    if (QQ.Login->Viery_Ticket != nullptr)
        delete[] QQ.Login->Viery_Ticket;
    if (QQ.Login->PhoneNumber != nullptr)
        delete[] QQ.Login->PhoneNumber;
    if (QQ.Login->SmsToken != nullptr)
        delete[] QQ.Login->SmsToken;
    delete QQ.Login;
    QQ.Login = nullptr;
}

byte Android::QQ_Send_Sms()
{
    Fun_Send_Sync(10, 2, "wtlogin.login", wtlogin::login_Send_Sms(),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      Unpack_wtlogin(BodyBin, sso_seq);
                  });
    return (QQ.Login->state);
}

byte Android::QQ_Viery_Ticket(const char *Ticket)
{
    Fun_Send_Sync(10, 2, "wtlogin.login", wtlogin::login_Viery_Ticket(Ticket),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      Unpack_wtlogin(BodyBin, sso_seq);
                  });
    return (QQ.Login->state);
}

byte Android::QQ_Viery_Sms(const char *SmsCode)
{
    Fun_Send_Sync(10, 2, "wtlogin.login", wtlogin::login_Viery_Sms(SmsCode),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      Unpack_wtlogin(BodyBin, sso_seq);
                  });
    return (QQ.Login->state);
}

char *Android::QQ_Get_Viery_Ticket()
{
    return (QQ.Login->Viery_Ticket);
}

char *Android::QQ_Get_Viery_PhoneNumber()
{
    return (QQ.Login->PhoneNumber);
}

void Android::QQ_Online()
{
    QQ_SetOnlineType(11);
    QQ.Status = 11;
    std::thread Thread(std::bind(&Android::Fun_Life_Event, this));
    Thread.detach();
    /*
     * friendlist_getFriendGroupList(0);
     * friendlist_GetTroopListReqV2();
     */
}

void Android::QQ_Offline()
{
    QQ_SetOnlineType(21);
    QQ.Status = 21;
}

/*
 * / <summary>
 * / 设置在线状态
 * / </summary>
 * / <param name="Type">11:在线 21:离线 31:离开 41:隐身 50:忙碌 60:Q我吧 70:免打扰 95:接收离线消息(离线)</param>
 */
void Android::QQ_SetOnlineType(const byte Type)
{
    Fun_Send_Sync(10, 1, "StatSvc.register", StatSvc::Register(Type),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      LPBYTE sBuffer;
                      Unpack_Body_Request_Packet(BodyBin, sBuffer);

                      UnJce UnJce(sBuffer);
                      std::vector<JceStruct::Map<char *, std::vector<JceStruct::Map<char *, LPBYTE>>>> Map;
                      UnJce.Read(Map, 0);

                      for (size_t i = 0; i < Map.size(); i++)
                      {
                          for (size_t j = 0; j < Map[i].Value.size(); j++)
                          {
                              UnJce.Reset(Map[i].Value[j].Value);
                              UnJce.Read(UnJce, 0);

                              delete[] Map[i].Value[j].Key;
                              delete[] Map[i].Value[j].Value;
                          }

                          delete[] Map[i].Key;
                      }
                      delete[] sBuffer;
                  });

    /*
     * Fun_Send_Sync(10, 1, "StatSvc.SetStatusFromClient", StatSvc::SetStatusFromClient(Type),
     *            [&](uint sso_seq, LPBYTE BodyBin)
     *            {
     *            });
     */
}

void Android::QQ_Heart_Beat()
{
    Fun_Send_Sync(10, 1, "StatSvc.SimpleGet", StatSvc::SimpleGet(),
                  [&](uint sso_seq, LPBYTE BodyBin) {
                  });
}

void Android::QQ_SyncCookie()
{
    byte tmp[24] = {0};
    memcpy(tmp, QQ.Token.md5, 16);
    byte *bin = XBin::Int2Bin(QQ.QQ);
    memcpy(tmp + 20, bin, 4);
    delete[] bin;
    if (QQ.Token.md52 != nullptr)
        delete[] QQ.Token.md52;
    QQ.Token.md52 = Utils::MD5(tmp, 24);
    QQ.Login = new QQ::Login;
    Fun_Send_Sync(10, 2, "wtlogin.exchange_emp", wtlogin::exchange_emp(),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      Unpack_wtlogin(BodyBin, sso_seq);
                  });
}

void Android::QQ_SyncFriendList(int startIndex)
{
    Fun_Send_Sync(11, 1, "friendlist.getFriendGroupList", friendlist::getFriendGroupList(startIndex),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      LPBYTE sBuffer;
                      Unpack_Body_Request_Packet(BodyBin, sBuffer);

                      UnJce UnJce(sBuffer);
                      std::vector<JceStruct::Map<char *, LPBYTE>> Map;
                      UnJce.Read(Map, 0);

                      for (size_t i = 0; i < Map.size(); i++)
                      {
                          UnJce.Reset(Map[i].Value);
                          UnJce.Read(UnJce, 0);

                          int startIndex, totoal_friend_count, get_count = 0;
                          UnJce.Read(startIndex, 3);
                          UnJce.Read(totoal_friend_count, 5);
                          UnJce.Read(get_count, 6);
                          if (startIndex + get_count < totoal_friend_count)
                              Android::QQ_SyncFriendList(startIndex + get_count);
                          if (startIndex == 0)
                              QQ.FriendList.resize(totoal_friend_count);

                          std::vector<::UnJce> Friends;
                          UnJce.Read(Friends, 7);
                          for (size_t j = 0; j < Friends.size(); j++)
                          {
                              Friends[j].Read((int &)QQ.FriendList[startIndex + j].QQ, 0);
                              Friends[j].Read(QQ.FriendList[startIndex + j].Remark, 3);
                              Friends[j].Read(QQ.FriendList[startIndex + j].status, 5);
                              Friends[j].Read(QQ.FriendList[startIndex + j].Nick, 14);
                          }

                          delete[] Map[i].Key;
                          delete[] Map[i].Value;
                      }
                      delete[] sBuffer;
                  });
}

void Android::QQ_SyncGroupList()
{
    Fun_Send_Sync(11, 1, "friendlist.GetTroopListReqV2", friendlist::GetTroopListReqV2(),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      LPBYTE sBuffer;
                      Unpack_Body_Request_Packet(BodyBin, sBuffer);

                      UnJce UnJce(sBuffer);
                      std::vector<JceStruct::Map<char *, LPBYTE>> Map;
                      UnJce.Read(Map, 0);

                      for (size_t i = 0; i < Map.size(); i++)
                      {
                          UnJce.Reset(Map[i].Value);
                          UnJce.Read(UnJce, 0);
                          /* UnJce.Read(totoal_group_count, 1); */

                          std::vector<::UnJce> Groups;
                          UnJce.Read(Groups, 5);
                          QQ.GroupList.resize(Groups.size());

                          for (size_t j = 0; j < Groups.size(); j++)
                          {
                              Groups[j].Read((int &)QQ.GroupList[j].GroupCode, 1);
                              Groups[j].Read(QQ.GroupList[j].GroupName, 4);
                              Groups[j].Read(QQ.GroupList[j].MemberCount, 19);
                              Groups[j].Read((int &)QQ.GroupList[j].MasterQQ, 23);
                          }

                          delete[] Map[i].Key;
                          delete[] Map[i].Value;
                      }
                      delete[] sBuffer;
                  });
}

void Android::QQ_SyncGroupMemberList(uint Group)
{
    Fun_Send_Sync(11, 1, "friendlist.getTroopMemberList", friendlist::getTroopMemberList(Group),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      LPBYTE sBuffer;
                      Unpack_Body_Request_Packet(BodyBin, sBuffer);

                      UnJce UnJce(sBuffer);
                      std::vector<JceStruct::Map<char *, LPBYTE>> Map;
                      UnJce.Read(Map, 0);

                      for (size_t i = 0; i < Map.size(); i++)
                      {
                          UnJce.Reset(Map[i].Value);
                          UnJce.Read(UnJce, 0);

                          std::vector<::UnJce> Groups;
                          UnJce.Read(Groups, 3);
                          QQ.GroupList.resize(Groups.size());

                          for (size_t j = 0; j < Groups.size(); j++)
                          {
                              /*
                               * Groups[j].Read((int&)QQ->GroupList[j].GroupCode, 1);
                               * Groups[j].Read(QQ->GroupList[j].GroupName, 4);
                               * Groups[j].Read(QQ->GroupList[j].MemberCount, 19);
                               * Groups[j].Read((int&)QQ->GroupList[j].MasterQQ, 23);
                               */
                          }

                          delete[] Map[i].Key;
                          delete[] Map[i].Value;
                      }
                      delete[] sBuffer;
                  });
}

void Android::QQ_SyncGroupAdminList(uint Group)
{
    return (Fun_Send_Sync(11, 1, "OidbSvc.0x899_0", OidbSvc::_0x899_0(Group),
                          [&](uint sso_seq, LPBYTE BodyBin)
                          {
                              UnProtobuf UnPB(BodyBin);

                              std::vector<uint> ManagerList;

                              UnPB.StepIn(4);
                              while (UnPB.IsEnd())
                              {
                                  UnPB.StepIn(4);
                                  ManagerList.emplace_back(UnPB.GetVarint(1));
                                  UnPB.StepOut();
                              }
                              UnPB.StepOut();
                          }));
}

/*
 * / <summary>
 * / Get QQ Online state
 * / </summary>
 * / <returns>true:online false:offline</returns>
 */
bool Android::QQ_Status()
{
    return (QQ.Status != 21 && TCP.Connected);
}

const char8_t *Android::QQ_GetErrorMsg()
{
    return (QQ.ErrorMsg);
}

void Android::QQ_Set_Token(QQ::Token *_Token)
{
    if (QQ.Token.A2 != nullptr)
        delete[] QQ.Token.A2;
    if (QQ.Token.TGT != nullptr)
        delete[] QQ.Token.TGT;
    if (QQ.Token.D2Key != nullptr)
        delete[] QQ.Token.D2Key;
    if (QQ.Token.wtSessionTicket != nullptr)
        delete[] QQ.Token.wtSessionTicket;
    if (QQ.Token.wtSessionTicketKey != nullptr)
        delete[] QQ.Token.wtSessionTicketKey;
    if (QQ.Token.token_16A != nullptr)
        delete[] QQ.Token.token_16A;
    if (QQ.Token.md5 != nullptr)
        delete[] QQ.Token.md5;
    if (QQ.Token.TGTkey != nullptr)
        delete[] QQ.Token.TGTkey;
    if (QQ.Token.ksid != nullptr)
        delete[] QQ.Token.ksid;
    QQ.Token = *_Token;
}

const QQ::Token *Android::QQ_Get_Token()
{
    return (&QQ.Token);
}

std::tuple<bool, char8_t *, char8_t *> Android::QQ_UploadImage_Private(const uint QQ, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight, const byte *Image)
{
    return (Fun_Send_Sync<std::tuple<bool, char8_t *, char8_t *>>(11, 1, "LongConn.OffPicUp", LongConn::OffPicUp(QQ, ImageName, ImageMD5, ImageLength, ImageWidth, ImageHeight),
                                                                  [&](uint sso_seq, LPBYTE BodyBin)
                                                                      -> std::tuple<bool, char8_t *, char8_t *>
                                                                  {
                                                                      UnProtobuf UnPB(BodyBin);

                                                                      UnPB.StepIn(2);
                                                                      switch (UnPB.GetVarint(5))
                                                                      {
                                                                      case 0: /* 需要上传 */
                                                                      {
                                                                          if (Image != nullptr)
                                                                          {
                                                                              /*
                                                                               * IP PORT为数组,这里就取第一组
                                                                               * 从右向左入栈,因此这里需要分开写
                                                                               */
                                                                              char *IP = XBin::Int2IP(UnPB.GetVarint(6));
                                                                              uint Port = UnPB.GetVarint(7);
                                                                              LPBYTE ukey = UnPB.GetBin(8);
                                                                              try
                                                                              {
                                                                                  PicUp::DataUp(Image, ImageLength, ImageMD5, 2, IP, Port, ukey);
                                                                              }
                                                                              catch (const char *e)
                                                                              {
                                                                                  Log::AddLog(Log::LogType::NOTICE, Log::MsgType::OTHER, u8"Upload fail", e);
                                                                                  return std::make_tuple(false, new char8_t, new char8_t);
                                                                              }
                                                                              delete IP;
                                                                              delete ukey;
                                                                          }
                                                                          else
                                                                          {
                                                                              Log::AddLog(Log::LogType::WARNING, Log::MsgType::OTHER, u8"Upload image", u8"Upload failed");
                                                                              return std::make_tuple(false, new char8_t, new char8_t);
                                                                          }
                                                                      }
                                                                      case 1:
                                                                      {
                                                                          char8_t *ImageID1 = UnPB.GetStr(10);
                                                                          char8_t *ImageID2 = UnPB.GetStr(11);
                                                                          return std::make_tuple(true, ImageID1, ImageID2);
                                                                      }
                                                                      };
                                                                      return std::make_tuple(false, new char8_t, new char8_t);
                                                                  }));
}

uint Android::QQ_UploadImage_Group(const uint Group, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight, const byte *Image)
{
    return (Fun_Send_Sync<uint>(11, 1, "ImgStore.GroupPicUp", ImgStore::GroupPicUp(Group, ImageName, ImageMD5, ImageLength, ImageWidth, ImageHeight),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> uint
                                {
                                    UnProtobuf UnPB(BodyBin);

                                    UnPB.StepIn(3);
                                    switch (UnPB.GetVarint(4))
                                    {
                                    case 0: /* 需要上传 */
                                    {
                                        if (Image != nullptr)
                                        {
                                            /*
                                             * IP PORT为数组,这里就取第一组
                                             * 从右向左入栈,因此这里需要分开写
                                             */
                                            char *IP = XBin::Int2IP(UnPB.GetVarint(6));
                                            uint Port = UnPB.GetVarint(7);
                                            LPBYTE ukey = UnPB.GetBin(8);
                                            try
                                            {
                                                PicUp::DataUp(Image, ImageLength, ImageMD5, 2, IP, Port, ukey);
                                            }
                                            catch (const char *e)
                                            {
                                                Log::AddLog(Log::LogType::NOTICE, Log::MsgType::OTHER, u8"Upload fail", e);
                                                return 0;
                                            }
                                            delete IP;
                                            delete ukey;
                                        }
                                        else
                                        {
                                            Log::AddLog(Log::LogType::WARNING, Log::MsgType::OTHER, u8"Upload image", u8"Upload failed");
                                            return 0;
                                        }
                                    }
                                    case 1:
                                        return UnPB.GetVarint(9);
                                    };
                                    return 0;
                                }));
}

void Android::QQ_UploadPtt_Private(const uint QQ_, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Ptt)
{
    Protobuf PB;
    PB.WriteVarint(1, 500);
    PB.WriteVarint(2, 0);
    PB.StepIn(7);
    PB.WriteVarint(10, QQ.QQ);
    PB.WriteVarint(20, QQ_);
    PB.WriteVarint(30, 2);
    PB.WriteVarint(40, PttLength);
    PB.WriteStr(50, PttName);
    PB.StepOut();
    PB.WriteVarint(101, 17);
    PB.WriteVarint(102, 104);
    PB.StepIn(99999);
    PB.WriteVarint(1, 3);
    PB.WriteVarint(2, 0);
    PB.WriteVarint(90300, 1);
    PB.WriteVarint(90500, 3);
    PB.WriteVarint(90600, 1);
    PB.WriteVarint(90800, PttTime);
    PB.StepOut();

    PicUp::DataUp(Ptt, PttLength, PttMD5, 26, (char *)QQ.sig.UploadVoice_IP, QQ.sig.UploadVoice_Port, QQ.sig.UploadVoice_ukey, PB.Pack());
    delete PB.Pack();
}

void Android::QQ_UploadPtt_Group(const uint Group, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Ptt)
{
    Protobuf PB;
    PB.WriteVarint(1, 3);
    PB.WriteVarint(2, 3);
    PB.StepIn(5);
    PB.WriteVarint(1, Group);
    PB.WriteVarint(2, QQ.QQ);
    PB.WriteVarint(3, 0);
    PB.WriteBin(4, PttMD5, 16);
    PB.WriteVarint(5, PttLength);
    PB.WriteStr(6, PttName);
    PB.WriteVarint(7, 5);
    PB.WriteVarint(8, 9);
    PB.WriteVarint(9, 3);
    PB.WriteStr(10, (const char8_t *)AndroidQQ_VERSION);
    PB.WriteVarint(12, PttTime);
    PB.WriteVarint(13, 1);
    PB.WriteVarint(14, 1);
    PB.WriteVarint(15, 1);
    PB.StepOut();

    PicUp::DataUp(Ptt, PttLength, PttMD5, 29, (char *)QQ.sig.UploadVoice_IP, QQ.sig.UploadVoice_Port, QQ.sig.UploadVoice_ukey, PB.Pack());
    delete PB.Pack();
}

void Android::QQ_TranslatePtt_Private(const uint QQ_, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Ptt)
{
    Fun_Send_Sync(11, 1, "pttTrans.TransC2CPttReq", pttTrans::TransC2CPttReq(QQ_, PttName, PttMD5, PttLength, PttTime),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      UnProtobuf UnPB(BodyBin);
                  });
}

void Android::QQ_TranslatePtt_Group(const uint Group, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Ptt)
{
    Fun_Send_Sync(11, 1, "pttTrans.TransGroupPttReq", pttTrans::TransGroupPttReq(Group, PttName, PttMD5, PttLength, PttTime),
                  [&](uint sso_seq, LPBYTE BodyBin)
                  {
                      UnProtobuf UnPB(BodyBin);
                  });
}

uint Android::QQ_Get_Account()
{
    return (QQ.QQ);
}

/*
 * / <summary>
 * / 取Cookie(skey,p_skey)
 * / </summary>
 * / <param name="Host">p_skey的目标域名</param>
 * / <returns>使用new,记得delete</returns>
 */
char *Android::QQ_GetCookies(const char *Host)
{
    char *Cookies = new char[100];
    strcpy(Cookies, "skey=");
    strcat(Cookies, QQ.Cookie.skey);
    strcat(Cookies, ";p_skey=");
    for (size_t i = 0; i < QQ.Cookie.p_skey.size(); i++)
    {
        if (!strcmp(QQ.Cookie.p_skey[i].host, Host))
        {
            strcat(Cookies, QQ.Cookie.p_skey[i].p_skey);
        }
    }
    return (Cookies);
}

bool Android::QQ_SendLike(const uint QQ, const int Times)
{
    return (Fun_Send_Sync<bool>(11, 1, "VisitorSvc.ReqFavorite", VisitorSvc::ReqFavorite(QQ, Times),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    LPBYTE sBuffer;
                                    Unpack_Body_Request_Packet(BodyBin, sBuffer);

                                    UnJce UnJce(sBuffer);
                                    std::vector<JceStruct::Map<char *, std::vector<JceStruct::Map<char *, LPBYTE>>>> Map;
                                    UnJce.Read(Map, 0);

                                    for (size_t i = 0; i < Map.size(); i++)
                                    {
                                        for (size_t j = 0; j < Map[i].Value.size(); j++)
                                        {
                                            UnJce.Reset(Map[i].Value[j].Value);
                                            UnJce.Read(UnJce, 0);
                                            /* Todo */
                                            delete[] Map[i].Value[j].Key;
                                            delete[] Map[i].Value[j].Value;
                                        }

                                        delete[] Map[i].Key;
                                    }
                                    delete[] sBuffer;
                                    return true;
                                }));
}

/* / <param name="ToType">接收者类型 2 Friend 1 Group</param> */
bool Android::QQ_SendMsg(const int ToNumber, const uint ToType, const Message::Msg *Msg)
{
    return (Fun_Send_Sync<bool>(11, 1, "MessageSvc.PbSendMsg", MessageSvc::PbSendMsg(ToNumber, ToType, Msg),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    UnProtobuf UnPB(BodyBin);
                                    return !UnPB.GetVarint(1);
                                }));
}

bool Android::QQ_DrawGroupMsg(const uint Group, const uint MsgId, const uint MsgRand)
{
    return (Fun_Send_Sync<bool>(11, 1, "PbMessageSvc.PbMsgWithDraw", PbMessageSvc::PbMsgWithDraw(Group, MsgId, MsgRand),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    UnProtobuf UnPB(BodyBin);
                                    UnPB.StepIn(2);
                                    uint retcode = UnPB.GetVarint(1);
                                    if (retcode != 0)
                                    {
                                        if (QQ.ErrorMsg != nullptr)
                                            delete[] QQ.ErrorMsg;
                                        QQ.ErrorMsg = UnPB.GetStr(2);
                                        UnPB.StepOut();
                                        return false;
                                    }
                                    else
                                    {
                                        UnPB.StepOut();
                                        return true;
                                    }
                                }));
}

bool Android::QQ_DrawPrivateMsg(const uint Group, const uint MsgId, const uint MsgRand)
{
    /* return PbMessageSvc_PbMsgWithDraw(Group, MsgId, MsgRand); */
    return (true);
}

bool Android::QQ_KickGroupMember(const uint Group, const uint QQ, const bool Forever)
{
    return (Fun_Send_Sync<bool>(11, 1, "OidbSvc.0x8a0_0", OidbSvc::_0x8a0_0(Group, QQ, Forever),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    UnProtobuf UnPB(BodyBin);
                                    return true;
                                }));
}

bool Android::QQ_SetGroupAdmin(const uint Group, const uint QQ, const bool Set)
{
    return (Fun_Send_Sync<bool>(11, 1, "OidbSvc.0x55c_1", OidbSvc::_0x55c_1(Group, QQ, Set),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    UnProtobuf UnPB(BodyBin);
                                    return true;
                                }));
}

bool Android::QQ_SetGroupMemberTitle(const uint Group, const uint QQ, const char8_t *Title)
{
    return (Fun_Send_Sync<bool>(11, 1, "OidbSvc.0x8fc_2", OidbSvc::_0x8fc_2(Group, QQ, Title),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    UnProtobuf UnPB(BodyBin);
                                    return true;
                                }));
}

bool Android::QQ_SetGroupMemberCard(const uint Group, const uint QQ, const char *Card)
{
    return (Fun_Send_Sync<bool>(11, 1, "friendlist.ModifyGroupCardReq", friendlist::ModifyGroupCardReq(Group, QQ, Card),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    /* Todo */
                                    return true;
                                }));
}

bool Android::QQ_SetGroupMemberBan(const uint Group, const uint QQ, const uint Time)
{
    return (Fun_Send_Sync<bool>(11, 1, "OidbSvc.0x570_8", OidbSvc::_0x570_8(Group, QQ, Time),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    UnProtobuf UnPB(BodyBin);
                                    return true;
                                }));
}

bool Android::QQ_SetGroupBan(const uint Group, const bool Ban)
{
    return (Fun_Send_Sync<bool>(11, 1, "OidbSvc.0x89a_0", OidbSvc::_0x89a_0(Group, Ban),
                                [&](uint sso_seq, LPBYTE BodyBin)
                                    -> bool
                                {
                                    UnProtobuf UnPB(BodyBin);
                                    return true;
                                }));
}

// ReturnType 0 accept 1 reject 2 block
bool Android::QQ_RequestFriendAction(int64_t msgSeq, uint32_t reqUin, int ReturnType)
{
    return Fun_Send_Sync<bool>(11, 1, "ProfileService.Pb.ReqSystemMsgAction.Friend", ProfileService::Pb_ReqSystemMsgAction_Friend(msgSeq, reqUin, ReturnType),
                               [&](uint sso_seq, LPBYTE BodyBin)
                                   -> bool
                               {
                                   return true;
                               });
}

// ReturnType 0 accept 1 reject 2 block
bool Android::QQ_RequestGroupAction(int64_t msgSeq, uint32_t reqUin, uint32_t groupCode, bool IsInvited, int ReturnType)
{
    return Fun_Send_Sync<bool>(11, 1, "ProfileService.Pb.ReqSystemMsgAction.Group", ProfileService::Pb_ReqSystemMsgAction_Group(msgSeq, reqUin, groupCode, IsInvited, ReturnType),
                               [&](uint sso_seq, LPBYTE BodyBin)
                                   -> bool
                               {
                                   return true;
                               });
}

const std::vector<QQ::FriendInfo> *Android::QQ_GetFriendList()
{
    return (&QQ.FriendList);
}

const std::vector<QQ::GroupInfo> *Android::QQ_GetGroupList()
{
    return (&QQ.GroupList);
}

const std::vector<QQ::GroupMemberInfo> *Android::QQ_GetGroupMemberList(uint Group)
{
    return (nullptr);
}

const std::vector<uint> *Android::QQ_GetGroupAdminList(const uint Group)
{
    return (nullptr);
}
