#pragma once

#include "../Utils/Protobuf.h"
#include "../Utils/Tea.h"

#define FUNC(TlvName, ...) uint16_t Tlv##TlvName(byte *bin, const uint len, ##__VA_ARGS__)

namespace Tlv
{
	FUNC(001, uint QQ, uint Time);
	FUNC(002, const char *code, const char VieryToken1[4]);
	FUNC(008);
	FUNC(008);
	FUNC(018, const uint QQ);
	FUNC(100, const uint SUB_APPID, const bool IsFreshSkey);
	FUNC(104, const byte VieryToken2[36]);
	FUNC(106, const uint QQ, const char *QQ_Str, const byte md5[16], const byte md52[16], const byte TGTKey[16], const byte GUID[16], const uint Time, const uint SUB_APPID, bool emp);
	FUNC(107);
	FUNC(108, const byte ksid[16]);
	FUNC(109, const char *IMEI);
	FUNC(116);
	FUNC(124, const char *os_type, const char *os_version, const unsigned short _network_type, const char *_apn, const char *NetworkName);
	FUNC(128, const char *_device, const char *Brand, const byte GUID[16]);
	FUNC(141, const char *NetworkName, const char *NetworkType);
	FUNC(142, const char *QQ_APKID);
	FUNC(144, const byte TGTKey[16], const char *IMEI, const char *os_type, const char *os_version, const unsigned short _network_type, const char *_apn, const char *NetworkName, const char *_device, const char *Brand, const byte GUID[16]);
	FUNC(145, const byte GUID[16]);
	FUNC(147, const char *QQ_VERSION, const byte QQ_ASIG[16]);
	FUNC(154, const uint SsoSeq);
	FUNC(16A, const byte *token_16A);
	FUNC(16E, const char *_device);
	FUNC(174, const char *SmsToken);
	FUNC(177, const uint build_time, const char *SDK_VERSION);
	FUNC(17A);
	FUNC(17C, const char *code);
	FUNC(187);
    FUNC(188, const char *IMEI);
	FUNC(191, const byte CodeType);
	FUNC(193, const char *Ticket);
	FUNC(194);
	FUNC(197);
	FUNC(198);
	FUNC(202, const char *BSSID, const char *WiFi_name);
	FUNC(400, const long long QQ, const byte GUID[16], const uint Time, const byte *token_403);
	FUNC(401, const byte GUID[16], const byte *token_402);
	FUNC(511, const char **domainList, const byte ListSize);
	FUNC(516);
	FUNC(521);
	FUNC(525, const uint QQ, const char *IP, const uint Time, const uint SUB_APPID, const bool IsEmp);
	FUNC(52D);
	FUNC(542);
	FUNC(544);
	FUNC(545);
	FUNC(547, const byte *ClientPow);
	FUNC(548);
	FUNC(553);
};

#undef FUNC