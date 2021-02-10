#pragma once

#include "Protobuf.h"
#include "Tea.h"

namespace Tlv
{
	unsigned __int16 Tlv001(byte* bin, const uint len, uint QQ, uint Time);
	unsigned __int16 Tlv002(byte* bin, const uint len, const char* code, const char VieryToken1[4]);
	unsigned __int16 Tlv008(byte* bin, const uint len);
	unsigned __int16 Tlv018(byte* bin, const uint len, const uint QQ);
	unsigned __int16 Tlv100(byte* bin, const uint len, const uint APPID, const bool IsFreshSkey);
	unsigned __int16 Tlv104(byte* bin, const uint len, const byte VieryToken2[36]);
	unsigned __int16 Tlv106(byte* bin, const uint len, const uint QQ, const char* QQ_Str, const byte md5[16], const byte md52[16], const byte TGTKey[16], const byte GUID[16], const uint Time, const uint APPID, bool emp);
	unsigned __int16 Tlv107(byte* bin, const uint len);
	unsigned __int16 Tlv108(byte* bin, const uint len, const byte ksid[16]);
	unsigned __int16 Tlv109(byte* bin, const uint len, const char* IMEI);
	unsigned __int16 Tlv116(byte* bin, const uint len);
	unsigned __int16 Tlv124(byte* bin, const uint len, const char* os_type, const char* os_version, const unsigned short _network_type, const char* _apn, const char* NetworkName);
	unsigned __int16 Tlv128(byte* bin, const uint len, const char* _device, const char* Brand, const byte GUID[16]);
	unsigned __int16 Tlv141(byte* bin, const uint len, const char* NetworkName, const char* NetworkType);
	unsigned __int16 Tlv142(byte* bin, const uint len, const char* QQ_APKID);
	unsigned __int16 Tlv144(byte* bin, const uint len, const byte TGTKey[16], const char* IMEI, const char* os_type, const char* os_version, const unsigned short _network_type, const char* _apn, const char* NetworkName, const char* _device, const char* Brand, const byte GUID[16]);
	unsigned __int16 Tlv145(byte* bin, const uint len, const byte GUID[16]);
	unsigned __int16 Tlv147(byte* bin, const uint len, const char* QQ_VERSION, const byte QQ_ASIG[16]);
	unsigned __int16 Tlv154(byte* bin, const uint len, const uint SsoSeq);
	unsigned __int16 Tlv16A(byte* bin, const uint len, const byte* token_16A);
	unsigned __int16 Tlv16E(byte* bin, const uint len, const char* _device);
	unsigned __int16 Tlv174(byte* bin, const uint len, const char* SmsToken);
	unsigned __int16 Tlv177(byte* bin, const uint len, const uint build_time, const char* SDK_VERSION);
	unsigned __int16 Tlv17A(byte* bin, const uint len);
	unsigned __int16 Tlv17C(byte* bin, const uint len, const char* code);
	unsigned __int16 Tlv187(byte* bin, const uint len);
	unsigned __int16 Tlv188(byte* bin, const uint len);
	unsigned __int16 Tlv191(byte* bin, const uint len, const byte CodeType);
	unsigned __int16 Tlv193(byte* bin, const uint len, const char* Ticket);
	unsigned __int16 Tlv194(byte* bin, const uint len);
	unsigned __int16 Tlv197(byte* bin, const uint len);
	unsigned __int16 Tlv198(byte* bin, const uint len);
	unsigned __int16 Tlv202(byte* bin, const uint len, const char* BSSID, const char* WiFi_name);
	unsigned __int16 Tlv400(byte* bin, const uint len, const long long QQ, const byte GUID[16], const uint Time, const byte* token_403);
	unsigned __int16 Tlv401(byte* bin, const uint len, const byte GUID[16], const byte* token_402);
	unsigned __int16 Tlv511(byte* bin, const uint len, const char** domainList, const byte ListSize);
	unsigned __int16 Tlv516(byte* bin, const uint len);
	unsigned __int16 Tlv521(byte* bin, const uint len);
	unsigned __int16 Tlv525(byte* bin, const uint len, const uint QQ, const char* IP, const uint Time, const uint APPID, const bool IsEmp);
	unsigned __int16 Tlv52D(byte* bin, const uint len);
	unsigned __int16 Tlv544(byte* bin, const uint len, const char* QQ_APKID, const byte QQ_ASIG[16]);
	unsigned __int16 Tlv545(byte* bin, const uint len, const char* qimei);
	unsigned __int16 Tlv547(byte* bin, const uint len, const byte* ClientPow);
};