#pragma once

#include "Protobuf.h"
#include "Tea.h"

namespace Tlv
{
	uint16_t Tlv001(byte* bin, const uint len, uint QQ, uint Time);
	uint16_t Tlv002(byte* bin, const uint len, const char* code, const char VieryToken1[4]);
	uint16_t Tlv008(byte* bin, const uint len);
	uint16_t Tlv018(byte* bin, const uint len, const uint QQ);
	uint16_t Tlv100(byte* bin, const uint len, const uint APPID, const bool IsFreshSkey);
	uint16_t Tlv104(byte* bin, const uint len, const byte VieryToken2[36]);
	uint16_t Tlv106(byte* bin, const uint len, const uint QQ, const char* QQ_Str, const byte md5[16], const byte md52[16], const byte TGTKey[16], const byte GUID[16], const uint Time, const uint APPID, bool emp);
	uint16_t Tlv107(byte* bin, const uint len);
	uint16_t Tlv108(byte* bin, const uint len, const byte ksid[16]);
	uint16_t Tlv109(byte* bin, const uint len, const char* IMEI);
	uint16_t Tlv116(byte* bin, const uint len);
	uint16_t Tlv124(byte* bin, const uint len, const char* os_type, const char* os_version, const unsigned short _network_type, const char* _apn, const char* NetworkName);
	uint16_t Tlv128(byte* bin, const uint len, const char* _device, const char* Brand, const byte GUID[16]);
	uint16_t Tlv141(byte* bin, const uint len, const char* NetworkName, const char* NetworkType);
	uint16_t Tlv142(byte* bin, const uint len, const char* QQ_APKID);
	uint16_t Tlv144(byte* bin, const uint len, const byte TGTKey[16], const char* IMEI, const char* os_type, const char* os_version, const unsigned short _network_type, const char* _apn, const char* NetworkName, const char* _device, const char* Brand, const byte GUID[16]);
	uint16_t Tlv145(byte* bin, const uint len, const byte GUID[16]);
	uint16_t Tlv147(byte* bin, const uint len, const char* QQ_VERSION, const byte QQ_ASIG[16]);
	uint16_t Tlv154(byte* bin, const uint len, const uint SsoSeq);
	uint16_t Tlv16A(byte* bin, const uint len, const byte* token_16A);
	uint16_t Tlv16E(byte* bin, const uint len, const char* _device);
	uint16_t Tlv174(byte* bin, const uint len, const char* SmsToken);
	uint16_t Tlv177(byte* bin, const uint len, const uint build_time, const char* SDK_VERSION);
	uint16_t Tlv17A(byte* bin, const uint len);
	uint16_t Tlv17C(byte* bin, const uint len, const char* code);
	uint16_t Tlv187(byte* bin, const uint len);
	uint16_t Tlv188(byte* bin, const uint len);
	uint16_t Tlv191(byte* bin, const uint len, const byte CodeType);
	uint16_t Tlv193(byte* bin, const uint len, const char* Ticket);
	uint16_t Tlv194(byte* bin, const uint len);
	uint16_t Tlv197(byte* bin, const uint len);
	uint16_t Tlv198(byte* bin, const uint len);
	uint16_t Tlv202(byte* bin, const uint len, const char* BSSID, const char* WiFi_name);
	uint16_t Tlv400(byte* bin, const uint len, const long long QQ, const byte GUID[16], const uint Time, const byte* token_403);
	uint16_t Tlv401(byte* bin, const uint len, const byte GUID[16], const byte* token_402);
	uint16_t Tlv511(byte* bin, const uint len, const char** domainList, const byte ListSize);
	uint16_t Tlv516(byte* bin, const uint len);
	uint16_t Tlv521(byte* bin, const uint len);
	uint16_t Tlv525(byte* bin, const uint len, const uint QQ, const char* IP, const uint Time, const uint APPID, const bool IsEmp);
	uint16_t Tlv52D(byte* bin, const uint len);
	uint16_t Tlv544(byte* bin, const uint len, const char* QQ_APKID, const byte QQ_ASIG[16]);
	uint16_t Tlv545(byte* bin, const uint len, const char* qimei);
	uint16_t Tlv547(byte* bin, const uint len, const byte* ClientPow);
};