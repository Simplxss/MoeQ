#pragma once

#include "Definition.h"
#include "Log.h"
#include "../Utils/Protobuf.h"
#include "../Utils/Socket.h"

class PicUp
{
private:
    QQ::QQ *QQ;

public:
    PicUp(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    bool DataUp(const byte *TotalData, const uint TotalDataLength, const byte *TotalDataMD5, const int DataType, const char *IP, const uint Port, const LPBYTE ukey, const LPBYTE PttInfo = nullptr);
};