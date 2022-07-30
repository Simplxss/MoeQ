#include "ImgStore.h"

LPBYTE ImgStore::GroupPicUp(const uint Group, const char8_t *ImageName, const byte *ImageMD5, const uint ImageLength, const uint ImageWidth, const uint ImageHeight)
{
    Protobuf PB;
    PB.WriteVarint(1, 3);
    PB.WriteVarint(2, 1);
    PB.StepIn(3);
    PB.WriteVarint(1, Group);
    PB.WriteVarint(2, QQ->QQ);
    PB.WriteVarint(3, 0);
    PB.WriteBin(4, ImageMD5, 16);
    PB.WriteVarint(5, ImageLength);
    PB.WriteStr(6, ImageName);
    PB.WriteVarint(7, 5);
    PB.WriteVarint(8, 9);
    PB.WriteVarint(9, 1);
    PB.WriteVarint(10, ImageWidth);
    PB.WriteVarint(11, ImageHeight);
    PB.WriteVarint(12, 1000);
    PB.WriteStr(13, (const char8_t *)AndroidQQ_VERSION);
    PB.WriteVarint(15, 1052);
    PB.WriteVarint(16, 1);
    PB.WriteVarint(19, 0);
    PB.StepOut();
    return PB.Pack();
}