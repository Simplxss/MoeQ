#include "Tlv.h"

#define FUNC(TlvName, ...) uint16_t Tlv::Tlv##TlvName(byte *bin, const uint len, ##__VA_ARGS__)

FUNC(001, uint QQ, uint Time)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(1);
	Pack.SetBin_(Utils::GetRandomBin(4), 4);
	Pack.SetInt(QQ);
	Pack.SetInt(Time);
	Pack.SetBin((byte *)"\0\0\0\0\0\0", 6);
	return Pack.Pack(0x0001);
}

FUNC(002, const char *code, const char VieryToken1[4])
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(strlen(code));
	Pack.SetStr(code);
	Pack.SetShort(4);
	Pack.SetStr(VieryToken1);
	return Pack.Pack(0x0002);
}

FUNC(008)
{
	::TlvPack Pack(bin, len);
	Pack.SetLong(0x08040000);
	return Pack.Pack(0x0008);
}

FUNC(018, const uint QQ)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin((const unsigned char *)"\0\1\0\0\6\0\0\0\0\x10\0\0\0\0", 14);
	Pack.SetInt(QQ);
	Pack.SetInt(0);
	return Pack.Pack(0x0018);
}

FUNC(100, const uint APPID, const bool IsFreshSkey)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(1);  //_db_buf_ver
	Pack.SetInt(0x12);  //_sso_ver
	Pack.SetInt(0X10);
	Pack.SetInt(IsFreshSkey ? APPID : 1); // Fresh D2Key
	Pack.SetInt(0);
	Pack.SetInt(IsFreshSkey ? 0x021410E0 : 0X001000C0);
	return Pack.Pack(0x0100);
}

FUNC(104, const byte VieryToken2[36])
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(VieryToken2, 36);
	return Pack.Pack(0x0104);
	;
}

FUNC(106, const uint QQ, const char *QQ_Str, const byte md5[16], const byte md52[16], const byte TGTKey[16], const byte GUID[16], const uint Time, const uint APPID, bool emp)
{
	::Pack _Pack;
	_Pack.SetShort(4); //_TGTGTVer
	_Pack.SetInt(Utils::GetRandom(129312, 123128723));
	_Pack.SetInt(0x12); //_SSoVer
	_Pack.SetInt(0X10);
	_Pack.SetInt(0);
	_Pack.SetLong(QQ);
	_Pack.SetInt(Time);
	_Pack.SetInt(0);
	_Pack.SetByte(1);
	_Pack.SetBin(md5, 16);
	_Pack.SetBin(TGTKey, 16);
	_Pack.SetInt(emp ? 1 : 0);
	_Pack.SetByte(1);
	_Pack.SetBin(GUID, 16);
	_Pack.SetInt(APPID);
	_Pack.SetInt(1);
	_Pack.SetShort(strlen(QQ_Str));
	_Pack.SetStr(QQ_Str);
	_Pack.SetShort(0);

	std::vector<byte> data;
	Tea::encrypt(md52, _Pack.GetAll(), _Pack.Length(), data);
	delete[] _Pack.GetAll();

	::TlvPack Pack(bin, len);
	Pack.SetBin(&data);
	return Pack.Pack(0x0106);
	;
}

FUNC(107)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin((const byte *)"\0\0\0\0\0\1", 6);
	return Pack.Pack(0x0107);
	;
}

FUNC(108, const byte ksid[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(ksid, 16);
	return Pack.Pack(0x0108);
}

FUNC(109, const char *IMEI)
{
	::TlvPack Pack(bin, len);
	Pack.SetMD5((byte *)IMEI, strlen(IMEI));
	return Pack.Pack(0x0109);
}

FUNC(116)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(0);		 // _ver
	Pack.SetInt(0x08F7FF7C); // mMiscBitmap
	Pack.SetInt(0x00010400); // mSubSigMap
	Pack.SetByte(0);		 // arr length
	return Pack.Pack(0x0116);
}

FUNC(124, const char *os_type, const char *os_version, const unsigned short _network_type, const char *_apn, const char *NetworkName)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(strlen(os_type));
	Pack.SetStr(os_type);
	Pack.SetShort(strlen(os_version));
	Pack.SetStr(os_version);
	Pack.SetShort(_network_type);
	Pack.SetShort(strlen(NetworkName));
	Pack.SetStr(NetworkName);
	Pack.SetShort(0);
	Pack.SetShort(strlen(_apn));
	Pack.SetStr(_apn);
	return Pack.Pack(0x0124);
}

