#include "wtlogin.h"

/// <summary>
/// wtlogin用
/// </summary>
/// <param name="Buffer">会自动销毁</param>
/// <param name="BufferLen"></param>
/// <param name="emp"></param>
/// <returns></returns>
LPBYTE wtlogin::Make_Body_PC(byte *Buffer, const uint BufferLen, const bool emp)
{
    ::Pack Pack(BufferLen + 100);
    Pack.SetShort(0x1F41);
    Pack.SetShort(0X0810);
    Pack.SetShort(1);
    Pack.SetInt(QQ->QQ);
    Pack.SetByte(3);

    if (emp)
    {
        Pack.SetByte(0x45);
    }
    else
    {
        Pack.SetByte(0x87);
    }

    Pack.SetByte(0);
    Pack.SetInt(2);
    Pack.SetInt(0);
    Pack.SetInt(0);

    if (emp)
    {
        Pack.SetShort(48);
        Pack.SetBin(QQ->Token.wtSessionTicket, 48);
    }
    else
    {
        Pack.SetBin((byte *)"\2\1", 2);
        Pack.SetBin(QQ->Login->RandKey, 16);
        Pack.SetBin((byte *)"\1\x31", 2);
        Pack.SetShort(1); // public_key_ver (better is 2)
        Pack.SetShort(QQ->Login->ECDH.pubkeyLen);
        Pack.SetBin(QQ->Login->ECDH.pubkey, QQ->Login->ECDH.pubkeyLen);
    }

    std::vector<byte> data;
    if (emp)
    {
        Tea::encrypt(QQ->Token.wtSessionTicketKey, Buffer, BufferLen, data);
    }
    else
    {
        byte *key = Utils::MD5(QQ->Login->ECDH.sharekey, 16);
        Tea::encrypt(key, Buffer, BufferLen, data);
        delete[] key;
    }
    delete[] Buffer;
    Pack.SetBin(&data);

    byte *bin;
    uint bin_len = Pack.GetAll_(bin, true);
    Pack.SetByte(2);
    Pack.SetShort(bin_len + 4);
    Pack.SetBin_(bin, bin_len);
    Pack.SetByte(3);

    Pack.SetLength();
    return Pack.GetAll();
}

