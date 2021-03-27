#include "pch.h"
#include "Tlv.h"

unsigned __int16 Tlv::Tlv001(byte* bin, uint len, uint QQ, uint Time)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(1);
	Pack.SetBin_(Utils::GetRandomBin(4), 4);
	Pack.SetInt(QQ);
	Pack.SetInt(Time);
	Pack.SetBin((byte*)"\0\0\0\0\0\0", 6);
	return Pack.Pack(0x0001);
}

unsigned __int16 Tlv::Tlv002(byte* bin, const uint len, const char* code, const char VieryToken1[4])
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(strlen(code));
	Pack.SetStr(code);
	Pack.SetShort(4);
	Pack.SetStr(VieryToken1);
	return Pack.Pack(0x0002);
}

unsigned __int16 Tlv::Tlv008(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetLong(0x08040000);
	return Pack.Pack(0x0008);
}

unsigned __int16 Tlv::Tlv018(byte* bin, const uint len, const uint QQ)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin((const unsigned char*)"\0\1\0\0\6\0\0\0\0\x10\0\0\0\0", 14);
	Pack.SetInt(QQ);
	Pack.SetInt(0);
	return Pack.Pack(0x0018);
}

unsigned __int16 Tlv::Tlv100(byte* bin, const uint len, const uint APPID, const bool IsFreshSkey)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(1);
	Pack.SetInt(0x5);
	Pack.SetInt(0X10);
	Pack.SetInt(IsFreshSkey ? APPID : 1); // Fresh D2Key
	Pack.SetInt(0);
	Pack.SetInt(IsFreshSkey ? 0x021410E0 : 0X001000C0);
	return Pack.Pack(0x0100);
}

unsigned __int16 Tlv::Tlv104(byte* bin, const uint len, const byte VieryToken2[36])
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(VieryToken2, 36);
	return Pack.Pack(0x0104);;
}

unsigned __int16 Tlv::Tlv106(byte* bin, const uint len, const uint QQ, const char* QQ_Str, const byte md5[16], const byte md52[16], const byte TGTKey[16], const byte GUID[16], const uint Time, const uint APPID, bool emp)
{
	::Pack _Pack;
	_Pack.SetShort(4);//_TGTGTVer
	_Pack.SetInt(Utils::GetRandom(129312, 123128723));
	_Pack.SetInt(0xB);//_SSoVer 
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
	return Pack.Pack(0x0106);;
}

unsigned __int16 Tlv::Tlv107(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin((const byte*)"\0\0\0\0\0\1", 6);
	return Pack.Pack(0x0107);;
}

unsigned __int16 Tlv::Tlv108(byte* bin, const uint len, const byte ksid[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(ksid, 16);
	return Pack.Pack(0x0108);
}

unsigned __int16 Tlv::Tlv109(byte* bin, const uint len, const char* IMEI)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(Utils::MD5((byte*)IMEI, strlen(IMEI)), 16);
	return Pack.Pack(0x0109);
}

unsigned __int16 Tlv::Tlv116(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(0);//_ver
	Pack.SetInt(0x08F7FF7C);//mMiscBitmap
	Pack.SetInt(0x00010400);//mSubSigMap
	Pack.SetByte(0);//arr length
	return Pack.Pack(0x0116);
}

unsigned __int16 Tlv::Tlv124(byte* bin, const uint len, const char* os_type, const char* os_version, const unsigned short _network_type, const char* _apn, const char* NetworkName)
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

unsigned __int16 Tlv::Tlv128(byte* bin, const uint len, const char* _device, const char* Brand, const byte GUID[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetBin((const byte*)"\0\0\0\1\1\1\0\0\0", 9);
	Pack.SetShort(strlen(_device));
	Pack.SetStr(_device);
	Pack.SetShort(16);
	Pack.SetBin(GUID, 16);
	Pack.SetShort(strlen(Brand));
	Pack.SetStr(Brand);
	return Pack.Pack(0x0128);
}

unsigned __int16 Tlv::Tlv141(byte* bin, const uint len, const char* NetworkName, const char* NetworkType)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(1);
	Pack.SetShort(strlen(NetworkName));
	Pack.SetStr(NetworkName);
	Pack.SetShort(1);
	Pack.SetShort(strlen(NetworkType));
	Pack.SetStr(NetworkType);
	return Pack.Pack(0x0141);
}

