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
    LPBYTE Pb_ReqSystemMsgNew_Friend();
    LPBYTE Pb_ReqSystemMsgNew_Group();
    // ReturnType 0 accept 1 reject 2 block
    LPBYTE Pb_ReqSystemMsgAction_Friend(int64_t msgSeq, uint32_t reqUin, int ReturnType);
    // ReturnType 0 accept 1 reject 2 block
    LPBYTE Pb_ReqSystemMsgAction_Group(int64_t msgSeq, uint32_t reqUin, uint32_t groupCode, bool IsInvited, int ReturnType);
};
