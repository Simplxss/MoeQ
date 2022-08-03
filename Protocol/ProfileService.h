#pragma once

#include "Definition.h"
#include "../Utils/Protobuf.h"

class ProfileService
{
private:
    QQ::QQ *QQ;

public:
    ProfileService(QQ::QQ *_QQ)
    {
        QQ = _QQ;
    };

public:
    LPBYTE Pb_ReqSystemMsgNew_Group();
};
