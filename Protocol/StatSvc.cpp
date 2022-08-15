#include "StatSvc.h"

LPBYTE StatSvc::Register(const byte state)
{
    Jce Jce;
    Jce.Write(QQ->QQ, 0);                          //lUin
    Jce.Write(state == 21 ? 0 : 7, 1);            //lBid
    Jce.Write(0, 2);                              //cConnType
    Jce.Write("", 3);                             //sOther
    Jce.Write(state == 0 ? QQ->Status : state, 4); //iStatus
    Jce.Write(state == 0, 5);                     //bOnlinePush
    Jce.Write(false, 6);                          //bIsOnline
    Jce.Write(false, 7);                          //bIsShowOnline
    Jce.Write(false, 8);                          //bKikPC''''
    Jce.Write(false, 9);                          //bKikWeak
    Jce.Write(517, 10);                           //timeStamp
    Jce.Write(22, 11);                            //iOSVersion
    Jce.Write(1, 12);                             //cNetType
    Jce.Write("", 13);                            //sBuildVer
    Jce.Write(false, 14);                         //bRegType
    //vecDevParam
    Jce.Write(Device->GUID, 16, 16);   //vecGuid
    Jce.Write(2052, 17);              //iLocaleID
    Jce.Write(false, 18);             //bSlientPush
    Jce.Write(Device->_device, 19);    //strDevName
    Jce.Write(Device->_device, 20);    //strDevType
    Jce.Write(Device->os_version, 21); //strOSVer
    Jce.Write(true, 22);              //bOpenPush
    Jce.Write(13, 23);                //iLargeSeq
    Jce.Write(0, 24);                 //iLastWatchStartTime
    //vecBindUin
    Jce.Write(0, 26);                                                                                  //uOldSSOIp
    Jce.Write(0, 27);                                                                                  //uNewSSOIp
    Jce.Write("", 28);                                                                                 //sChannelNo
    Jce.Write(0, 29);                                                                                  //lCpId
    Jce.Write(Device->Brand, 30);                                                                       //strVendorName
    Jce.Write("", 31);                                                                                 //strVendorOSName
    Jce.Write("", 32);                                                                                 //strIOSIdfa
    Jce.Write((byte *)"\x0A\x08\x08\x2E\x10\xEF\xBF\x8B\xF4\x05\x0A\x05\x08\x9B\x02\x10\x00", 17, 33); //bytes_0x769_reqbody
    Jce.Write(false, 34);                                                                              //bIsSetStatus
    //vecServerBuf
    Jce.Write(false, 36); //bSetMute
    Jce.Write(0, 38);     //uExtOnlineStatus
    Jce.Write(0, 39);     //iBatteryStatus

    Jce.Write(&Jce, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"SvcReqRegister", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce.GetAll(bin);

    return Make_Body_Request_Packet(3, 0, "PushService", "SvcReqRegister", bin, len);
}

LPBYTE StatSvc::SimpleGet()
{
    Pack Pack(4, true);
    Pack.SetLength();
    return Pack.GetAll();
}

LPBYTE StatSvc::SetStatusFromClient(const byte state)
{
    Jce Jce;
    Jce.Write(QQ->QQ, 0);                          //lUin
    Jce.Write(state == 21 ? 0 : 7, 1);            //lBid
    Jce.Write(0, 2);                              //cConnType
    Jce.Write("", 3);                             //sOther
    Jce.Write(state == 0 ? QQ->Status : state, 4); //iStatus
    Jce.Write(state == 0, 5);                     //bOnlinePush
    Jce.Write(0, 6);                              //bIsOnline
    Jce.Write(0, 7);                              //bIsShowOnline
    Jce.Write(false, 8);                          //bKikPC''''
    Jce.Write(false, 9);                          //bKikWeak
    Jce.Write((uint)std::time(0), 10);            //timeStamp
    Jce.Write(23, 11);                            //iOSVersion
    Jce.Write(1, 12);                             //cNetType
    Jce.Write("", 13);                            //sBuildVer
    Jce.Write(false, 14);                         //bRegType
    //vecDevParam
    Jce.Write(Device->GUID, 16, 16);   //vecGuid
    Jce.Write(2052, 17);              //iLocaleID
    Jce.Write(false, 18);             //bSlientPush
    Jce.Write(Device->_device, 19);    //strDevName
    Jce.Write(Device->_device, 20);    //strDevType
    Jce.Write(Device->os_version, 21); //strOSVer
    Jce.Write(true, 22);              //bOpenPush
    Jce.Write(0, 23);                 //iLargeSeq
    Jce.Write(0, 24);                 //iLastWatchStartTime
    //vecBindUin
    Jce.Write(0, 26);                                                                                  //uOldSSOIp
    Jce.Write(0, 27);                                                                                  //uNewSSOIp
    Jce.Write("", 28);                                                                                 //sChannelNo
    Jce.Write(0, 29);                                                                                  //lCpId
    Jce.Write(Device->Brand, 30);                                                                       //strVendorName
    Jce.Write("", 31);                                                                                 //strVendorOSName
    Jce.Write("", 32);                                                                                 //strIOSIdfa
    Jce.Write((byte *)"\x0A\x08\x08\x2E\x10\xEF\xBF\x8B\xF4\x05\x0A\x05\x08\x9B\x02\x10\x00", 17, 33); //bytes_0x769_reqbody
    Jce.Write(true, 34);                                                                               //bIsSetStatus
    //vecServerBuf
    Jce.Write(0, 36);     //bSetMute
    Jce.Write(0, 38);     //uExtOnlineStatus
    Jce.Write(10000, 39); //iBatteryStatus

    Jce.Write(&Jce, 0);
    LPBYTE bin = Jce.GetAll_();

    const std::vector<JceStruct::Map<const char *, const LPBYTE>> JceMap{JceStruct::Map<const char *, const LPBYTE>{"SvcReqRegister", bin}};
    Jce.Write(&JceMap, 0);
    delete[] bin;

    uint len = Jce.GetAll(bin);

    return Make_Body_Request_Packet(3, 0, "PushService", "SvcReqRegister", bin, len);
}