FUNC(128, const char *_device, const char *Brand, const byte GUID[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(0);
	Pack.SetByte(0);
	Pack.SetByte(1);
	Pack.SetByte(0);
	Pack.SetInt(0x1000);
	Pack.SetShort(strlen(_device));
	Pack.SetStr(_device);
	Pack.SetShort(16);
	Pack.SetBin(GUID, 16);
	Pack.SetShort(strlen(Brand));
	Pack.SetStr(Brand);
	return Pack.Pack(0x0128);
}

FUNC(141, const char *NetworkName, const char *apn)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(1);
	Pack.SetShort(strlen(NetworkName));
	Pack.SetStr(NetworkName);
	Pack.SetShort(2);
	Pack.SetShort(strlen(apn));
	Pack.SetStr(apn);
	return Pack.Pack(0x0141);
}

FUNC(142, const char *AndroidQQ_APKID)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(strlen(AndroidQQ_APKID));
	Pack.SetStr(AndroidQQ_APKID);
	return Pack.Pack(0x0142);
}

FUNC(144, const byte TGTKey[16], const char *IMEI, const char *os_type, const char *os_version, const unsigned short _network_type, const char *_apn, const char *NetworkName, const char *_device, const char *Brand, const byte GUID[16])
{
	::Pack _Pack(500);
	_Pack.SetShort(5);

#define PackTlv(TlvName, ...) _Pack.Skip(Tlv::Tlv##TlvName(_Pack.GetCurrentPoint(), _Pack.GetLeftSpace(), ##__VA_ARGS__))

	PackTlv(109, IMEI);
	PackTlv(52D);
	PackTlv(124, os_type, os_version, _network_type, _apn, NetworkName);
	PackTlv(128, _device, Brand, GUID);
	PackTlv(16E, _device);

#undef PackTlv

	std::vector<byte> data;
	Tea::encrypt(TGTKey, _Pack.GetAll(), _Pack.Length(), data);
	delete[] _Pack.GetAll();

	::TlvPack Pack(bin, len);
	Pack.SetBin(&data);
	return Pack.Pack(0x0144);
}

FUNC(145, const byte GUID[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(GUID, 16);
	return Pack.Pack(0X0145);
}

FUNC(147, const char *QQ_VERSION, const byte AndroidQQ_ASIG[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(0x10);
	Pack.SetShort(strlen(QQ_VERSION));
	Pack.SetStr(QQ_VERSION);
	Pack.SetShort(16);
	Pack.SetBin(AndroidQQ_ASIG, 16);
	return Pack.Pack(0X0147);
}

FUNC(154, const uint SsoSeq)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(SsoSeq);
	return Pack.Pack(0X0154);
}

FUNC(16A, const byte *token_16A)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(token_16A, 56);
	return Pack.Pack(0X016A);
}

FUNC(16E, const char *_device)
{
	::TlvPack Pack(bin, len);
	Pack.SetStr(_device);
	return Pack.Pack(0X016E);
	;
}

FUNC(174, const char *SmsToken)
{
	::TlvPack Pack(bin, len);
	Pack.SetStr(SmsToken);
	return Pack.Pack(0X0174);
}

FUNC(177, const uint build_time, const char *SDK_VERSION)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(1);
	Pack.SetInt(build_time);
	Pack.SetShort(strlen(SDK_VERSION));
	Pack.SetStr(SDK_VERSION);
	return Pack.Pack(0x0177);
}

FUNC(17A)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(9);
	return Pack.Pack(0X017A);
	;
}

FUNC(17C, const char *code)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(strlen(code));
	Pack.SetStr(code);
	return Pack.Pack(0X017C);
}

FUNC(187)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin_(Utils::GetRandomBin(16), 16);
	return Pack.Pack(0X0187);
}

FUNC(188)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin_(Utils::GetRandomBin(16), 16);
	return Pack.Pack(0X0188);
}

// CodeType 验证码类型 0x01:字母 0x82:滑块
FUNC(191, const byte CodeType)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(CodeType);
	return Pack.Pack(0X0191);
}

FUNC(193, const char *Ticket)
{
	::TlvPack Pack(bin, len);
	Pack.SetStr(Ticket);
	return Pack.Pack(0X0193);
}

