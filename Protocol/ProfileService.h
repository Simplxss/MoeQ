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
    LPBYTE Pb_ReqSystemMsgNew_Friend();
    LPBYTE Pb_ReqSystemMsgAction_Group(int32_t sso_seq, int64_t msgSeq, uint32_t reqUin, uint32_t groupCode, bool IsInvited, ::Event::RequestEvent::ReturnType ReturnType);
};
