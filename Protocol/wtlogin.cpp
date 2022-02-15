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
    Pack.SetBin((byte *)"\x1f\x41", 2);
    Pack.SetBin((byte *)"\x08\x10", 2);
    Pack.SetShort(1);
    Pack.SetInt(QQ->QQ);
    if (emp)
    {
        Pack.SetBin((byte *)"\3\x45\0\0\0\0\2\0\0\0\0\0\0", 13);
        Pack.SetInt(48);
        Pack.SetBin(QQ->Token.wtSessionTicket, 48);
    }
    else
    {
        Pack.SetBin((byte *)"\3\x87\0\0\0\0\2\0\0\0\0\0\0\0\0", 15);
        Pack.SetBin((byte *)"\1\1", 2);
        Pack.SetBin(QQ->Login->RandKey, 16);
        Pack.SetBin((byte *)"\1\2", 2);

        Pack.SetShort(QQ->Login->ECDH.pubkeyLen);
        Pack.SetBin(QQ->Login->ECDH.pubkey, QQ->Login->ECDH.pubkeyLen);
    }
    {
        std::vector<byte> data;
        if (emp)
        {
            Tea::encrypt(QQ->Token.wtSessionTicketKey, Buffer, BufferLen, data);
        }
        else
        {
            byte *key = Utils::MD5(QQ->Login->ECDH.sharekey, 24);
            Tea::encrypt(key, Buffer, BufferLen, data);
            delete[] key;
        }
        delete[] Buffer;
        Pack.SetBin(&data);
    }
    {
        byte *bin;
        uint bin_len = Pack.GetAll_(bin, true);
        Pack.SetByte(2);
        Pack.SetShort(bin_len + 4);
        Pack.SetBin_(bin, bin_len);
        Pack.SetByte(3);
    }
    Pack.SetLength();
    return Pack.GetAll();
}

