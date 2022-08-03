#include "VisitorSvc.h"

LPBYTE VisitorSvc::ReqFavorite(const uint QQ, const int Times)
{
    Jce Jce, Jce_;
    Jce.Write(this->QQ->QQ, 0);
    Jce.Write(1, 1);
    Jce.Write(1265524299, 2);
    Jce.Write(1, 3);
    Jce.Write(0, 4);

    Jce_.Write(&Jce, 0);
    Jce_.Write(QQ, 1);
    Jce_.Write(0, 2);
    Jce_.Write(66, 2);
    Jce_.Write(Times, 2);

    Jce_.Write(&Jce_, 0);
    LPBYTE bin = Jce_.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"ReqFavorite", bin}};
    Jce_.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce_.GetAll(bin);
    return Make_Body_Request_Packet(3, 0, "VisitorSvc", "ReqFavorite", bin, len);
}