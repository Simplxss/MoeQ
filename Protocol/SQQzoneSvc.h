#pragma once

#include "Definition.h"
#include "../Utils/JceStruct.h"

class SQQzoneSvc
{
private:
    QQ::QQ *QQ;
    QQ::Device *Device;

public:
    SQQzoneSvc(QQ::QQ *_QQ, QQ::Device *_Device)
    {
        QQ = _QQ;
        Device = _Device;
    };

public:
    LPBYTE getUndealCount();
};