unsigned __int16 Tlv::Tlv142(byte* bin, const uint len, const char* QQ_APKID)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(strlen(QQ_APKID));
	Pack.SetStr(QQ_APKID);
	return Pack.Pack(0x0142);
}

unsigned __int16 Tlv::Tlv144(byte* bin, const uint len, const byte TGTKey[16], const char* IMEI, const char* os_type, const char* os_version, const unsigned short _network_type, const char* _apn, const char* NetworkName, const char* _device, const char* Brand, const byte GUID[16])
{
	::Pack _Pack(500);
	_Pack.SetShort(5);
	_Pack.Skip(Tlv::Tlv109(_Pack.GetCurrentPoint(), _Pack.GetLeftSpace(), IMEI));
	_Pack.Skip(Tlv::Tlv52D(_Pack.GetCurrentPoint(), _Pack.GetLeftSpace()));
	_Pack.Skip(Tlv::Tlv124(_Pack.GetCurrentPoint(), _Pack.GetLeftSpace(), os_type, os_version, _network_type, _apn, NetworkName));
	_Pack.Skip(Tlv::Tlv128(_Pack.GetCurrentPoint(), _Pack.GetLeftSpace(), _device, Brand, GUID));
	_Pack.Skip(Tlv::Tlv16E(_Pack.GetCurrentPoint(), _Pack.GetLeftSpace(), _device));

	std::vector<byte> data;
	Tea::encrypt(TGTKey, _Pack.GetAll(), _Pack.Length(), data);
	delete[] _Pack.GetAll();

	::TlvPack Pack(bin, len);
	Pack.SetBin(&data);
	return Pack.Pack(0x0144);
}

unsigned __int16 Tlv::Tlv145(byte* bin, const uint len, const byte GUID[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(GUID, 16);
	return Pack.Pack(0X0145);
}

unsigned __int16 Tlv::Tlv147(byte* bin, const uint len, const char* QQ_VERSION, const byte QQ_ASIG[16])
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(16);
	Pack.SetShort(strlen(QQ_VERSION));
	Pack.SetStr(QQ_VERSION);
	Pack.SetShort(16);
	Pack.SetBin(QQ_ASIG, 16);
	return Pack.Pack(0X0147);
}

unsigned __int16 Tlv::Tlv154(byte* bin, const uint len, const uint SsoSeq)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(SsoSeq);
	return Pack.Pack(0X0154);
}

unsigned __int16 Tlv::Tlv16A(byte* bin, const uint len, const byte* token_16A)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(token_16A, 56);
	return Pack.Pack(0X016A);
}

unsigned __int16 Tlv::Tlv16E(byte* bin, const uint len, const char* _device)
{
	::TlvPack Pack(bin, len);
	Pack.SetStr(_device);
	return Pack.Pack(0X016E);;
}

unsigned __int16 Tlv::Tlv174(byte* bin, const uint len, const char* SmsToken)
{
	::TlvPack Pack(bin, len);
	Pack.SetStr(SmsToken);
	return Pack.Pack(0X0174);
}

unsigned __int16 Tlv::Tlv177(byte* bin, const uint len, const uint build_time, const char* SDK_VERSION)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(1);
	Pack.SetInt(build_time);
	Pack.SetShort(strlen(SDK_VERSION));
	Pack.SetStr(SDK_VERSION);
	return Pack.Pack(0x0177);
}

unsigned __int16 Tlv::Tlv17A(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(9);
	return Pack.Pack(0X017A);;
}

unsigned __int16 Tlv::Tlv17C(byte* bin, const uint len, const char* code)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(strlen(code));
	Pack.SetStr(code);
	return Pack.Pack(0X017C);
}

unsigned __int16 Tlv::Tlv187(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin_(Utils::GetRandomBin(16), 16);
	return Pack.Pack(0X0187);
}

unsigned __int16 Tlv::Tlv188(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin_(Utils::GetRandomBin(16), 16);
	return Pack.Pack(0X0188);
}

//CodeType 验证码类型 1:字母 130:滑块
unsigned __int16 Tlv::Tlv191(byte* bin, const uint len, const byte CodeType)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(CodeType);
	return Pack.Pack(0X0191);
}

unsigned __int16 Tlv::Tlv193(byte* bin, const uint len, const char* Ticket)
{
	::TlvPack Pack(bin, len);
	Pack.SetStr(Ticket);
	return Pack.Pack(0X0193);
}

