#pragma once

#include "Definition.h"
#include "../Utils/Protobuf.h"

class MessageSvc
{
private:
    QQ::QQ *QQ;

public:
    MessageSvc(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    virtual std::tuple<bool, char8_t *, char8_t *> QQ_UploadImage_Private(const uint QQ, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight, const byte *Image = nullptr) { return std::tuple(bool(), new char8_t, new char8_t); };
    virtual uint QQ_UploadImage_Group(const uint Group, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight, const byte *Image = nullptr) { return uint(); };
    virtual void QQ_UploadPtt_Private(const uint QQ_, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Image){};
    virtual void QQ_UploadPtt_Group(const uint Group, const char8_t *PttName, const byte *PttMD5, const uint PttLength, const uint PttTime, const byte *Image){};

public:
    LPBYTE PbGetMsg();
    LPBYTE PbSendMsg(const uint ToNumber, const byte ToType, const Message::Msg *Msg);
};
