#include "LongConn.h"

LPBYTE LongConn::OffPicUp(const uint QQ_, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight)
{
    Protobuf PB;
    PB.WriteVarint(1, 1);
    PB.StepIn(2);
    PB.WriteVarint(1, QQ->QQ);
    PB.WriteVarint(2, QQ_);
    PB.WriteVarint(3, 0);
    PB.WriteBin(4, ImageMD5, 16);
    PB.WriteVarint(5, ImageLength);
    PB.WriteStr(6, ImageName);
    PB.WriteVarint(7, 5);
    PB.WriteVarint(8, 9);
    PB.WriteVarint(10, 0);
    PB.WriteVarint(12, 1);
    PB.WriteVarint(13, 0);
    PB.WriteVarint(14, ImageWidth);
    PB.WriteVarint(15, ImageHeight);
    PB.WriteVarint(16, 2000);
    PB.WriteStr(17, (const char8_t *)AndroidQQ_VERSION);
    PB.WriteVarint(21, 0);
    PB.WriteVarint(22, 0);
    PB.StepOut();
    PB.WriteVarint(10, 3);
    return PB.Pack();
}