unsigned __int16 Tlv::Tlv194(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin_(Utils::GetRandomBin(16), 16);
	return Pack.Pack(0X0194);
}

unsigned __int16 Tlv::Tlv197(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(0);
	return Pack.Pack(0X0197);
}

unsigned __int16 Tlv::Tlv198(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetByte(0);
	return Pack.Pack(0X0198);
}

unsigned __int16 Tlv::Tlv202(byte* bin, const uint len, const char* BSSID, const char* WiFi_name)
{
	::TlvPack Pack(bin, len);
	Pack.SetShort(16);
	Pack.SetBin(Utils::MD5((byte*)BSSID, strlen(BSSID)), 16);
	Pack.SetShort(strlen(WiFi_name));
	Pack.SetStr(WiFi_name);
	return Pack.Pack(0X0202);
}

unsigned __int16 Tlv::Tlv400(byte* bin, const uint len, const long long QQ, const byte GUID[16], const uint Time, const byte* token_403)
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

unsigned __int16 Tlv::Tlv401(byte* bin, const uint len, const byte GUID[16], const byte* token_402)
{
	::TlvPack Pack(bin, len);
	byte b[32];
	memcpy(b, GUID, 16);
	memcpy(b + 15, Utils::GetRandomBin(16), 16);
	memcpy(b + 31, token_402, 1);
	Pack.SetBin(Utils::MD5(b, 24), 16);
	return Pack.Pack(0X0401);
}

unsigned __int16 Tlv::Tlv511(byte* bin, const uint len, const char** domainList, const byte ListSize)
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

unsigned __int16 Tlv::Tlv516(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(0);
	return Pack.Pack(0X0516);
}

unsigned __int16 Tlv::Tlv521(byte* bin, const uint len)
{
	//未知组包
	::TlvPack Pack(bin, len);
	Pack.SetInt(0);
	Pack.SetShort(0);
	return Pack.Pack(0X0521);
}

unsigned __int16 Tlv::Tlv525(byte* bin, const uint len, const uint QQ, const char* IP, const uint Time, const uint APPID, const bool IsEmp)
{
	::TlvPack Pack(bin, len);
	Pack.SetInt(0x00010536);
	Pack.SetByte(0);
	if (IsEmp)
	{
		Pack.SetByte(0x41);
		Pack.SetByte(1);
		Pack.SetByte(0); //ArrLegth
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
	}
	else
	{
		Pack.SetByte(2);
		Pack.SetByte(1);
		Pack.SetByte(0);
	}
	return Pack.Pack(0X0525);
}

