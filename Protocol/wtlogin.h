#pragma once

#include "Definition.h"
#include "Tlv.h"

class wtlogin
{
private:
    QQ::QQ *QQ;
    QQ::Device *Device;

public:
    wtlogin(QQ::QQ *_QQ, QQ::Device *_Device)
    {
        QQ = _QQ;
        Device = _Device;
    };

private:
    LPBYTE Make_Body_PC(byte *Buffer, const uint BufferLen, const bool emp);

public:
    LPBYTE login();
    LPBYTE login_Send_Sms();
    LPBYTE login_Viery_Ticket(const char *Ticket);
    LPBYTE login_Viery_Sms(const char *SmsCode);
    LPBYTE login_Viery_204();
    LPBYTE exchange_emp();
};