LPBYTE wtlogin::login()
{
    ::Pack Pack(1500);
    time_t Time = std::time(0);
    const char *domainList[] = {"openmobile.qq.com", "docs.qq.com", "connect.qq.com", "qzone.qq.com", "vip.qq.com", "qun.qq.com", "game.qq.com", "qqweb.qq.com", "ti.qq.com", "office.qq.com", "mail.qq.com", "qzone.com", "mma.qq.com", "tenpay.com"};
    Pack.SetBin((byte *)"\x00\x09", 2);
    Pack.SetShort(24);
    Pack.Skip(Tlv::Tlv018(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ));
    Pack.Skip(Tlv::Tlv001(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, Time));
    Pack.Skip(Tlv::Tlv106(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, QQ->QQ_Str, QQ->Token.md5, QQ->Token.md52, QQ->Token.TGTkey, Device->GUID, Time, AndroidQQ_APPID, false));
    Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv100(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APPID, true));
    Pack.Skip(Tlv::Tlv107(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv142(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APKID));
    Pack.Skip(Tlv::Tlv144(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Token.TGTkey, Device->IMEI, Device->os_type, Device->os_version, Device->_network_type, Device->_apn, Device->NetworkName, Device->_device, Device->Brand, Device->GUID));
    Pack.Skip(Tlv::Tlv145(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->GUID));
    Pack.Skip(Tlv::Tlv147(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_VERSION, AndroidQQ_ASIG));
    Pack.Skip(Tlv::Tlv154(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->SsoSeq));
    Pack.Skip(Tlv::Tlv141(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->NetworkName, Device->_apn));
    Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv511(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), domainList, 14));
    Pack.Skip(Tlv::Tlv187(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv188(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv194(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv191(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), 0x82));
    Pack.Skip(Tlv::Tlv202(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->BSSID, Device->WiFiName));
    Pack.Skip(Tlv::Tlv177(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_BUILDTIME, AndroidQQ_SDK_VERSION));
    Pack.Skip(Tlv::Tlv516(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv521(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv525(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), 0, 0, 0, 0, false));
    Pack.Skip(Tlv::Tlv544(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APKID, AndroidQQ_ASIG));
    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_ScanCode()
{
    ::Pack Pack(1500);
    time_t Time = std::time(0);
    const char *domainList[] = {"openmobile.qq.com", "docs.qq.com", "connect.qq.com", "qzone.qq.com", "vip.qq.com", "qun.qq.com", "game.qq.com", "qqweb.qq.com", "ti.qq.com", "office.qq.com", "mail.qq.com", "qzone.com", "mma.qq.com", "tenpay.com"};
    Pack.SetBin((byte *)"\x00\x09", 2);
    Pack.SetShort(24);
    Pack.Skip(Tlv::Tlv018(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ));
    Pack.Skip(Tlv::Tlv001(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, Time));
    Pack.Skip(Tlv::Tlv106(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, QQ->QQ_Str, QQ->Token.md5, QQ->Token.md52, QQ->Token.TGTkey, Device->GUID, Time, AndroidQQ_APPID, false));
    Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv100(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APPID, true));
    Pack.Skip(Tlv::Tlv107(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv142(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APKID));
    Pack.Skip(Tlv::Tlv144(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Token.TGTkey, Device->IMEI, Device->os_type, Device->os_version, Device->_network_type, Device->_apn, Device->NetworkName, Device->_device, Device->Brand, Device->GUID));
    Pack.Skip(Tlv::Tlv145(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->GUID));
    Pack.Skip(Tlv::Tlv147(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_VERSION, AndroidQQ_ASIG));
    Pack.Skip(Tlv::Tlv154(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->SsoSeq));
    Pack.Skip(Tlv::Tlv141(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->NetworkName, Device->_apn));
    Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv511(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), domainList, 14));
    Pack.Skip(Tlv::Tlv187(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv188(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv194(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv191(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), 0x82));
    Pack.Skip(Tlv::Tlv202(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->BSSID, Device->WiFiName));
    Pack.Skip(Tlv::Tlv177(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_BUILDTIME, AndroidQQ_SDK_VERSION));
    Pack.Skip(Tlv::Tlv516(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv521(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv525(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), 0, 0, 0, 0, false));
    Pack.Skip(Tlv::Tlv544(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APKID, AndroidQQ_ASIG));
    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Send_Sms()
{
    ::Pack Pack(300);
    Pack.SetBin((byte *)"\x00\x08", 2);
    Pack.SetShort(6);
    Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Login->VieryToken2));
    Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv174(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Login->SmsToken));
    Pack.Skip(Tlv::Tlv17A(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv197(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Viery_Ticket(const char *Ticket)
{
    ::Pack Pack(900);
    Pack.SetBin((byte *)"\x00\x02", 2);
    Pack.SetShort(4);
    Pack.Skip(Tlv::Tlv193(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Ticket));
    Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Login->VieryToken2));
    Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    //Pack.Skip(Tlv::Tlv547(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Login->ClientPow));
    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Viery_Sms(const char *SmsCode)
{
    ::Pack Pack(300);
    Pack.SetBin((byte *)"\x00\x07", 2);
    Pack.SetShort(7);
    Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Login->VieryToken2));
    Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv174(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Login->SmsToken));
    Pack.Skip(Tlv::Tlv17C(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), SmsCode));
    Pack.Skip(Tlv::Tlv401(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->GUID, QQ->Login->token_402));
    Pack.Skip(Tlv::Tlv198(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::login_Viery_204()
{
    ::Pack Pack(300);
    Pack.SetBin((byte *)"\x00\x14", 2);
    Pack.SetShort(6);
    Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Login->VieryToken2));
    Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv401(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->GUID, QQ->Login->token_402));
    //Pack.Skip(Tlv::Tlv402(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    //Pack.Skip(Tlv::Tlv403(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    return Make_Body_PC(Pack.GetAll(), Pack.Length(), false);
}

LPBYTE wtlogin::exchange_emp()
{
    ::Pack Pack(1600);
    time_t Time = std::time(0);
    const char *domainList[] = {"openmobile.qq.com", "docs.qq.com", "connect.qq.com", "qzone.qq.com", "vip.qq.com", "qun.qq.com", "game.qq.com", "qqweb.qq.com", "ti.qq.com", "office.qq.com", "mail.qq.com", "qzone.com", "mma.qq.com", "tenpay.com"};
    Pack.SetBin((byte *)"\x00\x0f", 2);
    Pack.SetShort(27);
    Pack.Skip(Tlv::Tlv018(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ));
    Pack.Skip(Tlv::Tlv001(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, Time));
    Pack.Skip(Tlv::Tlv106(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, QQ->QQ_Str, QQ->Token.md5, QQ->Token.md52, QQ->Token.TGTkey, Device->GUID, Time, AndroidQQ_APPID, true));
    Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv100(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APPID, true));
    Pack.Skip(Tlv::Tlv107(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv108(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Token.ksid));
    Pack.Skip(Tlv::Tlv144(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Token.TGTkey, Device->IMEI, Device->os_type, Device->os_version, Device->_network_type, Device->_apn, Device->NetworkName, Device->_device, Device->Brand, Device->GUID));
    Pack.Skip(Tlv::Tlv142(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APKID));
    Pack.Skip(Tlv::Tlv145(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->GUID));
    Pack.Skip(Tlv::Tlv16A(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->Token.token_16A));
    Pack.Skip(Tlv::Tlv154(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->SsoSeq));
    Pack.Skip(Tlv::Tlv141(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->NetworkName, Device->_apn));
    Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv511(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), domainList, 14));
    Pack.Skip(Tlv::Tlv147(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_VERSION, AndroidQQ_ASIG));
    Pack.Skip(Tlv::Tlv177(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_BUILDTIME, AndroidQQ_SDK_VERSION));
    Pack.Skip(Tlv::Tlv400(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, Device->GUID, Time, (byte *)"\1\2\3\4\5\6\7\x8")); //lazy
    Pack.Skip(Tlv::Tlv187(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv188(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv194(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv202(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->BSSID, Device->WiFiName));
    Pack.Skip(Tlv::Tlv516(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv521(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
    Pack.Skip(Tlv::Tlv525(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ->QQ, Device->IP, Time, AndroidQQ_APPID, true));
    Pack.Skip(Tlv::Tlv544(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), AndroidQQ_APKID, AndroidQQ_ASIG));
    Pack.Skip(Tlv::Tlv545(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device->QIMEI));

    return Make_Body_PC(Pack.GetAll(), Pack.Length(), true);
}