unsigned __int16 Tlv::Tlv52D(byte* bin, const uint len)
{
	::TlvPack Pack(bin, len);

	ProtobufStruct::TreeNode Node9{ nullptr,nullptr,9,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x20""eng.se.infra.20191230.112159" };
	ProtobufStruct::TreeNode Node8{ nullptr,&Node9,8,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x0E""no message" };
	ProtobufStruct::TreeNode Node7{ nullptr,&Node8,7,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x14""b17313ff4d8d04f9" };
	ProtobufStruct::TreeNode Node6{ nullptr,&Node7,6,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x28""dd049e10-2740-420f-a6e4-6832791fc40e" };
	ProtobufStruct::TreeNode Node5{ nullptr,&Node6,5,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x3F""Xiaomi/Xiaomi/Alphe:5.1.1/20171130.376229:user/release-keys" };
	ProtobufStruct::TreeNode Node4{ nullptr,&Node5,4,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x20""eng.se.infra.20191230.112159" };
	ProtobufStruct::TreeNode Node3{ nullptr,&Node4,3,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x07""REL" };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node3,2,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x6C""Linux version 4.0.9 (dxu@mv-mobl1) (gcc version 4.8 (GCC) ) #27 SMP PREEMPT Mon Dec 30 11:06:57 CST 2019" };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\x09""uboot" };

	Protobuf PB;
	Pack.SetBinEx_(PB.Pack(&Node1));
	return Pack.Pack(0x052D);
}

unsigned __int16 Tlv::Tlv544(byte* bin, const uint len, const char* QQ_APKID, const byte QQ_ASIG[16])
{
	//懒得研究了,太复杂了
	::TlvPack Pack(bin, len);
	Pack.SetInt(0x07D9);
	Pack.SetShort(0);
	Pack.SetShort(0);
	Pack.SetInt(0x00220020);
	Pack.SetBin((byte*)"\x9C\x10\x39\xC7\xFB\x6C\x18\x2B\x33\x66\xB7\xFC\x4E\x8E\x3D\xC6\x2D\xB7\x88\xC4\x12\xBC\xB1\x46\x9E\x74\x82\x3A\xC2\xC1\x88\xB9\x01\x00\x00\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x01\x6F\xD0\xB0\x72\xBD\x39\x79\x41\x41\x73\x46\x79\x41\x46\x70", 62);
	Pack.SetShort(strlen(QQ_APKID));
	Pack.SetStr(QQ_APKID);
	Pack.SetStr(XBin::Bin2Hex(QQ_ASIG, 16));
	Pack.SetInt(0x04D26C9F);
	Pack.SetInt(0);
	return Pack.Pack(0x0544);
}

unsigned __int16 Tlv::Tlv545(byte* bin, const uint len, const char* qimei)
{
	::TlvPack Pack(bin, len);
	Pack.SetBin(Utils::MD5((byte*)qimei, strlen(qimei)), 16);
	return Pack.Pack(0x0545);
}

unsigned __int16 Tlv::Tlv547(byte* bin, const uint len, const byte* ClientPow)
{
	struct PowValue
	{
		int a, b, c, d, e;
		int f[3];
		int g, i, k, m;
		byte* h, * j, * l, * n;
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
	if (PowValue.g > 0) {
		PowValue.h = new byte[PowValue.g];
		for (size_t i = 0; i < PowValue.g; i++, i1++)
		{
			PowValue.h[i] = ClientPow[i1];
		}
	}
	PowValue.i = XBin::Bin2Short(ClientPow + i1);
	i2 = i1 + 2;
	if (PowValue.i > 0) {
		PowValue.j = new byte[PowValue.i];
		for (size_t i = 0; i < PowValue.i; i++, i2++)
		{
			PowValue.j[i] = ClientPow[i2];
		}
	}
	PowValue.k = XBin::Bin2Short(ClientPow + i2);
	i3 = i2 + 2;
	if (PowValue.k > 0) {
		PowValue.l = new byte[PowValue.k];
		for (size_t i = 0; i < PowValue.k; i++, i3++)
		{
			PowValue.l[i] = ClientPow[i3];
		}
	}
	if (PowValue.e == 1) {
		PowValue.m = XBin::Bin2Short(ClientPow + i3);
		int i4 = i3 + 2;
		if (PowValue.m > 0) {
			PowValue.n = new byte[PowValue.m];
			for (size_t i = 0; i < PowValue.k; i++, i4++)
			{
				PowValue.n[i] = ClientPow[i4];
			}
		}
	}
	long currentTimeMillis = Utils::CurrentTimeMillis();
	switch (PowValue.b) {
	case 1:
		switch (PowValue.c)
		{
		case 1:
			byte * sha256;
			PowValue.n = new byte[PowValue.g];
			PowValue.m = PowValue.g;
			memcpy(PowValue.n, PowValue.h, PowValue.g);
			while (true)
			{
				sha256 = Utils::Sha256(PowValue.n, PowValue.g);
				if (PowValue.d <= 32) {
					for (int i = 255, j = 0; i >= 0 && j < PowValue.d; i--, j++)
					{
						if ((sha256[i / 8] & (1 << (i % 8))) != 0) goto LoopTail;
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
		byte * sha256;
		PowValue.n = new byte[PowValue.g];
		PowValue.m = PowValue.g;
		memcpy(PowValue.n, PowValue.h, PowValue.g);
		switch (PowValue.c)
		{
		case 1:
			while (true)
			{
				sha256 = Utils::Sha256(PowValue.n, PowValue.g);
				if (memcmp(sha256, PowValue.j, PowValue.i) == 0) break;
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
	for (int i : PowValue.f) {
		Pack.SetByte(i);
	}
	Pack.SetShort(PowValue.g);
	Pack.SetBin_(PowValue.h, PowValue.g);
	Pack.SetShort(PowValue.i);
	Pack.SetBin_(PowValue.j, PowValue.i);
	Pack.SetShort(PowValue.k);
	Pack.SetBin_(PowValue.l, PowValue.k);
	if (PowValue.e == 1) {
		Pack.SetShort(PowValue.m);
		Pack.SetBin_(PowValue.n, PowValue.m);
		Pack.SetInt(PowValue.o);
		Pack.SetInt(PowValue.p);
	}
	return Pack.Pack(0x0547);
}