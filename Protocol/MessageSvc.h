#pragma once

#include "Defined.h"
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
    virtual uint QQ_UploadImage(const uint Group, const LPBYTE ImageName, const LPBYTE ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight, const byte *Image = nullptr) { return uint(); };

public:
    LPBYTE PbGetMsg();
    LPBYTE PbSendMsg(const uint ToNumber, const byte ToType, const Message::Msg *Msg);
};