LPBYTE wtlogin::login()
{
    ::Pack Pack(1500);
    time_t Time = std::time(0);
    const char *domainList[] = {"openmobile.qq.com", "docs.qq.com", "connect.qq.com", "qzone.qq.com", "vip.qq.com", "qun.qq.com", "game.qq.com", "qqweb.qq.com", "ti.qq.com", "office.qq.com", "mail.qq.com", "qzone.com", "mma.qq.com", "tenpay.com"};
    Pack.SetShort(9);
    Pack.SetShort(25);

#define PACKTLV(TlvName, ...) Pack.Skip(Tlv::Tlv##TlvName(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), ##__VA_ARGS__))

    PACKTLV(018, QQ->QQ);
    PACKTLV(001, QQ->QQ, Time);
    PACKTLV(106, QQ->QQ, QQ->QQ_Str, QQ->Token.md5, QQ->Token.md52, QQ->Token.TGTkey, Device->GUID, Time, AndroidQQ_APPID, false);
    PACKTLV(116);
    PACKTLV(100, AndroidQQ_APPID, true);
    PACKTLV(107);
    PACKTLV(108, AndroidQQ_ASIG);
    PACKTLV(142, AndroidQQ_APKID);
    PACKTLV(144, QQ->Token.TGTkey, Device->IMEI, Device->os_type, Device->os_version, Device->_network_type, Device->_apn, Device->NetworkName, Device->_device, Device->Brand, Device->GUID);
    PACKTLV(145, Device->GUID);
    PACKTLV(147, AndroidQQ_VERSION, AndroidQQ_ASIG);
    PACKTLV(154, QQ->SsoSeq);
    PACKTLV(141, Device->NetworkName, Device->_apn);
    PACKTLV(008);
    PACKTLV(511, domainList, 14);
    PACKTLV(187);
    PACKTLV(188);
    PACKTLV(191, 0x82);
    PACKTLV(177, AndroidQQ_BUILDTIME, AndroidQQ_SDK_VERSION);
    PACKTLV(516);
    PACKTLV(521);
    PACKTLV(525, 0, 0, 0, 0, false);
    PACKTLV(544, AndroidQQ_APKID, AndroidQQ_ASIG);
    PACKTLV(545);
    // PACKTLV(548);
    PACKTLV(542);

#undef PACKTLV

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_ScanCode()
{
    ::Pack Pack(1500);
    time_t Time = std::time(0);
    const char *domainList[] = {"openmobile.qq.com", "docs.qq.com", "connect.qq.com", "qzone.qq.com", "vip.qq.com", "qun.qq.com", "game.qq.com", "qqweb.qq.com", "ti.qq.com", "office.qq.com", "mail.qq.com", "qzone.com", "mma.qq.com", "tenpay.com"};
    Pack.SetShort(9);
    Pack.SetShort(24);

#define PACKTLV(TlvName, ...) Pack.Skip(Tlv::Tlv##TlvName(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), ##__VA_ARGS__))

    PACKTLV(018, QQ->QQ);
    PACKTLV(001, QQ->QQ, Time);
    PACKTLV(106, QQ->QQ, QQ->QQ_Str, QQ->Token.md5, QQ->Token.md52, QQ->Token.TGTkey, Device->GUID, Time, AndroidQQ_APPID, false);
    PACKTLV(116);
    PACKTLV(100, AndroidQQ_APPID, true);
    PACKTLV(107);
    PACKTLV(142, AndroidQQ_APKID);
    PACKTLV(144, QQ->Token.TGTkey, Device->IMEI, Device->os_type, Device->os_version, Device->_network_type, Device->_apn, Device->NetworkName, Device->_device, Device->Brand, Device->GUID);
    PACKTLV(145, Device->GUID);
    PACKTLV(147, AndroidQQ_VERSION, AndroidQQ_ASIG);
    PACKTLV(154, QQ->SsoSeq);
    PACKTLV(141, Device->NetworkName, Device->_apn);
    PACKTLV(008);
    PACKTLV(511, domainList, 14);
    PACKTLV(187);
    PACKTLV(188);
    PACKTLV(194);
    PACKTLV(191, 0x82);
    PACKTLV(202, Device->BSSID, Device->WiFiName);
    PACKTLV(177, AndroidQQ_BUILDTIME, AndroidQQ_SDK_VERSION);
    PACKTLV(516);
    PACKTLV(521);
    PACKTLV(525, 0, 0, 0, 0, false);
    PACKTLV(544, AndroidQQ_APKID, AndroidQQ_ASIG);

#undef PACKTLV

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Send_Sms()
{
    ::Pack Pack(300);
    Pack.SetShort(8);
    Pack.SetShort(6);

#define PACKTLV(TlvName, ...) Pack.Skip(Tlv::Tlv##TlvName(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), ##__VA_ARGS__))

    PACKTLV(008);
    PACKTLV(104, QQ->Login->VieryToken2);
    PACKTLV(116);
    PACKTLV(174, QQ->Login->SmsToken);
    PACKTLV(17A);
    PACKTLV(197);

#undef PACKTLV

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Viery_Ticket(const char *Ticket)
{
    ::Pack Pack(900);
    Pack.SetShort(2);
    Pack.SetShort(6);

#define PACKTLV(TlvName, ...) Pack.Skip(Tlv::Tlv##TlvName(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), ##__VA_ARGS__))

    PACKTLV(193, Ticket);
    PACKTLV(008);
    PACKTLV(104, QQ->Login->VieryToken2);
    PACKTLV(116);
    PACKTLV(547, QQ->Login->ClientPow);
    PACKTLV(542);

#undef PACKTLV

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Viery_Sms(const char *SmsCode)
{
    ::Pack Pack(300);
    Pack.SetShort(7);
    Pack.SetShort(7);

#define PACKTLV(TlvName, ...) Pack.Skip(Tlv::Tlv##TlvName(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), ##__VA_ARGS__))

    PACKTLV(008);
    PACKTLV(104, QQ->Login->VieryToken2);
    PACKTLV(116);
    PACKTLV(174, QQ->Login->SmsToken);
    PACKTLV(17C, SmsCode);
    PACKTLV(401, Device->GUID, QQ->Login->token_402);
    PACKTLV(198);

#undef PACKTLV

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Viery_204()
{
    ::Pack Pack(300);
    Pack.SetBin((byte *)"\x00\x14", 2);
    Pack.SetShort(0x14);
    Pack.SetShort(6);

#define PACKTLV(TlvName, ...) Pack.Skip(Tlv::Tlv##TlvName(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), ##__VA_ARGS__))

    PACKTLV(008);
    PACKTLV(104, QQ->Login->VieryToken2);
    PACKTLV(116);
    PACKTLV(401, Device->GUID, QQ->Login->token_402);
    // PACKTLV(402);
    // PACKTLV(403);

#undef PACKTLV

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::exchange_emp()
{
    ::Pack Pack(1600);
    time_t Time = std::time(0);
    const char *domainList[] = {"openmobile.qq.com", "docs.qq.com", "connect.qq.com", "qzone.qq.com", "vip.qq.com", "qun.qq.com", "game.qq.com", "qqweb.qq.com", "ti.qq.com", "office.qq.com", "mail.qq.com", "qzone.com", "mma.qq.com", "tenpay.com"};
    Pack.SetShort(0x0F);
    Pack.SetShort(27);

#define PACKTLV(TlvName, ...) Pack.Skip(Tlv::Tlv##TlvName(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), ##__VA_ARGS__))

    PACKTLV(018, QQ->QQ);
    PACKTLV(001, QQ->QQ, Time);
    PACKTLV(106, QQ->QQ, QQ->QQ_Str, QQ->Token.md5, QQ->Token.md52, QQ->Token.TGTkey, Device->GUID, Time, AndroidQQ_APPID, true);
    PACKTLV(116);
    PACKTLV(100, AndroidQQ_APPID, true);
    PACKTLV(107);
    PACKTLV(108, QQ->Token.ksid);
    PACKTLV(144, QQ->Token.TGTkey, Device->IMEI, Device->os_type, Device->os_version, Device->_network_type, Device->_apn, Device->NetworkName, Device->_device, Device->Brand, Device->GUID);
    PACKTLV(142, AndroidQQ_APKID);
    PACKTLV(145, Device->GUID);
    PACKTLV(16A, QQ->Token.token_16A);
    PACKTLV(154, QQ->SsoSeq);
    PACKTLV(141, Device->NetworkName, Device->_apn);
    PACKTLV(008);
    PACKTLV(511, domainList, 14);
    PACKTLV(147, AndroidQQ_VERSION, AndroidQQ_ASIG);
    PACKTLV(177, AndroidQQ_BUILDTIME, AndroidQQ_SDK_VERSION);
    PACKTLV(400, QQ->QQ, Device->GUID, Time, (byte *)"\1\2\3\4\5\6\7\x08"); // lazy
    PACKTLV(187);
    PACKTLV(188);
    PACKTLV(194);
    PACKTLV(202, Device->BSSID, Device->WiFiName);
    PACKTLV(516);
    PACKTLV(521);
    PACKTLV(525, QQ->QQ, Device->IP, Time, AndroidQQ_APPID, true);
    PACKTLV(544, AndroidQQ_APKID, AndroidQQ_ASIG);
    PACKTLV(545);

#undef PACKTLV

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), true);
}
