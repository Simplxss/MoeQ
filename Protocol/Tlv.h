#pragma once

#include "../Utils/Protobuf.h"
#include "../Utils/Tea.h"

#define Func(TlvName, ...) uint16_t Tlv##TlvName(byte *bin, const uint len, ##__VA_ARGS__);

namespace Tlv
{
	Func(001, uint QQ, uint Time)
	Func(002, const char *code, const char VieryToken1[4])
	Func(008)
	Func(008)
	Func(018, const uint QQ)
	Func(100, const uint APPID, const bool IsFreshSkey)
	Func(104, const byte VieryToken2[36])
	Func(106, const uint QQ, const char *QQ_Str, const byte md5[16], const byte md52[16], const byte TGTKey[16], const byte GUID[16], const uint Time, const uint APPID, bool emp)
	Func(107)
	Func(108, const byte ksid[16])
	Func(109, const char *IMEI)
	Func(116)
	Func(124, const char *os_type, const char *os_version, const unsigned short _network_type, const char *_apn, const char *NetworkName)
	Func(128, const char *_device, const char *Brand, const byte GUID[16])
	Func(141, const char *NetworkName, const char *NetworkType)
	Func(142, const char *QQ_APKID)
	Func(144, const byte TGTKey[16], const char *IMEI, const char *os_type, const char *os_version, const unsigned short _network_type, const char *_apn, const char *NetworkName, const char *_device, const char *Brand, const byte GUID[16])
	Func(145, const byte GUID[16])
	Func(147, const char *QQ_VERSION, const byte QQ_ASIG[16])
	Func(154, const uint SsoSeq)
	Func(16A, const byte *token_16A)
	Func(16E, const char *_device)
	Func(174, const char *SmsToken)
	Func(177, const uint build_time, const char *SDK_VERSION)
	Func(17A)
	Func(17C, const char *code)
	Func(187)
	Func(188)
	Func(191, const byte CodeType)
	Func(193, const char *Ticket)
	Func(194)
	Func(197)
	Func(198)
	Func(202, const char *BSSID, const char *WiFi_name)
	Func(400, const long long QQ, const byte GUID[16], const uint Time, const byte *token_403)
	Func(401, const byte GUID[16], const byte *token_402)
	Func(511, const char **domainList, const byte ListSize)
	Func(516)
	Func(521)
	Func(525, const uint QQ, const char *IP, const uint Time, const uint APPID, const bool IsEmp)
	Func(52D)
	Func(544, const char *QQ_APKID, const byte QQ_ASIG[16])
	Func(545, const char *qimei)
	Func(547, const byte *ClientPow)
};

#undef Func