FUNC(194)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin_(Utils::GetRandomBin(16), 16);
	return Pack.Pack(0X0194);
}

FUNC(197)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(0);
	return Pack.Pack(0X0197);
}

FUNC(198)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(0);
	return Pack.Pack(0X0198);
}

FUNC(202, const char *BSSID, const char *WiFi_name)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(16);
	Pack.SetMD5((byte *)BSSID, strlen(BSSID));
	Pack.SetShort(strlen(WiFi_name));
	Pack.SetStr(WiFi_name);
	return Pack.Pack(0X0202);
}

FUNC(400, const long long QQ, const byte GUID[16], const uint Time, const byte *token_403)
{
	::Pack _Pack;
	_Pack.SetShort(1);
	_Pack.SetLong(QQ);
	_Pack.SetBin(GUID, 16);
	_Pack.SetStr_(Utils::GetRandomLetter(16));
	_Pack.SetInt(16);
	_Pack.SetInt(1);
	_Pack.SetInt(Time);
	_Pack.SetBin(token_403, 8);

	std::vector<byte> data;
	Tea::encrypt(GUID, _Pack.GetAll(), _Pack.Length(), data);
	delete[] _Pack.GetAll();

	::TlvPack Pack(bin, len);
	Pack.SetBin(&data);
	return Pack.Pack(0X0400);
}

FUNC(401, const byte GUID[16], const byte *token_402)
{
	::TlvPack Pack(bin, len);
	byte b[32];
	memcpy(b, GUID, 16);
	memcpy(b + 15, Utils::GetRandomBin(16), 16);
	memcpy(b + 31, token_402, 1);
	Pack.SetMD5(b, 24);
	return Pack.Pack(0X0401);
}

FUNC(511, const char **domainList, const byte ListSize)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(ListSize);
	for (size_t i = 0; i < ListSize; i++)
	{
		Pack.SetByte(1);
		Pack.SetShort(strlen(domainList[i]));
		Pack.SetStr(domainList[i]);
	}
	return Pack.Pack(0X0511);
}

FUNC(516)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(0);
	return Pack.Pack(0X0516);
}

FUNC(521)
{
	//未知组包
	::TlvPack Pack(bin, len);
	Pack.SetInt(0);
	Pack.SetShort(0);
	return Pack.Pack(0X0521);
}

FUNC(525, const uint QQ, const char *IP, const uint Time, const uint APPID, const bool IsEmp)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(0x00010536);
	Pack.SetByte(0);
	Pack.SetByte(0x4D);
	Pack.SetByte(1);
	Pack.SetByte(0); // ArrLegth

	/*
	Pack.SetInt(0);
	Pack.SetInt(QQ);
	Pack.SetByte(4);
	Pack.SetBin_(XBin::IP2Bin(IP), 4);
	Pack.SetInt(Time);
	Pack.SetInt(APPID);

	Pack.SetInt(0);
	Pack.SetInt(QQ);
	Pack.SetByte(4);
	Pack.SetBin_(XBin::IP2Bin(IP), 4);
	Pack.SetInt(Time);
	Pack.SetInt(APPID);

	Pack.SetInt(0);
	Pack.SetInt(QQ);
	Pack.SetByte(4);
	Pack.SetBin_(XBin::IP2Bin(IP), 4);
	Pack.SetInt(Time);
	Pack.SetInt(APPID);
	*/

	return Pack.Pack(0X0525);
}

FUNC(52D)
{
	::TlvPack Pack(bin, len);

	ProtobufStruct::TreeNode Node9{nullptr, nullptr, 9, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x15"
																											"V12.5.1.0.QEBCNXM"};
	ProtobufStruct::TreeNode Node8{nullptr, &Node9, 8, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x04"
																										   ""};
	ProtobufStruct::TreeNode Node7{nullptr, &Node8, 7, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x14"
																										   "81fc47b45c9ffc34"};
	ProtobufStruct::TreeNode Node6{nullptr, &Node7, 6, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x28"
																										   "30417589-e527-49fc-bb09-bb8607684674"};
	ProtobufStruct::TreeNode Node5{nullptr, &Node6, 5, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x4F"
																										   "Xiaomi/sirius/sirius:10/QKQ1.190828.002/V12.5.1.0.QEBCNXM:user/release-keys"};
	ProtobufStruct::TreeNode Node4{nullptr, &Node5, 4, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x15"
																										   "V12.5.1.0.QEBCNXM"};
	ProtobufStruct::TreeNode Node3{nullptr, &Node4, 3, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x07"
																										   "REL"};
	ProtobufStruct::TreeNode Node2{nullptr, &Node3, 2, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x04"
																										   ""};
	ProtobufStruct::TreeNode Node1{nullptr, &Node2, 1, ProtobufStruct::ProtobufStructType::LENGTH, (void *)"\0\0\0\x0B"
																										   "unknown"};

	Protobuf PB;
	Pack.SetBinEx_(PB.Pack(&Node1));
	return Pack.Pack(0x052D);
}

