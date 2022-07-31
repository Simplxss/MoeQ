#pragma once

#include "Definition.h"
#include "../Utils/Protobuf.h"

class LongConn
{
private:
    QQ::QQ *QQ;

public:
    LongConn(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    LPBYTE OffPicUp(const uint QQ, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight);
};
