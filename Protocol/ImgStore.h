#pragma once

#include "Defined.h"
#include "../Utils/Protobuf.h"

class ImgStore
{
private:
    QQ::QQ *QQ;

public:
    ImgStore(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    LPBYTE GroupPicUp(const uint Group, const LPBYTE ImageName, const LPBYTE ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight);
};