FUNC(542)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(0x4A026001);
	return Pack.Pack(0X0542);
}

FUNC(544, const char *AndroidQQ_APKID, const byte AndroidQQ_ASIG[16])
{
	//构造在so层
	::TlvPack Pack(bin, len);
	Pack.SetInt(0x68656861);
	Pack.SetBin((byte *)"\x00\x00\x00\x01\x01\x00\x00\x00\x00\x00\x00\x00\x01\x01\x00\x05\x05\x00\x00\x00\x00", 22);
	Pack.SetInt(0xB18E8915);
	Pack.SetInt(0x2);
	Pack.SetInt(0xA6);

	Pack.SetShort(1);
	Pack.SetShort(8);
	Pack.SetLong(0x01821F7E440B);

	Pack.SetShort(2);
	Pack.SetShort(10);
	Pack.SetStr("E#qfCr$gsM");

	Pack.SetShort(3);
	Pack.SetShort(4);
	Pack.SetInt(0x01000001);

	Pack.SetShort(5);
	Pack.SetShort(4);
	Pack.SetInt(0x01000001);

	Pack.SetShort(4);
	Pack.SetShort(4);
	Pack.SetInt(0);

	Pack.SetShort(6);
	Pack.SetShort(4);
	Pack.SetInt(1);

	Pack.SetShort(7);
	Pack.SetShort(4);
	Pack.SetInt(0x01000005);

	Pack.SetShort(8);
	Pack.SetShort(4);
	Pack.SetInt(0x01000005);

	Pack.SetShort(9);
	Pack.SetShort(0x20);
	Pack.SetBin((byte *)"\x9F\x45\x49\x3B\x6A\xDE\x97\xC3\x7E\xDA\x54\x80\x1F\x68\x76\x07\xD6\x36\x43\xEE\xF4\x02\x2F\x95\x85\x42\x97\x61\x55\x04\x39\xEC", 32);

	Pack.SetShort(10);
	Pack.SetShort(0x10);
	Pack.SetBin((byte *)"\xC4\x74\xDB\x96\x88\xB6\x03\x36\x3D\x37\x30\x81\x63\x11\x32\x15", 16);

	Pack.SetShort(11);
	Pack.SetShort(0x10);
	Pack.SetBin((byte *)"\xFF\xD1\x8C\x92\x18\xE1\x1C\x33\xFC\x07\xEE\xA7\x51\x46\xEB\xC8", 16);

	Pack.SetShort(12);
	Pack.SetShort(4);
	Pack.SetInt(0x01000001);

	Pack.SetShort(13);
	Pack.SetShort(4);
	Pack.SetInt(2);

	return Pack.Pack(0x0544);
}

FUNC(545)
{
	//算法未知 在so层中
	::TlvPack Pack(bin, len);
	Pack.SetBin_((byte*)XBin::Bin2Hex(Utils::GetRandomBin(16), 16), 32);  //IMEI
	return Pack.Pack(0x0545);
}

FUNC(547, const byte *ClientPow)
{
	struct PowValue
	{
		int a, b, c, d, e;
		int f[3];
		int g, i, k, m;
		byte *h, *j, *l, *n;
		int o, p = 0;
	};

	::TlvPack Pack(bin, len);
	PowValue PowValue;
	int i1, i2, i3;
	PowValue.a = ClientPow[0];
	PowValue.b = ClientPow[1];
	PowValue.c = ClientPow[2];
	PowValue.d = ClientPow[3];
	PowValue.e = ClientPow[4];
	for (size_t i = 0, j = 5; i < 3; i++, j++)
	{
		PowValue.f[i] = ClientPow[j];
	}
	PowValue.g = XBin::Bin2Short(ClientPow + 8);
	i1 = 10;
	if (PowValue.g > 0)
	{
		PowValue.h = new byte[PowValue.g];
		for (size_t i = 0; i < PowValue.g; i++, i1++)
		{
			PowValue.h[i] = ClientPow[i1];
		}
	}
	PowValue.i = XBin::Bin2Short(ClientPow + i1);
	i2 = i1 + 2;
	if (PowValue.i > 0)
	{
		PowValue.j = new byte[PowValue.i];
		for (size_t i = 0; i < PowValue.i; i++, i2++)
		{
			PowValue.j[i] = ClientPow[i2];
		}
	}
	PowValue.k = XBin::Bin2Short(ClientPow + i2);
	i3 = i2 + 2;
	if (PowValue.k > 0)
	{
		PowValue.l = new byte[PowValue.k];
		for (size_t i = 0; i < PowValue.k; i++, i3++)
		{
			PowValue.l[i] = ClientPow[i3];
		}
	}
	if (PowValue.e == 1)
	{
		PowValue.m = XBin::Bin2Short(ClientPow + i3);
		int i4 = i3 + 2;
		if (PowValue.m > 0)
		{
			PowValue.n = new byte[PowValue.m];
			for (size_t i = 0; i < PowValue.k; i++, i4++)
			{
				PowValue.n[i] = ClientPow[i4];
			}
		}
	}
	long currentTimeMillis = Utils::CurrentTimeMillis();
	switch (PowValue.b)
	{
	case 1:
		switch (PowValue.c)
		{
		case 1:
			byte *sha256;
			PowValue.n = new byte[PowValue.g];
			PowValue.m = PowValue.g;
			memcpy(PowValue.n, PowValue.h, PowValue.g);
			while (true)
			{
				sha256 = Utils::Sha256(PowValue.n, PowValue.g);
				if (PowValue.d <= 32)
				{
					for (int i = 255, j = 0; i >= 0 && j < PowValue.d; i--, j++)
					{
						if ((sha256[i / 8] & (1 << (i % 8))) != 0)
							goto LoopTail;
					}
					break;
				}
			LoopTail:
				PowValue.p++;
				if (!BigInteger::AddOne(PowValue.n, PowValue.m))
				{
					throw "big number too large";
					return 0;
				}
			}
			break;
		case 2:
			throw "hash func not support sm3";
			return 0;
		default:
			throw "error hash func";
			return 0;
		}
	case 2:
		byte *sha256;
		PowValue.n = new byte[PowValue.g];
		PowValue.m = PowValue.g;
		memcpy(PowValue.n, PowValue.h, PowValue.g);
		switch (PowValue.c)
		{
		case 1:
			while (true)
			{
				sha256 = Utils::Sha256(PowValue.n, PowValue.g);
				if (memcmp(sha256, PowValue.j, PowValue.i) == 0)
					break;
				PowValue.p++;
				if (!BigInteger::AddOne(PowValue.n, PowValue.m))
				{
					throw "big number too large";
					return 0;
				}
			}
			break;
		case 2:
			throw "hash func not support sm3";
			return 0;
		default:
			throw "error hash func";
			return 0;
		}
		break;
	default:
		throw "not support algorithm";
		return 0;
	}
	PowValue.o = (int)(Utils::CurrentTimeMillis() - currentTimeMillis);
	PowValue.e = 1;
	Pack.SetByte(PowValue.a);
	Pack.SetByte(PowValue.b);
	Pack.SetByte(PowValue.c);
	Pack.SetByte(PowValue.d);
	Pack.SetByte(PowValue.e);
	for (int i : PowValue.f)
	{
		Pack.SetByte(i);
	}
	Pack.SetShort(PowValue.g);
	Pack.SetBin_(PowValue.h, PowValue.g);
	Pack.SetShort(PowValue.i);
	Pack.SetBin_(PowValue.j, PowValue.i);
	Pack.SetShort(PowValue.k);
	Pack.SetBin_(PowValue.l, PowValue.k);
	if (PowValue.e == 1)
	{
		Pack.SetShort(PowValue.m);
		Pack.SetBin_(PowValue.n, PowValue.m);
		Pack.SetInt(PowValue.o);
		Pack.SetInt(PowValue.p);
	}
	return Pack.Pack(0x0547);
}

FUNC(548)
{
	//算法未知
	::TlvPack Pack(bin, len);
	return Pack.Pack(0X0548);
}

#undef FUNC