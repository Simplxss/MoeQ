#include "pch.h"
#include "Android.h"

::ThreadPool HandleThreads;

namespace Message
{
	LPBYTE Pack1(const char* Text, const uint AtQQ)
	{
		if (Text == nullptr)
		{
			byte B[17];
			if (AtQQ == 0)
			{
				memcpy(B, "\0\0\0\x11\0\1\0\0\0\5\1\0\0\0\0\0\0", 17);
				Text = (const char*)u8"@全体成员";
			}
			else
			{
				memcpy(B, "\0\0\0\x11\0\1\0\0\0\5\0\0\0\0\0\0\0", 17);
				memcpy(B + 11, XBin::Int2Bin(AtQQ), 4);
				Text = (const char*)u8"@猪";
				//Todo
				//strcat(Text,)
			}
			uint len = strlen(Text);
			LPBYTE T = new byte[len + 4];
			memcpy(T, XBin::Int2Bin(len + 4), 4);
			memcpy(T + 4, Text, len);
			ProtobufStruct::TreeNode Node1_3{ nullptr,nullptr,3,ProtobufStruct::ProtobufStructType::LENGTH, B };
			ProtobufStruct::TreeNode Node1_1{ nullptr,&Node1_3,1,ProtobufStruct::ProtobufStructType::LENGTH, T };
			ProtobufStruct::TreeNode Node1{ &Node1_1,nullptr,1,ProtobufStruct::ProtobufStructType::LENGTH, };
			Protobuf PB;
			LPBYTE bin = PB.Pack(&Node1);
			delete[] T;
			return bin;
		}
		else
		{
			uint len = strlen(Text);
			LPBYTE T = new byte[len + 4];
			memcpy(T, XBin::Int2Bin(len + 4), 4);
			memcpy(T + 4, Text, len);
			ProtobufStruct::TreeNode Node1_1{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::LENGTH, T };
			ProtobufStruct::TreeNode Node1{ &Node1_1,nullptr,1,ProtobufStruct::ProtobufStructType::LENGTH, };
			Protobuf PB;
			return PB.Pack(&Node1);
		}
	}
	LPBYTE Pack2(const byte id)
	{
		ProtobufStruct::TreeNode Node2_1{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT, (void*)id };
		ProtobufStruct::TreeNode Node2{ &Node2_1,nullptr,2,ProtobufStruct::ProtobufStructType::LENGTH, };
		Protobuf PB;
		return PB.Pack(&Node2);
	}
	LPBYTE Pack6(const byte id)
	{
		ProtobufStruct::TreeNode Node2_1{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT, (void*)id };
		ProtobufStruct::TreeNode Node2{ &Node2_1,nullptr,2,ProtobufStruct::ProtobufStructType::LENGTH, };
		Protobuf PB;
		return PB.Pack(&Node2);
	}
	LPBYTE Pack8()//Todo
	{
		ProtobufStruct::TreeNode Node8_34_15{ nullptr,nullptr,15,ProtobufStruct::ProtobufStructType::VARINT,(void*)5 };
		ProtobufStruct::TreeNode Node8_34_10{ nullptr,&Node8_34_15,10,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node8_34_9{ nullptr,&Node8_34_10,9,ProtobufStruct::ProtobufStructType::LENGTH, };
		ProtobufStruct::TreeNode Node8_34_6{ nullptr,&Node8_34_9,6,ProtobufStruct::ProtobufStructType::LENGTH, };
		ProtobufStruct::TreeNode Node8_34_2{ nullptr,&Node8_34_6,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node8_34_1{ nullptr,&Node8_34_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
		ProtobufStruct::TreeNode Node8_34{ &Node8_34_1,nullptr,34,ProtobufStruct::ProtobufStructType::LENGTH, };
		ProtobufStruct::TreeNode Node8_30{ nullptr,&Node8_34,30,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node8_29{ nullptr,&Node8_30,29,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node8_26{ nullptr,&Node8_29,26,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node8_25{ nullptr,&Node8_26,25,ProtobufStruct::ProtobufStructType::VARINT,(void*)14321 };
		ProtobufStruct::TreeNode Node8_24{ nullptr,&Node8_25,24,ProtobufStruct::ProtobufStructType::VARINT,(void*)103 };
		ProtobufStruct::TreeNode Node8_23{ nullptr,&Node8_24,23,ProtobufStruct::ProtobufStructType::VARINT,(void*)267 };
		ProtobufStruct::TreeNode Node8_22{ nullptr,&Node8_23,22,ProtobufStruct::ProtobufStructType::VARINT,(void*)224 };
		ProtobufStruct::TreeNode Node8_20{ nullptr,&Node8_22,20,ProtobufStruct::ProtobufStructType::VARINT,(void*)1000 };
		ProtobufStruct::TreeNode Node8_17{ nullptr,&Node8_20,17,ProtobufStruct::ProtobufStructType::VARINT,(void*)5 };
		ProtobufStruct::TreeNode Node8_13{ nullptr,&Node8_17,13,ProtobufStruct::ProtobufStructType::LENGTH, };
		ProtobufStruct::TreeNode Node8_12{ nullptr,&Node8_13,12,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
		ProtobufStruct::TreeNode Node8_11{ nullptr,&Node8_12,11,ProtobufStruct::ProtobufStructType::LENGTH, };
		ProtobufStruct::TreeNode Node8_10{ nullptr,&Node8_11,10,ProtobufStruct::ProtobufStructType::VARINT,(void*)66 };
		ProtobufStruct::TreeNode Node8_9{ nullptr,&Node8_10,9,ProtobufStruct::ProtobufStructType::VARINT,(void*)80 };
		ProtobufStruct::TreeNode Node8_8{ nullptr,&Node8_9,8,ProtobufStruct::ProtobufStructType::VARINT,(void*)2073511832 };
		ProtobufStruct::TreeNode Node8_7{ nullptr,&Node8_8,7,ProtobufStruct::ProtobufStructType::VARINT,(void*)2893030503 };
		ProtobufStruct::TreeNode Node8_2{ nullptr,&Node8_7,2,ProtobufStruct::ProtobufStructType::LENGTH, };
		ProtobufStruct::TreeNode Node8{ &Node8_2,nullptr,8,ProtobufStruct::ProtobufStructType::LENGTH, };

		Protobuf PB;
		return PB.Pack(&Node8);
	}
	LPBYTE Pack37()
	{
		ProtobufStruct::TreeNode Node37_19_41{ nullptr,nullptr,41,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node37_19_31{ nullptr,&Node37_19_41,31,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node37_19_15{ nullptr,&Node37_19_31,15,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node37_19{ &Node37_19_15,nullptr,19,ProtobufStruct::ProtobufStructType::LENGTH, };
		ProtobufStruct::TreeNode Node37_17{ nullptr,&Node37_19,17,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		ProtobufStruct::TreeNode Node37{ &Node37_17,nullptr,37,ProtobufStruct::ProtobufStructType::LENGTH, };

		Protobuf PB;
		return PB.Pack(&Node37);
	}
	LPBYTE Pack51(const char* Json)
	{
		Pack Pack(500, true);
		Pack.SetByte(1);//压缩
		LPBYTE bin = Utils::ZlibCompress(Json);
		Pack.SetBin(bin + 4, XBin::Bin2Int(bin) - 4);
		Pack.SetLength();
		ProtobufStruct::TreeNode Node51_1{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::LENGTH, Pack.GetAll() };
		ProtobufStruct::TreeNode Node51{ &Node51_1,nullptr,51,ProtobufStruct::ProtobufStructType::LENGTH, };

		Protobuf PB;
		bin = PB.Pack(&Node51);
		delete[] Pack.GetAll();
		return bin;
	}
}

Android::Android(const char* IMEI, const char IMSI[16], const byte GUID[16], const byte MAC[6], const char* _device, const char* Brand)
{
	Device.IMEI = new char[strlen(IMEI)];
	Device.IMSI = new char[16];
	Device.GUID = new byte[16];
	Device.MAC = new byte[6];
	Device._device = new char[strlen(_device)];
	Device.Brand = new char[strlen(Brand)];
	memcpy(Device.IMEI, IMEI, strlen(IMEI) + 1);
	memcpy(Device.IMSI, IMSI, 16);
	memcpy(Device.GUID, GUID, 16);
	memcpy(Device.MAC, MAC, 6);
	memcpy(Device._device, _device, strlen(_device) + 1);
	memcpy(Device.Brand, Brand, strlen(Brand) + 1);
	memcpy(QQ.Version + 1, IMSI, 15);
	Device.os_type = "android";
	Device.os_version = "10.1.0";
	Device._network_type = 2;
	Device._apn = "CMCC";
	Device.NetworkName = "IMT-2020";
	Device.WiFiName = "0x";
	Device.BSSID = "a";//不知道什么东西
	Device.QIMEI = "a";//算法不明
	QQ.SsoSeq = Utils::GetRandom(1231123, 99999999);
	QQ.MsgCookie = Utils::GetRandomBin(4);

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	HandleThreads.init(sysInfo.dwNumberOfProcessors * 2);
	HandleThreads.start();
}

bool Android::Fun_Connect()
{
	wchar_t* IP = nullptr;
	TCP.DomainGetIP(L"msfwifi.3g.qq.com", IP);
	if (!TCP.Connect(Iconv::Unicode2Ansi(IP), 8080)) {
		delete[] IP;
		return false;
	};
	delete[] IP;
	return true;
}

void Android::Fun_Send(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer)
{
	::Pack Pack(XBin::Bin2Int(Buffer) + 100, true);
	::Pack _Pack(XBin::Bin2Int(Buffer) + 100, true);
	Pack.SetInt(PacketType);
	Pack.SetByte(EncodeType);
	switch (PacketType)
	{
	case 10:
		if (EncodeType == 1)
		{
			Pack.SetInt(68);
			Pack.SetBin(QQ.Token.A2, 64);
		}
		else
		{
			Pack.SetInt(4);
		}
		break;
	case 11:
		Pack.SetInt(QQ.SsoSeq);
		break;
	}
	Pack.SetByte(0);
	Pack.SetInt(strlen(QQ.QQ_Str) + 4);
	Pack.SetStr(QQ.QQ_Str);
	switch (PacketType)
	{
	case 10:
		_Pack.SetInt(QQ.SsoSeq);
		_Pack.SetInt(QQ_APPID);
		_Pack.SetInt(QQ_APPID);
		_Pack.SetBin((byte*)"\1\0\0\0\0\0\0\0\0\0\0\0", 12);
		if (EncodeType == 1)
		{
			_Pack.SetInt(76);
			_Pack.SetBin(QQ.Token.TGT, 72);
		}
		else
		{
			_Pack.SetInt(4);
		}
		_Pack.SetInt(strlen(ServiceCmd) + 4);
		_Pack.SetStr(ServiceCmd);
		_Pack.SetInt(8); //MsgCookie len + 4
		_Pack.SetBin(QQ.MsgCookie, 4);
		_Pack.SetInt(strlen(Device.IMEI) + 4); //IMEI len + 4
		_Pack.SetStr(Device.IMEI);
		_Pack.SetInt(4);
		_Pack.SetShort(34); //Version len + 2
		_Pack.SetStr(QQ.Version);
		_Pack.SetInt(4);
		break;
	case 11:
		_Pack.SetInt(strlen(ServiceCmd) + 4);
		_Pack.SetStr(ServiceCmd);
		_Pack.SetInt(8);
		_Pack.SetBin(QQ.MsgCookie, 4);
		_Pack.SetInt(4);
		break;
	}
	_Pack.SetLength();
	_Pack.SetBin_(_Pack.GetAll_(false));
	_Pack.SetBin_(Buffer);
	{
		byte* bin;
		uint bin_len = _Pack.GetAll(bin);
		switch (EncodeType)
		{
		case 0:
			Pack.SetBin(bin, bin_len);
			break;
		case 1:
		{
			std::vector<byte> data;
			Tea::encrypt(QQ.Token.D2Key, bin, bin_len, data);
			Pack.SetBin(&data);
		}
		break;
		case 2:
		{
			std::vector<byte> data;
			Tea::encrypt((byte*)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", bin, bin_len, data);
			Pack.SetBin(&data);
		}
		break;
		}
		delete[] bin;
	}
	Pack.SetLength();
	TCP.Send(Pack.GetAll());
	delete[] Pack.GetAll();
}

/// <summary>
/// 
/// </summary>
/// <param name="PacketType"></param>
/// <param name="EncodeType"></param>
/// <param name="ServiceCmd"></param>
/// <param name="Buffer">会自动销毁</param>
/// <returns>会自动销毁</returns>
LPBYTE Android::Fun_Send_Sync(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer)
{
	::Pack Pack(XBin::Bin2Int(Buffer) + 100, true);
	::Pack _Pack(XBin::Bin2Int(Buffer) + 100, true);
	int SsoSeq = QQ.SsoSeq.fetch_add(1);
	Pack.SetInt(PacketType);
	Pack.SetByte(EncodeType);
	switch (PacketType)
	{
	case 10:
		if (EncodeType == 1)
		{
			Pack.SetInt(68);
			Pack.SetBin(QQ.Token.A2, 64);
		}
		else
		{
			Pack.SetInt(4);
		}
		break;
	case 11:
		Pack.SetInt(SsoSeq);
		break;
	}
	Pack.SetByte(0);
	Pack.SetInt(strlen(QQ.QQ_Str) + 4);
	Pack.SetStr(QQ.QQ_Str);
	switch (PacketType)
	{
	case 10:
		_Pack.SetInt(SsoSeq);
		_Pack.SetInt(QQ_APPID);
		_Pack.SetInt(QQ_APPID);
		_Pack.SetBin((byte*)"\1\0\0\0\0\0\0\0\0\0\0\0", 12);
		if (EncodeType == 1)
		{
			_Pack.SetInt(76);
			_Pack.SetBin(QQ.Token.TGT, 72);
		}
		else
		{
			_Pack.SetInt(4);
		}
		_Pack.SetInt(strlen(ServiceCmd) + 4);
		_Pack.SetStr(ServiceCmd);
		_Pack.SetInt(8); //MsgCookie len + 4
		_Pack.SetBin(QQ.MsgCookie, 4);
		_Pack.SetInt(strlen(Device.IMEI) + 4); //IMEI len + 4
		_Pack.SetStr(Device.IMEI);
		_Pack.SetInt(4);
		_Pack.SetShort(34); //Version len + 2
		_Pack.SetStr(QQ.Version);
		_Pack.SetInt(4);
		break;
	case 11:
		_Pack.SetInt(strlen(ServiceCmd) + 4);
		_Pack.SetStr(ServiceCmd);
		_Pack.SetInt(8);
		_Pack.SetBin(QQ.MsgCookie, 4);
		_Pack.SetInt(4);
		break;
	}
	_Pack.SetLength();
	_Pack.SetBin_(_Pack.GetAll_(false));
	_Pack.SetBin_(Buffer);
	{
		byte* bin;
		uint bin_len = _Pack.GetAll(bin);
		switch (EncodeType)
		{
		case 0:
			Pack.SetBin(bin, bin_len);
			break;
		case 1:
		{
			std::vector<byte> data;
			Tea::encrypt(QQ.Token.D2Key, bin, bin_len, data);
			Pack.SetBin(&data);
		}
		break;
		case 2:
		{
			std::vector<byte> data;
			Tea::encrypt((byte*)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", bin, bin_len, data);
			Pack.SetBin(&data);
		}
		break;
		}
		delete[] bin;
	}
	Pack.SetLength();

	TCP.Send(Pack.GetAll());
	delete[] Pack.GetAll();

	std::mutex lock;
	std::unique_lock<std::mutex> ulock(lock);
	SendList[SsoSeq & 0x3F].cv.wait(ulock);
	return SendList[SsoSeq & 0x3F].BodyBin;
}

void Android::Fun_Msg_Loop()
{
	while (QQ.Status != 21)
	{
		LPBYTE bin = TCP.Receive();
		if (bin != nullptr)
		{
			HandleThreads.exec(std::bind(&Android::Fun_Receice, this, bin), bin);
		}
	}
}

void Android::Fun_Receice(const LPBYTE bin)
{
	::UnPack UnPack(bin);
	const uint PacketType = UnPack.GetInt();
	const byte EncodeType = UnPack.GetByte();
	uint CompressType;
	UnPack.GetByte();
	UnPack.GetBin(UnPack.GetInt() - 4);

	std::vector<byte> buffer;
	switch (EncodeType)
	{
	case 0:
		UnPack.Reset(UnPack.GetCurrentPoint(), UnPack.GetLeftLength());
		break;
	case 1:
		if (!Tea::decrypt(QQ.Token.D2Key, UnPack.GetCurrentPoint(), UnPack.GetLeftLength(), buffer)) return;
		UnPack.Reset(&buffer);
		break;
	case 2:
		if (!Tea::decrypt((byte*)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", UnPack.GetCurrentPoint(), UnPack.GetLeftLength(), buffer)) return;
		UnPack.Reset(&buffer);
		break;
	default:
		throw "unknown EncodeType";
		delete[] bin;
		return;
	}

	LPBYTE HeadBin = nullptr, BodyBin = nullptr;
	HeadBin = UnPack.GetBin();
	BodyBin = UnPack.GetBin();
	UnPack.Reset(HeadBin);
	int sso_seq;
	char* ServiceCmd;
	switch (PacketType)
	{
		uint len;
	case 10:
		sso_seq = UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetBin();
		len = UnPack.GetInt();
		ServiceCmd = new char[len - 3];
		ServiceCmd[len - 4] = '\0';
		memcpy(ServiceCmd, UnPack.GetStr(len - 4), len - 4);
		UnPack.GetBin();
		CompressType = UnPack.GetInt();
		break;
	case 11:
		sso_seq = UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetBin();
		len = UnPack.GetInt();
		ServiceCmd = new char[len - 3];
		ServiceCmd[len - 4] = '\0';
		memcpy(ServiceCmd, UnPack.GetStr(len - 4), len - 4);
		UnPack.GetBin();
		CompressType = UnPack.GetInt();
		break;
	default:
		throw "unknown PacketType";
		break;
	}

	if (ServiceCmd != NULL)
	{
		if (strlen(ServiceCmd) == 0) {
			delete[] ServiceCmd;
			throw "ServiceCmd is empty";
			return;
		}
	}

	switch (CompressType)
	{
	case 0:
		break;
	case 1:
		BodyBin = Utils::ZlibUnCompress(BodyBin);
		break;
	default:
		throw "unknown CompressType";
		break;
	}

	Log::AddLog(Log::LogType::__DEBUG, Log::MsgType::OTHER, L"serviceCmd", Iconv::Ansi2Unicode(ServiceCmd));

	if (sso_seq > 0)
	{
		SendList[sso_seq & 0x3F].BodyBin = BodyBin;
		SendList[sso_seq & 0x3F].cv.notify_one();
		Sleep(60000);
	}
	else
	{
		Fun_Handle(ServiceCmd, BodyBin, sso_seq);
	}
	delete[] ServiceCmd;
	delete[] bin;
	if (CompressType) delete[] BodyBin;
}

void Android::Fun_Handle(char* serviceCmd, const LPBYTE BodyBin, const uint sso_seq)
{
	char* buf;
	char* first = strtok_s(serviceCmd, ".", &buf);
	char* second = strtok_s(NULL, ".", &buf);
	if (!strcmp(first, "OnlinePush"))
	{
		if (!strcmp(second, "PbPushGroupMsg")) Un_Pack_OnlinePush_PbPushGroupMsg(BodyBin, sso_seq);
		if (!strcmp(second, "PbC2CMsgSync")) Un_Pack_OnlinePush_PbC2CMsgSync(BodyBin, sso_seq);
		if (!strcmp(second, "ReqPush")) Un_Pack_OnlinePush_ReqPush(BodyBin, sso_seq);
		if (!strcmp(second, "PbPushTransMsg")) Un_Pack_OnlinePush_PbPushTransMsg(BodyBin, sso_seq);
	}
	if (!strcmp(first, "MessageSvc"))
	{
		if (!strcmp(second, "PushNotify")) Un_Pack_MessageSvc_PushNotify(BodyBin, sso_seq);
		if (!strcmp(second, "PushForceOffline")) Un_Pack_MessageSvc_PushForceOffline(BodyBin, sso_seq);
	}
	if (!strcmp(first, "StatSvc"))
	{
		if (!strcmp(second, "SvcReqMSFLoginNotify")) Un_Pack_StatSvc_SvcReqMSFLoginNotify(BodyBin, sso_seq);
	}
	if (!strcmp(first, "ConfigPushSvc"))
	{
		if (!strcmp(second, "PushReq")) Un_Pack_ConfigPushSvc_PushReq(BodyBin, sso_seq);
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="iVersion"></param>
/// <param name="sServantName"></param>
/// <param name="sFuncName"></param>
/// <param name="sBuffer">会自动销毁</param>
/// <param name="Bufferlen"></param>
/// <returns></returns>
LPBYTE Android::Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char* sServantName, const char* sFuncName, byte* sBuffer, uint Bufferlen)
{
	Jce Jce(true);
	Jce.Write(iVersion, 1);
	Jce.Write(0, 2);
	Jce.Write(0, 3);
	Jce.Write(iRequestId, 4);
	Jce.Write(sServantName, 5);
	Jce.Write(sFuncName, 6);
	Jce.Write(sBuffer, Bufferlen, 7);
	Jce.Write(0, 8);
	std::vector<JceStruct::Map<const char*, const char*>> a;
	Jce.Write(&a, 9);
	Jce.Write(&a, 10);
	delete[] sBuffer;
	return Jce.GetAll();
}

/// <summary>
/// wtlogin用
/// </summary>
/// <param name="Buffer">会自动销毁</param>
/// <param name="BufferLen"></param>
/// <param name="emp"></param>
/// <returns></returns>
LPBYTE Android::Make_Body_PC(byte* Buffer, const uint BufferLen, const bool emp)
{
	::Pack Pack(BufferLen + 100);
	Pack.SetBin((byte*)"\x1f\x41", 2);
	Pack.SetBin((byte*)"\x08\x10", 2);
	Pack.SetShort(1);
	Pack.SetInt(QQ.QQ);
	if (emp)
	{
		Pack.SetBin((byte*)"\3\x45\0\0\0\0\2\0\0\0\0\0\0", 13);
		Pack.SetInt(48);
		Pack.SetBin(QQ.Token.wtSessionTicket, 48);
	}
	else
	{
		Pack.SetBin((byte*)"\3\x87\0\0\0\0\2\0\0\0\0\0\0\0\0", 15);
		Pack.SetBin((byte*)"\1\1", 2);
		Pack.SetBin(QQ.Login->RandKey, 16);
		Pack.SetBin((byte*)"\1\2", 2);

		Pack.SetShort(25);
		Pack.SetBin(QQ.Login->ECDH.pubkey, 25);
	}
	{
		std::vector<byte> data;
		if (emp)
		{
			Tea::encrypt(QQ.Token.wtSessionTicketKey, Buffer, BufferLen, data);
		}
		else
		{
			byte key[16] = { 0 };
			memcpy(key, Utils::MD5(QQ.Login->ECDH.sharekey, 24), 16);
			Tea::encrypt(key, Buffer, BufferLen, data);
		}
		delete[] Buffer;
		Pack.SetBin(&data);
	}
	{
		byte* bin;
		uint bin_len = Pack.GetAll_(bin, true);
		Pack.SetByte(2);
		Pack.SetShort(bin_len + 4);
		Pack.SetBin_(bin, bin_len);
		Pack.SetByte(3);
	}
	Pack.SetLength();
	return Pack.GetAll();
}

void Android::wtlogin_login()
{
	::Pack Pack(1300);
	time_t Time = std::time(0);
	const char* domainList[] = { "openmobile.qq.com", "docs.qq.com","connect.qq.com","qzone.qq.com","vip.qq.com","qun.qq.com","game.qq.com","qqweb.qq.com","ti.qq.com","office.qq.com","mail.qq.com","qzone.com","mma.qq.com","tenpay.com" };
	Pack.SetBin((byte*)"\x00\x09", 2);
	Pack.SetShort(24);
	Pack.Skip(Tlv::Tlv018(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.QQ));
	Pack.Skip(Tlv::Tlv001(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.QQ, Time));
	Pack.Skip(Tlv::Tlv106(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.QQ, QQ.QQ_Str, QQ.Token.md5, QQ.Token.md52, QQ.Token.TGTkey, Device.GUID, Time, QQ_APPID, false));
	Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv100(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_APPID, true));
	Pack.Skip(Tlv::Tlv107(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv142(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_APKID));
	Pack.Skip(Tlv::Tlv144(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Token.TGTkey, Device.IMEI, Device.os_type, Device.os_version, Device._network_type, Device._apn, Device.NetworkName, Device._device, Device.Brand, Device.GUID));
	Pack.Skip(Tlv::Tlv145(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.GUID));
	Pack.Skip(Tlv::Tlv147(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_VERSION, QQ_ASIG));
	Pack.Skip(Tlv::Tlv154(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.SsoSeq));
	Pack.Skip(Tlv::Tlv141(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.NetworkName, Device._apn));
	Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv511(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), domainList, 14));
	Pack.Skip(Tlv::Tlv187(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv188(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv194(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv191(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), 0x82));
	Pack.Skip(Tlv::Tlv202(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.BSSID, Device.WiFiName));
	Pack.Skip(Tlv::Tlv177(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_BUILDTIME, QQ_SDK_VERSION));
	Pack.Skip(Tlv::Tlv516(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv521(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv525(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv544(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_APKID, QQ_ASIG));
	Un_Pack_wtlogin_login(Fun_Send_Sync(10, 2, "wtlogin.login", Make_Body_PC(Pack.GetAll(), Pack.Length(), false)));
}

void Android::wtlogin_login_Send_Sms()
{
	::Pack Pack(300);
	Pack.SetBin((byte*)"\x00\x08", 2);
	Pack.SetShort(6);
	Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Login->VieryToken2));
	Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv174(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Login->SmsToken));
	Pack.Skip(Tlv::Tlv17A(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv197(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Un_Pack_wtlogin_login(Fun_Send_Sync(10, 2, "wtlogin.login", Make_Body_PC(Pack.GetAll(), Pack.Length(), false)));
}

void Android::wtlogin_login_Viery_Ticket(const char* Ticket)
{
	::Pack Pack(900);
	Pack.SetBin((byte*)"\x00\x02", 2);
	Pack.SetShort(5);
	Pack.Skip(Tlv::Tlv193(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Ticket));
	Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Login->VieryToken2));
	Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv547(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Login->ClientPow));
	Un_Pack_wtlogin_login(Fun_Send_Sync(10, 2, "wtlogin.login", Make_Body_PC(Pack.GetAll(), Pack.Length(), false)));
}

void Android::wtlogin_login_Viery_Sms(const char* SmsCode)
{
	::Pack Pack(300);
	Pack.SetBin((byte*)"\x00\x07", 2);
	Pack.SetShort(7);
	Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Login->VieryToken2));
	Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv174(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Login->SmsToken));
	Pack.Skip(Tlv::Tlv17C(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), SmsCode));
	Pack.Skip(Tlv::Tlv401(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.GUID, QQ.Login->token_402));
	Pack.Skip(Tlv::Tlv198(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Un_Pack_wtlogin_login(Fun_Send_Sync(10, 2, "wtlogin.login", Make_Body_PC(Pack.GetAll(), Pack.Length(), false)));
}

void Android::wtlogin_login_Viery_204()
{
	::Pack Pack(300);
	Pack.SetBin((byte*)"\x00\x14", 2);
	Pack.SetShort(6);
	Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv104(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Login->VieryToken2));
	Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv401(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.GUID, QQ.Login->token_402));
	//Pack.Skip(Tlv::Tlv402(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	//Pack.Skip(Tlv::Tlv403(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Un_Pack_wtlogin_login(Fun_Send_Sync(10, 2, "wtlogin.login", Make_Body_PC(Pack.GetAll(), Pack.Length(), false)));
}

void Android::wtlogin_exchange_emp()
{
	::Pack Pack(1400);
	time_t Time = std::time(0);
	const char* domainList[] = { "openmobile.qq.com", "docs.qq.com","connect.qq.com","qzone.qq.com","vip.qq.com","qun.qq.com","game.qq.com","qqweb.qq.com","ti.qq.com","office.qq.com","mail.qq.com","qzone.com","mma.qq.com","tenpay.com" };
	Pack.SetBin((byte*)"\x00\x0f", 2);
	Pack.SetShort(25);
	Pack.Skip(Tlv::Tlv018(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.QQ));
	Pack.Skip(Tlv::Tlv001(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.QQ, Time));
	Pack.Skip(Tlv::Tlv106(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.QQ, QQ.QQ_Str, QQ.Token.md5, QQ.Token.md52, QQ.Token.TGTkey, Device.GUID, Time, QQ_APPID, true));
	Pack.Skip(Tlv::Tlv116(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv100(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_APPID, true));
	Pack.Skip(Tlv::Tlv107(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv108(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Token.ksid));
	Pack.Skip(Tlv::Tlv144(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Token.TGTkey, Device.IMEI, Device.os_type, Device.os_version, Device._network_type, Device._apn, Device.NetworkName, Device._device, Device.Brand, Device.GUID));
	Pack.Skip(Tlv::Tlv142(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_APKID));
	Pack.Skip(Tlv::Tlv145(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.GUID));
	Pack.Skip(Tlv::Tlv16A(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.Token.token_16A));
	Pack.Skip(Tlv::Tlv154(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.SsoSeq));
	Pack.Skip(Tlv::Tlv141(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.NetworkName, Device._apn));
	Pack.Skip(Tlv::Tlv008(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv511(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), domainList, 14));
	Pack.Skip(Tlv::Tlv147(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_VERSION, QQ_ASIG));
	Pack.Skip(Tlv::Tlv177(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Time - 238, QQ_SDK_VERSION));
	//Pack.Skip(Tlv::Tlv400(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ.QQ, Device.GUID, Time, QQ.Login->token_403));
	Pack.Skip(Tlv::Tlv187(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv188(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv194(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv202(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.BSSID, Device.WiFiName));
	Pack.Skip(Tlv::Tlv516(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv521(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv525(Pack.GetCurrentPoint(), Pack.GetLeftSpace()));
	Pack.Skip(Tlv::Tlv544(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), QQ_APKID, QQ_ASIG));
	//Pack.Skip(Tlv::Tlv545(Pack.GetCurrentPoint(), Pack.GetLeftSpace(), Device.QIMEI));
	::UnPack UnPack(Fun_Send_Sync(10, 2, "wtlogin.exchange_emp", Make_Body_PC(Pack.GetAll(), Pack.Length(), true)));
	UnPack.GetByte();
	const uint len = UnPack.GetShort() - 1 - 2 - 2 - 2 - 2 - 4 - 2 - 1 - 1;
	UnPack.GetShort();
	UnPack.GetShort();
	UnPack.GetShort();
	UnPack.GetInt();
	UnPack.GetShort();
	const byte Result = UnPack.GetByte();

	const byte* Buffer = nullptr;
	Buffer = UnPack.GetBin(len);
	std::vector<byte> data;
	Tea::decrypt(QQ.Token.wtSessionTicketKey, Buffer, len, data);
	UnPack.Reset(&data);
	UnPack.GetShort();
	UnPack.GetByte();
	unsigned short Count = UnPack.GetShort();
	for (size_t i = 0; i < Count; i++)
	{
		unsigned short cmd = UnPack.GetShort();
		unsigned short binlen = UnPack.GetShort();
		Un_Tlv_Get(cmd, UnPack.GetBin(binlen), binlen);
	}
	switch (Result)
	{
	case 0:
		QQ.Login->state = LOGIN_SUCCESS;
		break;
	default:
		QQ.Login->state = Result;
		throw "Unknown login result";
		break;
	}
}

void Android::StatSvc_Register(const byte state)
{
	Jce Jce;
	Jce.Write(QQ.QQ, 0);//lUin
	Jce.Write(state == 21 ? 0 : 7, 1);//lBid
	Jce.Write(0, 2);//cConnType
	Jce.Write("", 3);//sOther
	Jce.Write(state == NULL ? QQ.Status : state, 4);//iStatus
	Jce.Write(state == NULL, 5);//bOnlinePush
	Jce.Write(false, 6);//bIsOnline
	Jce.Write(false, 7);//bIsShowOnline
	Jce.Write(false, 8);//bKikPC''''
	Jce.Write(false, 9);//bKikWeak
	Jce.Write(517, 10);//timeStamp
	Jce.Write(22, 11);//iOSVersion
	Jce.Write(1, 12);//cNetType
	Jce.Write("", 13);//sBuildVer
	Jce.Write(false, 14);//bRegType
	//vecDevParam
	Jce.Write(Device.GUID, 16, 16);//vecGuid
	Jce.Write(2052, 17);//iLocaleID
	Jce.Write(false, 18);//bSlientPush
	Jce.Write(Device._device, 19);//strDevName
	Jce.Write(Device._device, 20);//strDevType
	Jce.Write(Device.os_version, 21);//strOSVer
	Jce.Write(true, 22);//bOpenPush
	Jce.Write(13, 23);//iLargeSeq
	Jce.Write(0, 24);//iLastWatchStartTime
	//vecBindUin
	Jce.Write(0, 26);//uOldSSOIp
	Jce.Write(0, 27);//uNewSSOIp
	Jce.Write("", 28);//sChannelNo
	Jce.Write(0, 29);//lCpId
	Jce.Write(Device.Brand, 30);//strVendorName
	Jce.Write("", 31);//strVendorOSName
	Jce.Write("", 32);//strIOSIdfa
	Jce.Write((byte*)"\x0A\x08\x08\x2E\x10\xEF\xBF\x8B\xF4\x05\x0A\x05\x08\x9B\x02\x10\x00", 17, 33);//bytes_0x769_reqbody
	Jce.Write(false, 34);//bIsSetStatus
	//vecServerBuf
	Jce.Write(false, 36);//bSetMute
	Jce.Write(0, 38);//uExtOnlineStatus
	Jce.Write(0, 39);//iBatteryStatus

	Jce.Write(&Jce, 0);
	LPBYTE bin = Jce.GetAll_();

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "SvcReqRegister", bin } };
	Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = Jce.GetAll(bin);

	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(Fun_Send_Sync(10, 1, "StatSvc.register", Make_Body_Request_Packet(3, 0, "PushService", "SvcReqRegister", bin, len)), sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, std::vector<JceStruct::Map<char*, LPBYTE>>>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		for (size_t j = 0; j < Map[i].Value.size(); j++)
		{
			UnJce.Reset(Map[i].Value[j].Value);
			UnJce.Read(UnJce, 0);

			delete[] Map[i].Value[j].Key;
			delete[] Map[i].Value[j].Value;
		}

		delete[] Map[i].Key;
	}
	delete[] sBuffer;
}

void Android::StatSvc_SetStatusFromClient(const byte state)
{
	Jce Jce;
	Jce.Write(QQ.QQ, 0);//lUin
	Jce.Write(state == 21 ? 0 : 7, 1);//lBid
	Jce.Write(0, 2);//cConnType
	Jce.Write("", 3);//sOther
	Jce.Write(state == NULL ? QQ.Status : state, 4);//iStatus
	Jce.Write(state == NULL, 5);//bOnlinePush
	Jce.Write(0, 6);//bIsOnline
	Jce.Write(0, 7);//bIsShowOnline
	Jce.Write(false, 8);//bKikPC''''
	Jce.Write(false, 9);//bKikWeak
	Jce.Write(std::time(0), 10);//timeStamp
	Jce.Write(23, 11);//iOSVersion
	Jce.Write(1, 12);//cNetType
	Jce.Write("", 13);//sBuildVer
	Jce.Write(false, 14);//bRegType
	//vecDevParam
	Jce.Write(Device.GUID, 16, 16);//vecGuid
	Jce.Write(2052, 17);//iLocaleID
	Jce.Write(false, 18);//bSlientPush
	Jce.Write(Device._device, 19);//strDevName
	Jce.Write(Device._device, 20);//strDevType
	Jce.Write(Device.os_version, 21);//strOSVer
	Jce.Write(true, 22);//bOpenPush
	Jce.Write(0, 23);//iLargeSeq
	Jce.Write(0, 24);//iLastWatchStartTime
	//vecBindUin
	Jce.Write(0, 26);//uOldSSOIp
	Jce.Write(0, 27);//uNewSSOIp
	Jce.Write("", 28);//sChannelNo
	Jce.Write(0, 29);//lCpId
	Jce.Write(Device.Brand, 30);//strVendorName
	Jce.Write("", 31);//strVendorOSName
	Jce.Write("", 32);//strIOSIdfa
	Jce.Write((byte*)"\x0A\x08\x08\x2E\x10\xEF\xBF\x8B\xF4\x05\x0A\x05\x08\x9B\x02\x10\x00", 17, 33);//bytes_0x769_reqbody
	Jce.Write(true, 34);//bIsSetStatus
	//vecServerBuf
	Jce.Write(0, 36);//bSetMute
	Jce.Write(0, 38);//uExtOnlineStatus
	Jce.Write(10000, 39);//iBatteryStatus

	Jce.Write(&Jce, 0);
	LPBYTE bin = Jce.GetAll_();

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "SvcReqRegister", bin } };
	Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = Jce.GetAll(bin);

	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(Fun_Send_Sync(10, 1, "StatSvc.SetStatusFromClient", Make_Body_Request_Packet(3, 0, "PushService", "SvcReqRegister", bin, len)), sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, std::vector<JceStruct::Map<char*, LPBYTE>>>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		for (size_t j = 0; j < Map[i].Value.size(); j++)
		{
			UnJce.Reset(Map[i].Value[j].Value);
			UnJce.Read(UnJce, 0);

			delete[] Map[i].Value[j].Key;
			delete[] Map[i].Value[j].Value;
		}

		delete[] Map[i].Key;
	}
	delete[] sBuffer;

}

void Android::friendlist_getFriendGroupList(const int StartIndex)
{
	Jce Jce;
	Jce.Write(3, 0);
	Jce.Write(1, 1);
	Jce.Write(QQ.QQ, 2);
	Jce.Write(StartIndex, 3);  //开始数
	Jce.Write(20, 4);  //获取个数
	Jce.Write(0, 5);
	Jce.Write(1, 6);
	Jce.Write(0, 7);
	Jce.Write(0, 8);
	Jce.Write(0, 9);
	Jce.Write(1, 10);
	Jce.Write(5, 11);


	Jce.Write(&Jce, 0);
	LPBYTE bin = Jce.GetAll_();

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "FL", bin } };
	Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = Jce.GetAll_(bin);

	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(Fun_Send_Sync(11, 1, "friendlist.getFriendGroupList", Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "GetFriendListReq", bin, len)), sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, LPBYTE>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		UnJce.Reset(Map[i].Value);
		UnJce.Read(UnJce, 0);

		int startIndex, totoal_friend_count, get_count = 0;
		UnJce.Read(startIndex, 3);
		UnJce.Read(totoal_friend_count, 5);
		UnJce.Read(get_count, 6);
		if (startIndex + get_count < totoal_friend_count) friendlist_getFriendGroupList(startIndex + get_count);
		if (startIndex == 0) QQ.FriendList.resize(totoal_friend_count);

		std::vector<::UnJce> Friends;
		UnJce.Read(Friends, 7);
		for (size_t j = 0; j < Friends.size(); j++)
		{
			Friends[j].Read((int&)QQ.FriendList[startIndex + j].QQ, 0);
			Friends[j].Read(QQ.FriendList[startIndex + j].Remark, 3);
			Friends[j].Read(QQ.FriendList[startIndex + j].status, 5);
			Friends[j].Read(QQ.FriendList[startIndex + j].Nick, 14);
		}

		delete[] Map[i].Key;
		delete[] Map[i].Value;
	}
	delete[] sBuffer;
}

void Android::friendlist_GetTroopListReqV2()
{
	Jce Jce;
	Jce.Write(QQ.QQ, 0);
	Jce.Write(0, 1);
	Jce.Write(1, 4);
	Jce.Write(5, 5);

	Jce.Write(&Jce, 0);
	LPBYTE bin = Jce.GetAll_();

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "GetTroopListReqV2Simplify", bin } };
	Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = Jce.GetAll_(bin);

	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(Fun_Send_Sync(11, 1, "friendlist.GetTroopListReqV2", Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "GetTroopListReqV2Simplify", bin, len)), sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, LPBYTE>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		UnJce.Reset(Map[i].Value);
		UnJce.Read(UnJce, 0);
		//UnJce.Read(totoal_group_count, 1);

		std::vector<::UnJce> Groups;
		UnJce.Read(Groups, 5);
		QQ.GroupList.resize(Groups.size());

		for (size_t j = 0; j < Groups.size(); j++)
		{
			Groups[j].Read((int&)QQ.GroupList[j].GroupCode, 1);
			Groups[j].Read(QQ.GroupList[j].GroupName, 4);
			Groups[j].Read(QQ.GroupList[j].MemberCount, 19);
			Groups[j].Read((int&)QQ.GroupList[j].MasterQQ, 23);
		}

		delete[] Map[i].Key;
		delete[] Map[i].Value;
	}
	delete[] sBuffer;
}

void Android::friendlist_getTroopMemberList(const uint Group)
{
	Jce Jce;
	Jce.Write(QQ.QQ, 0);
	Jce.Write(Group, 1);
	Jce.Write(0, 2);
	Jce.Write(Group, 3);
	Jce.Write(2, 4);
	Jce.Write(1, 5);
	Jce.Write(0, 6);
	Jce.Write(1, 7);

	Jce.Write(&Jce, 0);
	LPBYTE bin = Jce.GetAll_();

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "GTML", bin } };
	Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = Jce.GetAll(bin);

	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(Fun_Send_Sync(11, 1, "friendlist.getTroopMemberList", Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "GetFriendListReq", bin, len)), sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, LPBYTE>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		UnJce.Reset(Map[i].Value);
		UnJce.Read(UnJce, 0);

		std::vector<::UnJce> Groups;
		UnJce.Read(Groups, 3);
		QQ.GroupList.resize(Groups.size());

		for (size_t j = 0; j < Groups.size(); j++)
		{
			/*
			Groups[j].Read((int&)QQ.GroupList[j].GroupCode, 1);
			Groups[j].Read(QQ.GroupList[j].GroupName, 4);
			Groups[j].Read(QQ.GroupList[j].MemberCount, 19);
			Groups[j].Read((int&)QQ.GroupList[j].MasterQQ, 23);
			*/
		}

		delete[] Map[i].Key;
		delete[] Map[i].Value;
	}
	delete[] sBuffer;
}

bool Android::friendlist_ModifyGroupCardReq(const uint Group, const uint QQ, const char* NewGroupCard)
{
	Jce Jce;
	Jce.Write(QQ, 0);
	Jce.Write(1, 1);
	Jce.Write(NewGroupCard, 2);
	Jce.Write(255, 3);
	Jce.Write("", 4);
	Jce.Write("", 5);
	Jce.Write("", 6);

	const std::vector<::Jce*> list{ &Jce };

	::Jce Jce_;
	Jce_.Write(0, 0);
	Jce_.Write(Group, 1);
	Jce_.Write(0, 2);
	Jce_.Write(&list, 3);

	Jce.Write(&Jce_, 0);
	LPBYTE bin = Jce.GetAll_(false);

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "MGCREQ", bin } };
	Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = Jce.GetAll(bin);
	Fun_Send_Sync(11, 1, "friendlist.ModifyGroupCardReq", Make_Body_Request_Packet(3, 0, "mqq.IMService.FriendListServiceServantObj", "ModifyGroupCardReq", bin, len));
	//Todo
	return true;
}

void Android::SQQzoneSvc_getUndealCount()
{
	Jce Jce;
	/*
	SQQzoneSvc.getUndealCount
	02 08 76 38 1B 12 00 0F 42 5B 23 00 00 00 00 B9 F8 23 A2 36 1A 56 31 5F 41 4E 44 5F 53 51 5F 38 2E 34 2E 31 5F 31 34 34 32 5F 59 59 42 5F 44 46 1E 51 7A 6F 6E 65 4E 65 77 53 65 72 76 69 63 65 2E 67 65 74 55 6E 64 65 61 6C 43 6F 75 6E 74 56 F7 73 63 72 65 65 6E 5F 77 69 64 74 68 3D 39 30 30 26 73 63 72 65 65 6E 5F 68 65 69 67 68 74 3D 31 36 30 30 26 69 3D 38 36 33 30 36 34 30 31 30 34 38 34 33 35 32 26 69 6D 73 69 3D 34 36 30 30 37 31 32 38 38 31 31 33 39 39 35 26 6D 61 63 3D 44 30 3A 43 36 3A 33 37 3A 44 44 3A 38 42 3A 35 46 26 6D 3D 4D 49 20 39 26 6F 3D 35 2E 31 2E 31 26 61 3D 32 32 26 73 63 3D 31 26 73 64 3D 30 26 70 3D 39 30 30 2A 31 36 30 30 26 66 3D 58 69 61 6F 6D 69 26 6D 6D 3D 33 30 33 38 26 63 66 3D 32 34 30 37 26 63 63 3D 32 26 61 69 64 3D 66 38 30 31 34 36 34 66 63 62 64 38 38 34 39 30 26 71 69 6D 65 69 3D 38 36 36 31 37 34 35 37 31 35 36 38 30 35 30 26 73 68 61 72 70 50 3D 31 26 6E 3D 77 69 66 69 26 6C 6F 6E 67 69 74 75 64 65 3D 26 6C 61 74 69 74 75 64 65 3D 6A 00 40 1D 00 0C 28 00 01 00 01 1D 00 00 01 00 0B 7A 0C 1C 2C 3D 00 00 06 00 00 00 00 00 00 0B 8D 00 01 01 39 08 00 02 06 0E 67 65 74 55 6E 64 65 61 6C 43 6F 75 6E 74 18 00 01 06 20 4E 53 5F 55 4E 44 45 41 4C 5F 43 4F 55 4E 54 2E 6D 6F 62 69 6C 65 5F 63 6F 75 6E 74 5F 72 65 71 1D 00 01 00 DC 0A 0C 10 01 20 03 48 00 01 0C 1C 58 00 0B 01 03 EA 12 5F 2B D2 F3 00 21 12 5F 2B D3 D3 01 03 F0 12 5F 2B D2 F3 01 03 E9 12 5F 2B D2 F3 01 03 EF 12 5F 2B D2 F3 01 03 ED 12 5F 2A E6 40 00 23 12 5F 2B D2 F3 01 03 EC 12 5F 2A E6 6D 03 00 00 00 00 FF FF FF FF 12 5F 2B D3 D4 01 03 EB 12 5F 2A E6 40 01 03 F2 12 5F 2A E6 40 66 00 78 00 03 00 01 1A 0A 00 01 10 01 0B 19 00 01 0A 02 3D DA 31 58 16 00 26 00 0B 26 00 3C 46 00 56 00 66 00 7C 8C 0B 00 02 1A 0A 0C 10 02 0B 19 00 01 0A 0C 16 00 26 00 0B 26 00 3C 46 00 56 00 66 00 7C 8C 0B 01 03 EE 1A 0A 0C 1C 0B 19 00 01 0A 0C 16 00 26 00 0B 26 00 3C 46 00 56 00 66 00 7C 8C 0B 88 00 01 00 21 16 01 30 96 00 AC C8 0C 0B 06 07 68 6F 73 74 75 69 6E 18 00 01 06 05 69 6E 74 36 34 1D 00 00 09 03 00 00 00 00 B9 F8 23 A2 9D 00 01 00 A2 08 00 03 06 0B 62 75 73 69 43 6F 6D 70 43 74 6C 18 00 01 06 1B 51 4D 46 5F 50 52 4F 54 4F 43 41 4C 2E 51 6D 66 42 75 73 69 43 6F 6E 74 72 6F 6C 1D 00 00 08 0A 0C 11 01 39 20 01 0B 06 0F 77 6E 73 5F 73 64 6B 5F 76 65 72 73 69 6F 6E 18 00 01 06 05 69 6E 74 33 32 1D 00 00 02 00 01 06 0D 63 6F 6E 66 5F 69 6E 66 6F 5F 72 65 71 18 00 01 06 22 51 4D 46 5F 50 52 4F 54 4F 43 41 4C 2E 6D 6F 62 69 6C 65 5F 67 65 74 5F 63 6F 6E 66 69 67 5F 72 65 71 1D 00 00 0B 0A 02 00 0F 42 5B 10 66 26 00 0B AC BC
	[
	[0 2 ]141965339
	[1 2 ]1000027
	[2 3 ]3120047010
	[3 6 ]V1_AND_SQ_8.4.1_1442_YYB_D
	[4 6 ]QzoneNewService.getUndealCount
	[5 6 ]screen_width=900&screen_height=1600&i=863064010484352&imsi=460071288113995&mac=D0:C6:37:DD:8B:5F&m=MI 9&o=5.1.1&a=22&sc=1&sd=0&p=900*1600&f=Xiaomi&mm=3038&cf=2407&cc=2&aid=f801464fcbd88490&qimei=866174571568050&sharpP=1&n=wifi&longitude=&latitude=
	[6 10 ]
	  [0 0 ]64
	  [1 13 ]
	  [2 8 ]{
		  key :1 val :00
		  }

	[7 10 ]
	  [0 12 ]0
	  [1 12 ]0
	  [2 12 ]0
	  [3 13 ]00 00 00 00 00 00

	[8 13 ]08 00 02 06 0E 67 65 74 55 6E 64 65 61 6C 43 6F 75 6E 74 18 00 01 06 20 4E 53 5F 55 4E 44 45 41 4C 5F 43 4F 55 4E 54 2E 6D 6F 62 69 6C 65 5F 63 6F 75 6E 74 5F 72 65 71 1D 00 01 00 DC 0A 0C 10 01 20 03 48 00 01 0C 1C 58 00 0B 01 03 EA 12 5F 2B D2 F3 00 21 12 5F 2B D3 D3 01 03 F0 12 5F 2B D2 F3 01 03 E9 12 5F 2B D2 F3 01 03 EF 12 5F 2B D2 F3 01 03 ED 12 5F 2A E6 40 00 23 12 5F 2B D2 F3 01 03 EC 12 5F 2A E6 6D 03 00 00 00 00 FF FF FF FF 12 5F 2B D3 D4 01 03 EB 12 5F 2A E6 40 01 03 F2 12 5F 2A E6 40 66 00 78 00 03 00 01 1A 0A 00 01 10 01 0B 19 00 01 0A 02 3D DA 31 58 16 00 26 00 0B 26 00 3C 46 00 56 00 66 00 7C 8C 0B 00 02 1A 0A 0C 10 02 0B 19 00 01 0A 0C 16 00 26 00 0B 26 00 3C 46 00 56 00 66 00 7C 8C 0B 01 03 EE 1A 0A 0C 1C 0B 19 00 01 0A 0C 16 00 26 00 0B 26 00 3C 46 00 56 00 66 00 7C 8C 0B 88 00 01 00 21 16 01 30 96 00 AC C8 0C 0B 06 07 68 6F 73 74 75 69 6E 18 00 01 06 05 69 6E 74 36 34 1D 00 00 09 03 00 00 00 00 B9 F8 23 A2
	[9 13 ]08 00 03 06 0B 62 75 73 69 43 6F 6D 70 43 74 6C 18 00 01 06 1B 51 4D 46 5F 50 52 4F 54 4F 43 41 4C 2E 51 6D 66 42 75 73 69 43 6F 6E 74 72 6F 6C 1D 00 00 08 0A 0C 11 01 39 20 01 0B 06 0F 77 6E 73 5F 73 64 6B 5F 76 65 72 73 69 6F 6E 18 00 01 06 05 69 6E 74 33 32 1D 00 00 02 00 01 06 0D 63 6F 6E 66 5F 69 6E 66 6F 5F 72 65 71 18 00 01 06 22 51 4D 46 5F 50 52 4F 54 4F 43 41 4C 2E 6D 6F 62 69 6C 65 5F 67 65 74 5F 63 6F 6E 66 69 67 5F 72 65 71 1D 00 00 0B 0A 02 00 0F 42 5B 10 66 26 00 0B
	[10 12 ]0
	[11 12 ]0

	]
	*/
	Fun_Send_Sync(10, 1, "SQQzoneSvc.getUndealCount", Jce.GetAll());
}

void Android::OnlinePush_RespPush(const uint sso_seq, const LPBYTE protobuf, const int a)
{
	Jce Jce;
	Jce.Write(QQ.QQ, 0); //lFromUin
	Jce.Write(0, 1); //uMsgTime
	Jce.Write(24042, 2); //shMsgSeq
	Jce.Write(protobuf, 3); //vMsgCookies
	Jce.Write(0, 4); //wCmd
	Jce.Write(0, 5); //uMsgType
	Jce.Write(0, 6); //uAppId
	Jce.Write(0, 7); //lSendTime
	Jce.Write(0, 8); //ssoSeq
	Jce.Write(0, 9); //ssoIp
	Jce.Write(0, 10); //clientIp

	const std::vector<::Jce*> list{ &Jce };

	::Jce Jce_;
	Jce_.Write(QQ.QQ, 0);
	Jce_.Write(&list, 1);
	Jce_.Write(a, 2);//unknow
	Jce_.Write(0, 4);

	Jce.Write(&Jce_, 0);
	LPBYTE bin = Jce.GetAll_();

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "resp", bin } };
	Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = Jce.GetAll(bin);
	Fun_Send(11, 1, "OnlinePush.RespPush", Make_Body_Request_Packet(3, sso_seq, "OnlinePush", "SvcRespPushMsg", bin, len));
}

bool Android::VisitorSvc_ReqFavorite(const uint QQ, const int Times)
{
	Jce Jce, _Jce;
	Jce.Write(this->QQ.QQ, 0);
	Jce.Write(1, 1);
	Jce.Write(1265524299, 2);
	Jce.Write(1, 3);
	Jce.Write(0, 4);

	_Jce.Write(&Jce, 0);
	_Jce.Write(QQ, 1);
	_Jce.Write(0, 2);
	_Jce.Write(66, 2);
	_Jce.Write(Times, 2);

	_Jce.Write(&_Jce, 0);
	LPBYTE bin = _Jce.GetAll_();

	const std::vector<JceStruct::Map<const char*, const LPBYTE>> JceMap{ JceStruct::Map<const char*, const LPBYTE>{ "ReqFavorite", bin } };
	_Jce.Write(&JceMap, 0);
	delete[] bin;

	uint len = _Jce.GetAll(bin);

	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(Fun_Send_Sync(11, 1, "VisitorSvc.ReqFavorite", Make_Body_Request_Packet(3, 0, "VisitorSvc", "ReqFavorite", bin, len)), sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, std::vector<JceStruct::Map<char*, LPBYTE>>>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		for (size_t j = 0; j < Map[i].Value.size(); j++)
		{
			UnJce.Reset(Map[i].Value[j].Value);
			UnJce.Read(UnJce, 0);
			//Todo
			delete[] Map[i].Value[j].Key;
			delete[] Map[i].Value[j].Value;
		}

		delete[] Map[i].Key;
	}
	delete[] sBuffer;
	return true;
}

void Android::MessageSvc_PbGetMsg()
{
	ProtobufStruct::TreeNode Node12{ nullptr,nullptr,12,ProtobufStruct::ProtobufStructType::LENGTH, (void*)"\0\0\0\4" };
	ProtobufStruct::TreeNode Node9{ nullptr,&Node12,9,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node7{ nullptr,&Node9,7,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6{ nullptr,&Node7,6,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node5{ nullptr,&Node6,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)3 };
	ProtobufStruct::TreeNode Node4{ nullptr,&Node5,4,ProtobufStruct::ProtobufStructType::VARINT,(void*)20 };
	ProtobufStruct::TreeNode Node3{ nullptr,&Node4,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2_14{ nullptr,nullptr,14,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2_13{ &Node2_14,nullptr,13,ProtobufStruct::ProtobufStructType::VARINT,(void*)std::time(0) };
	ProtobufStruct::TreeNode Node2_12{ &Node2_13,nullptr,12,ProtobufStruct::ProtobufStructType::VARINT,(void*)41 };
	ProtobufStruct::TreeNode Node2_11{ &Node2_12,nullptr,11,ProtobufStruct::ProtobufStructType::VARINT,(void*)1885270429 };
	ProtobufStruct::TreeNode Node2_9{ &Node2_11,nullptr,9,ProtobufStruct::ProtobufStructType::VARINT,(void*)2346412847 };
	ProtobufStruct::TreeNode Node2_5{ &Node2_9,nullptr,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)562530569 };
	ProtobufStruct::TreeNode Node2_4{ &Node2_5,nullptr,4,ProtobufStruct::ProtobufStructType::VARINT,(void*)3414434724 };
	ProtobufStruct::TreeNode Node2_3{ &Node2_4,nullptr,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)1787282332 };
	ProtobufStruct::TreeNode Node2_2{ &Node2_3,nullptr,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)std::time(0) };
	ProtobufStruct::TreeNode Node2_1{ &Node2_2,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)std::time(0) };
	ProtobufStruct::TreeNode Node2{ &Node2_1,&Node3,2,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "MessageSvc.PbGetMsg", PB.Pack(&Node1)));

	QQ.SyncCookies = UnPB.GetBin(3);
	if (UnPB.GetVarint(4) == 1); //Todo
	while (UnPB.GetField() == 5)
	{
		UnPB.StepIn(5);
		UnPB.GetVarint(3);
		while (UnPB.GetField() == 4)
		{
			Event::PrivateMsg PrivateMsg;
			UnPB.StepIn(4);
			UnPB.StepIn(1);
			PrivateMsg.FromQQ = UnPB.GetVarint(1);
			uint MsgType = UnPB.GetVarint(3);
			PrivateMsg.MsgType = UnPB.GetVarint(4);
			PrivateMsg.MsgID = UnPB.GetVarint(5);
			UnPB.StepOut();
			switch (MsgType)
			{
			case 33:
			{
				UnPB.StepIn(3);
				UnPack UnPack(UnPB.GetBin(2));
				Event::NoticeEvent::NoticeEvent NoticeEvent{ Event::NoticeEvent::NoticeEventType::group_memberchange ,new Event::NoticeEvent::group_memberchange };
				((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->FromGroup = UnPack.GetInt();
				UnPack.Skip(1);
				((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
				switch (UnPack.GetByte())
				{
				case 130:
					((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->Type = 0;
					break;
				case 131:
					((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->Type = 0;
					((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->OperateQQ = UnPack.GetInt();
					break;
				}
				UnPB.StepOut();
				Event::OnNoticeMsg(&NoticeEvent);
				Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &NoticeEvent);
			}
			break;
			case 34:
			{
				UnPB.StepIn(3);
				UnPack UnPack(UnPB.GetBin(2));
				Event::RequestEvent::RequestEvent RequestEvent{ Event::RequestEvent::RequestEventType::add_group ,new Event::RequestEvent::add_group };
				((Event::RequestEvent::add_group*)RequestEvent.Information)->FromGroup = UnPack.GetInt();
				UnPack.Skip(1);
				((Event::RequestEvent::add_group*)RequestEvent.Information)->FromQQ = UnPack.GetInt();
				switch (UnPack.GetByte())
				{
				case 130:
					((Event::RequestEvent::add_group*)RequestEvent.Information)->Type = 0;
					break;
				}
				UnPB.StepOut();
				Event::OnRequestMsg(&RequestEvent);
				Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &RequestEvent);
			}
			break;
			case 84:
				break;
			case 166:
				UnPB.StepIn(3);
				UnPB.StepIn(1);
				UnPB.StepIn(1);
				PrivateMsg.SendTime = UnPB.GetVarint(2);
				PrivateMsg.MsgRand = UnPB.GetVarint(3);
				UnPB.StepOut();
				while (UnPB.GetField() == 2)
				{
					UnPB.StepIn(2);
					Message::Msg* ThisMsg = nullptr;
					switch (UnPB.GetField())
					{
					case 1:
						UnPB.StepIn(1);
						if (ThisMsg != nullptr) ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::text,nullptr,new Message::text };
						else PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::text,nullptr, new Message::text };
						((Message::text*)ThisMsg->Message)->text = UnPB.GetStr(1);
						UnPB.StepOut();
						break;
					case 2://小黄豆
						UnPB.StepIn(2);
						if (ThisMsg != nullptr)	ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::classcal_face,nullptr,new Message::classcal_face };
						else PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::classcal_face,nullptr,new Message::classcal_face };
						((Message::classcal_face*)ThisMsg->Message)->id = UnPB.GetVarint(1);
						UnPB.StepOut();
						break;
					case 4:
						UnPB.StepIn(4);
						if (ThisMsg != nullptr)	ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::picture,nullptr,new Message::picture };
						else PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::picture,nullptr,new Message::picture };
						((Message::picture*)ThisMsg->Message)->Length = UnPB.GetVarint(2);
						UnPB.GetBin(((Message::picture*)ThisMsg->Message)->MD5, 7);
						((Message::picture*)ThisMsg->Message)->URL = UnPB.GetStr(15);
						((Message::picture*)ThisMsg->Message)->Width = UnPB.GetVarint(21);
						((Message::picture*)ThisMsg->Message)->Height = UnPB.GetVarint(22);
						UnPB.StepOut();
						break;
					case 5://文件
						break;
					case 6://原创表情
						UnPB.StepIn(6);
						if (ThisMsg != nullptr)	ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::expression,nullptr,new Message::expression };
						else PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::expression,nullptr,new Message::expression };
						UnPB.GetBin(((Message::expression*)ThisMsg->Message)->MD5, 4);
						((Message::expression*)ThisMsg->Message)->id = UnPB.GetVarint(5);
						UnPB.StepOut();
						break;
					case 8://图片
						UnPB.StepIn(8);
						if (ThisMsg != nullptr)	ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::picture,nullptr,new Message::picture };
						else PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::picture,nullptr,new Message::picture };
						UnPB.GetBin(((Message::picture*)ThisMsg->Message)->MD5, 13);
						((Message::picture*)ThisMsg->Message)->URL = UnPB.GetStr(16);
						((Message::picture*)ThisMsg->Message)->Width = UnPB.GetVarint(22);
						((Message::picture*)ThisMsg->Message)->Height = UnPB.GetVarint(23);
						((Message::picture*)ThisMsg->Message)->Length = UnPB.GetVarint(25);
						UnPB.StepOut();
						break;
					case 9://气泡消息
						/*
						4a 04 08 00 40 03
						[
						9 {
						  1: 0
						  8: 3
						}
						]
						*/
						break;
					case 12://xml
						UnPB.StepIn(12);
						if (PrivateMsg.Msg != nullptr) Message::DestoryMsg(PrivateMsg.Msg);
						PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::xml ,nullptr,new Message::xml };
						{
							LPBYTE Bin = UnPB.GetBin(1);
							if (Bin[4] == 1)
							{
								((Message::xml*)ThisMsg->Message)->text = Utils::ZlibUnCompress(Bin + 5, XBin::Bin2Int(Bin) - 5);
								delete Bin;
							}
							else
							{
								uint len = XBin::Bin2Int(Bin) - 4;
								((Message::xml*)ThisMsg->Message)->text = new char[len];
								memcpy(((Message::xml*)ThisMsg->Message)->text, Bin + 5, len - 1);
								((Message::xml*)ThisMsg->Message)->text[len] = 0;
								delete Bin;
							}
						}
						UnPB.StepOut();
						break;
					case 16:
						/*
						82 01 0b 0a 05 65 6d 6d 6d 63 18 01 28 01
						[
						16 {
						  1 {
							12: emmmc //发送人群名片
						  }
						  3: 1
						  5: 1
						}
						]
						*/
						break;
					case 33://小视频
						break;
					case 37:
						/*
						aa 02 3e 50 00 60 00 68 00 9a 01 35 08 07 20 cb
						50 c8 01 00 f0 01 00 f8 01 00 90 02 00 98 03 00
						a0 03 00 b0 03 00 c0 03 00 d0 03 00 e8 03 00 8a
						04 02 10 02 90 04 80 40 b8 04 00 c0 04 00 ca 04
						00
						[
						37 {
						  10: 0
						  12: 0
						  13: 0
						  19 {
							1: 7
							4: 10315
							25: 0
							30: 0
							31: 0
							34: 0
							51: 0
							52: 0
							54: 0
						   56: 0
							58: 0
							61: 0
							65 {
							  2: 2
							}
							66: 8192
							71: 0
							72: 0
							73: ""
						  }
						}
						]
						*/
						break;
					case 45://回复
						UnPB.StepIn(45);
						if (ThisMsg != nullptr) Message::DestoryMsg(PrivateMsg.Msg);
						PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::reply ,nullptr,new Message::reply };
						((Message::reply*)ThisMsg->Message)->MsgId = UnPB.GetVarint(1);
						((Message::reply*)ThisMsg->Message)->QQ = UnPB.GetVarint(2);
						((Message::reply*)ThisMsg->Message)->Time = UnPB.GetVarint(3);
						UnPB.GetVarint(4);
						{
							Message::Msg* ReplyMsg = nullptr;
							while (UnPB.GetField() == 5)
							{
								UnPB.StepIn(5);
								if (ReplyMsg != nullptr) ReplyMsg = ReplyMsg->NextPoint = new Message::Msg;
								else ((Message::reply*)ThisMsg->Message)->Msg = ReplyMsg = new Message::Msg;
								switch (UnPB.GetField())
								{
								case 1:
									ReplyMsg->MsgType = Message::MsgType::text;
									ReplyMsg->Message = new Message::text;
									UnPB.StepIn(1);
									((Message::text*)ReplyMsg->Message)->text = UnPB.GetStr(1);
									UnPB.StepOut();
									break;
								case 2:
									ReplyMsg->MsgType = Message::MsgType::classcal_face;
									ReplyMsg->Message = new Message::classcal_face;
									UnPB.StepIn(2);
									((Message::classcal_face*)ReplyMsg->Message)->id = UnPB.GetVarint(1);
									UnPB.StepOut();
									break;
								}
								UnPB.StepOut();
							}
						}
						UnPB.StepOut();
						break;
					case 51://json
						UnPB.StepIn(51);
						if (PrivateMsg.Msg != nullptr) Message::DestoryMsg(PrivateMsg.Msg);
						PrivateMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::json ,nullptr,new Message::json };
						{
							LPBYTE Bin = UnPB.GetBin(1);
							if (Bin[4] == 1)
							{
								((Message::json*)ThisMsg->Message)->text = Utils::ZlibUnCompress(Bin + 5, XBin::Bin2Int(Bin) - 5);
								delete Bin;
							}
							else
							{
								uint len = XBin::Bin2Int(Bin) - 4;
								((Message::json*)ThisMsg->Message)->text = new char[len];
								memcpy(((Message::json*)ThisMsg->Message)->text, Bin + 5, len - 1);
								((Message::json*)ThisMsg->Message)->text[len] = 0;
								delete Bin;
							}

						}
						UnPB.StepOut();
						break;
					case 53:
						UnPB.StepIn(53);
						UnPB.GetVarint(1);
						//Todo 吃瓜等新表情,json等解析
						UnPB.StepOut();
						break;
					case 56://红包和转账
						UnPB.StepIn(38);
						UnPB.StepIn(1);
						{
							char* listid = nullptr, * authkey = nullptr;
							uint channel = NULL;
							listid = UnPB.GetStr(9);
							authkey = UnPB.GetStr(10);
							channel = UnPB.GetVarint(51);
							delete[] listid, authkey;
						}
						UnPB.StepOut();
						UnPB.StepOut();
						break;
					default:
						break;
					}
					UnPB.StepOut();
				}
				UnPB.StepOut();
				UnPB.StepOut();
				Event::OnPrivateMsg(&PrivateMsg);
				if (PrivateMsg.Msg != nullptr) Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::PRIVATE, L"Simple Message", PrivateMsg.Msg);
				Message::DestoryMsg(PrivateMsg.Msg);
				break;
			default:
				throw "Unknow msgtype";
				break;
			}
			UnPB.StepOut();
		}
		UnPB.StepOut();
	}
}

/// <summary>
/// 发送消息(群聊,私聊)
/// </summary>
/// <param name="ToNumber"></param>
/// <param name="ToType">接收者类型 0 Friend 1 Group</param>
/// <param name="Msg"></param>
/// <returns></returns>
bool Android::MessageSvc_PbSendMsg(const uint ToNumber, const byte ToType, const Message::Msg* Msg)
{
	ProtobufStruct::TreeNode Node8{ nullptr,nullptr,8,ProtobufStruct::ProtobufStructType::VARINT,(void*)(ToType == 0 ? 2 : 1) };
	ProtobufStruct::TreeNode Node5, Node6, Node6_1, Node6_2, Node6_3, Node6_4, Node6_5, Node6_9, Node6_11, Node6_12, Node6_13, Node6_14;
	if (ToType == 0)
	{
		Node6_14 = ProtobufStruct::TreeNode{ nullptr,nullptr,14,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
		Node6_13 = ProtobufStruct::TreeNode{ &Node6_14,nullptr,13,ProtobufStruct::ProtobufStructType::VARINT,(void*)std::time(0) };
		Node6_12 = ProtobufStruct::TreeNode{ &Node6_13,nullptr,12,ProtobufStruct::ProtobufStructType::VARINT,(void*)41 };
		Node6_11 = ProtobufStruct::TreeNode{ &Node6_12,nullptr,11,ProtobufStruct::ProtobufStructType::VARINT,(void*)1885270429 };
		Node6_9 = ProtobufStruct::TreeNode{ &Node6_11,nullptr,9,ProtobufStruct::ProtobufStructType::VARINT,(void*)2346412847 };
		Node6_5 = ProtobufStruct::TreeNode{ &Node6_9,nullptr,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)562530569 };
		Node6_4 = ProtobufStruct::TreeNode{ &Node6_5,nullptr,4,ProtobufStruct::ProtobufStructType::VARINT,(void*)3414434724 };
		Node6_3 = ProtobufStruct::TreeNode{ &Node6_4,nullptr,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)1787282332 };
		Node6_2 = ProtobufStruct::TreeNode{ &Node6_3,nullptr,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)std::time(0) };
		Node6_1 = ProtobufStruct::TreeNode{ &Node6_2,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)std::time(0) };
		Node6 = ProtobufStruct::TreeNode{ &Node6_1,&Node8,6,ProtobufStruct::ProtobufStructType::LENGTH, };
		Node5 = ProtobufStruct::TreeNode{ nullptr,&Node6,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)Utils::GetRandom(0,2147483647) };
	}
	else Node5 = ProtobufStruct::TreeNode{ nullptr,&Node8,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)Utils::GetRandom(0,2147483647) };
	ProtobufStruct::TreeNode Node4{ nullptr,&Node5,4,ProtobufStruct::ProtobufStructType::VARINT,(void*)Utils::GetRandom(0,2147483647) };
	ProtobufStruct::TreeNode* Node3_1_2 = nullptr;
	do
	{
		switch (Msg->MsgType)
		{
		case Message::MsgType::text:
			Node3_1_2 = new ProtobufStruct::TreeNode{ nullptr,Node3_1_2,2,ProtobufStruct::ProtobufStructType::LENGTH,Message::Pack1(((Message::text*)Msg->Message)->text,((Message::text*)Msg->Message)->AtQQ) };
			break;
		case Message::MsgType::classcal_face:
			Node3_1_2 = new ProtobufStruct::TreeNode{ nullptr,Node3_1_2,2,ProtobufStruct::ProtobufStructType::LENGTH,Message::Pack2(((Message::classcal_face*)Msg->Message)->id) };
			break;
		case Message::MsgType::expression:

			break;
		case Message::MsgType::picture:
			break;
		case Message::MsgType::xml:
			break;
		case Message::MsgType::reply:
		{
			Message::Msg* ReplyMsg = ((Message::reply*)Msg->Message)->Msg;
			while (ReplyMsg != nullptr)
			{
			}
		}
		break;
		case Message::MsgType::json:
			Node3_1_2 = new ProtobufStruct::TreeNode{ nullptr,Node3_1_2,2,ProtobufStruct::ProtobufStructType::LENGTH,Message::Pack51(((Message::json*)Msg->Message)->text) };
			break;
		default:
			break;
		}
	} while ((Msg = Msg->NextPoint) != nullptr);
	Node3_1_2 = new ProtobufStruct::TreeNode{ nullptr, Node3_1_2,2,ProtobufStruct::ProtobufStructType::LENGTH, Message::Pack37() };
	ProtobufStruct::TreeNode Node3_1{ Node3_1_2,nullptr,1,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node3{ &Node3_1,&Node4,3,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node2_3{ nullptr,nullptr,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2_2{ nullptr,&Node2_3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2_1{ nullptr,&Node2_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node2{ &Node2_1,&Node3,2,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node1_1_1, Node1_1, Node1_2_1, Node1_2, Node1;

	switch (ToType)
	{
	case 0:
		Node1_1_1 = ProtobufStruct::TreeNode{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)ToNumber };
		Node1_1 = ProtobufStruct::TreeNode{ &Node1_1_1,nullptr,1,ProtobufStruct::ProtobufStructType::LENGTH, };
		Node1 = ProtobufStruct::TreeNode{ &Node1_1,&Node2,1,ProtobufStruct::ProtobufStructType::LENGTH, };
		break;
	case 1:
		Node1_2_1 = ProtobufStruct::TreeNode{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)ToNumber };
		Node1_2 = ProtobufStruct::TreeNode{ &Node1_2_1,nullptr,2,ProtobufStruct::ProtobufStructType::LENGTH, };
		Node1 = ProtobufStruct::TreeNode{ &Node1_2,&Node2,1,ProtobufStruct::ProtobufStructType::LENGTH, };
		break;
	default:
		throw "ToType not exist";
		break;
	}

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "MessageSvc.PbSendMsg", PB.Pack(&Node1)));

	ProtobufStruct::TreeNode* tmp;
	do
	{
		delete[] Node3_1_2->Data;
		tmp = Node3_1_2->brother;
		delete Node3_1_2;
	} while ((Node3_1_2 = tmp) != nullptr);
	return !UnPB.GetVarint(1);
}

bool Android::PbMessageSvc_PbMsgWithDraw(const uint Target, const uint MsgId, const uint MsgRand)
{
	ProtobufStruct::TreeNode Node2_5_1{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2_5{ &Node2_5_1,nullptr,5,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node2_4_2{ nullptr,nullptr,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)MsgRand };
	ProtobufStruct::TreeNode Node2_4_1{ nullptr,&Node2_4_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)MsgId };
	ProtobufStruct::TreeNode Node2_4{ &Node2_4_1,&Node2_5,4,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node2_3{ nullptr,&Node2_4,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)Target };
	ProtobufStruct::TreeNode Node2_2{ nullptr,&Node2_3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2_1{ nullptr,&Node2_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node2{ &Node2_1,nullptr,2,ProtobufStruct::ProtobufStructType::LENGTH, };


	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "PbMessageSvc.PbMsgWithDraw", PB.Pack(&Node2)));
	UnPB.StepIn(2);
	uint retcode = UnPB.GetVarint(1);
	if (retcode != 0)
	{
		if (QQ.ErrorMsg != nullptr) delete[] QQ.ErrorMsg;
		QQ.ErrorMsg = UnPB.GetStr(2);
		UnPB.StepOut();
		return false;
	}
	else
	{
		UnPB.StepOut();
		return true;
	}
}

void Android::ProfileService_Pb_ReqSystemMsgNew_Group()
{
	ProtobufStruct::TreeNode Node11{ nullptr,nullptr,11,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node10{ nullptr,&Node11,10,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node9{ nullptr,&Node10,9,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node8{ nullptr,&Node9,8,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node6_17{ nullptr,nullptr,17,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_16{ nullptr,&Node6_17,16,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_15{ nullptr,&Node6_16,15,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_14{ nullptr,&Node6_15,14,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_13{ nullptr,&Node6_14,13,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_12{ nullptr,&Node6_13,12,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_11{ nullptr,&Node6_12,11,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_9{ nullptr,&Node6_11,9,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_8{ nullptr,&Node6_9,8,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_7{ nullptr,&Node6_8,7,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_6{ nullptr,&Node6_7,6,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_5{ nullptr,&Node6_6,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_3{ nullptr,&Node6_5,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_2{ nullptr,&Node6_3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6_1{ nullptr,&Node6_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node6{ &Node6_1,&Node8,6,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node5{ nullptr,&Node6,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)3 };
	ProtobufStruct::TreeNode Node4{ nullptr,&Node5,4,ProtobufStruct::ProtobufStructType::VARINT,(void*)1000 };
	ProtobufStruct::TreeNode Node3{ nullptr,&Node4,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)1597344360637873 };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)1590834830000000 };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)20 };

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "ProfileService.Pb.ReqSystemMsgNew.Group", PB.Pack(&Node1)));
}

void Android::ImgStore_GroupPicUp(const uint Group, const byte ImageMD5[16], const uint ImageLength, const uint ImageWidth, const uint ImageHeight)
{
	LPBYTE B = new byte[20];
	memcpy(B, XBin::Int2Bin(20), 4);
	memcpy(B + 4, ImageMD5, 16);
	LPBYTE T = new byte[36];
	memcpy(T, XBin::Int2Bin(36), 4);
	memcpy(T + 4, XBin::Bin2Hex(ImageMD5, 16), 32);
	uint len = strlen(QQ_VERSION);
	LPBYTE V = new byte[len + 4];
	memcpy(V, XBin::Int2Bin(len + 4), 4);
	memcpy(V + 4, QQ_VERSION, len);
	ProtobufStruct::TreeNode Node3_19{ nullptr,nullptr,19,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node3_15{ nullptr,&Node3_19,15,ProtobufStruct::ProtobufStructType::VARINT,(void*)1006 };
	ProtobufStruct::TreeNode Node3_13{ nullptr,&Node3_15,13,ProtobufStruct::ProtobufStructType::LENGTH, V };
	ProtobufStruct::TreeNode Node3_12{ nullptr,&Node3_13,12,ProtobufStruct::ProtobufStructType::VARINT,(void*)1000 };
	ProtobufStruct::TreeNode Node3_11{ nullptr,&Node3_12,11,ProtobufStruct::ProtobufStructType::VARINT,(void*)ImageHeight };
	ProtobufStruct::TreeNode Node3_10{ nullptr,&Node3_11,10,ProtobufStruct::ProtobufStructType::VARINT,(void*)ImageWidth };
	ProtobufStruct::TreeNode Node3_9{ nullptr,&Node3_10,9,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node3_8{ nullptr,&Node3_9,8,ProtobufStruct::ProtobufStructType::VARINT,(void*)9 };
	ProtobufStruct::TreeNode Node3_7{ nullptr,&Node3_8,7,ProtobufStruct::ProtobufStructType::VARINT,(void*)5 };
	ProtobufStruct::TreeNode Node3_6{ nullptr,&Node3_7,6,ProtobufStruct::ProtobufStructType::LENGTH, T };
	ProtobufStruct::TreeNode Node3_5{ nullptr,&Node3_6,5,ProtobufStruct::ProtobufStructType::VARINT,(void*)ImageLength };
	ProtobufStruct::TreeNode Node3_4{ nullptr,&Node3_5,4,ProtobufStruct::ProtobufStructType::LENGTH,B };
	ProtobufStruct::TreeNode Node3_3{ nullptr,&Node3_4,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node3_2{ nullptr,&Node3_3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)QQ.QQ };
	ProtobufStruct::TreeNode Node3_1{ nullptr,&Node3_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)Group };
	ProtobufStruct::TreeNode Node3{ &Node3_1,nullptr,3,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)3 };

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "ImgStore.GroupPicUp", PB.Pack(&Node1)));

}

/// <summary>
/// 设置管理员
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Set"></param>
void Android::OidbSvc_0x55c_1(const uint Group, const uint QQ, const bool Set)
{
	Pack Pack(13, true);
	Pack.SetInt(Group);
	Pack.SetInt(QQ);
	Pack.SetByte(Set);

	ProtobufStruct::TreeNode Node4{ nullptr,nullptr,4,ProtobufStruct::ProtobufStructType::LENGTH,Pack.GetAll() };
	ProtobufStruct::TreeNode Node2{ nullptr,nullptr,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node1{ nullptr,nullptr,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)1372 };

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "OidbSvc.0x55c_1", PB.Pack(&Node1)));

}

/// <summary>
/// 群禁言(Time为0时解除禁言)
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Time">单位:秒</param>
void Android::OidbSvc_0x570_8(const uint Group, const uint QQ, const  uint Time)
{
	Pack Pack(19, true);
	Pack.SetInt(Group);
	Pack.SetBin((byte*)"\x20\0\1", 3);
	Pack.SetInt(QQ);
	Pack.SetInt(Time);
	ProtobufStruct::TreeNode Node4{ nullptr,nullptr,4,ProtobufStruct::ProtobufStructType::LENGTH, Pack.GetAll() };
	ProtobufStruct::TreeNode Node3{ nullptr,&Node4,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)8 };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)1392 };


	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "OidbSvc.0x570_8", PB.Pack(&Node1)));

}

/// <summary>
/// 取管理员列表(包括群主)
/// </summary>
/// <param name="Group"></param>
std::vector<uint>* Android::OidbSvc_0x899_0(const uint Group)
{
	ProtobufStruct::TreeNode Node4_5_3{ nullptr,nullptr,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)1 };
	ProtobufStruct::TreeNode Node4_5_1{ nullptr,&Node4_5_3,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node4_5{ &Node4_5_1,nullptr,5,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node4_3{ nullptr,&Node4_5,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)2 };
	ProtobufStruct::TreeNode Node4_2{ nullptr,&Node4_3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node4_1{ nullptr,&Node4_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)Group };
	ProtobufStruct::TreeNode Node4{ &Node4_1,nullptr,4,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node4,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)2201 };

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "OidbSvc.0x899_0", PB.Pack(&Node1)));

	std::vector<uint> ManagerList;

	UnPB.StepIn(4);
	while (UnPB.IsEnd())
	{
		UnPB.StepIn(4);
		ManagerList.insert(ManagerList.end(), UnPB.GetVarint(1));
		UnPB.StepOut();
	}
	UnPB.StepOut();
	return &ManagerList;
}

/// <summary>
/// 全体禁言(解禁)
/// </summary>
/// <param name="Group"></param>
/// <param name="Ban"></param>
void Android::OidbSvc_0x89a_0(const uint Group, const bool Ban)
{
	ProtobufStruct::TreeNode Node4_2_17{ nullptr,nullptr,17,ProtobufStruct::ProtobufStructType::VARINT,(void*)(Ban ? 268435455 : 0) };
	ProtobufStruct::TreeNode Node4_2{ &Node4_2_17,nullptr,2,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node4_1{ nullptr,&Node4_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)Group };
	ProtobufStruct::TreeNode Node4{ &Node4_1,nullptr,4,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node3{ nullptr,&Node4,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)2202 };

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "OidbSvc.0x89a_0", PB.Pack(&Node1)));

}

/// <summary>
/// 群踢人
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Forever">不再接收加群申请</param>
void Android::OidbSvc_0x8a0_0(const uint Group, const  uint QQ, const  bool Forever)
{
	ProtobufStruct::TreeNode Node4_2_3{ nullptr,nullptr,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)Forever };
	ProtobufStruct::TreeNode Node4_2_2{ nullptr,&Node4_2_3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)QQ };
	ProtobufStruct::TreeNode Node4_2_1{ nullptr,&Node4_2_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)5 };
	ProtobufStruct::TreeNode Node4_2{ &Node4_2_1,nullptr,2,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node4_1{ nullptr,&Node4_2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)Group };
	ProtobufStruct::TreeNode Node4{ &Node4_1,nullptr,4,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node3{ nullptr,&Node4,3,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node3,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)0 };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)2208 };

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "OidbSvc.0x8a0_0", PB.Pack(&Node1)));

}

/// <summary>
/// 设置专属头衔
/// </summary>
/// <param name="Group"></param>
/// <param name="QQ"></param>
/// <param name="Title">为空即收回</param>
void Android::OidbSvc_0x8fc_2(const uint Group, const  uint QQ, const  char* Title)
{
	uint len = strlen(Title);
	LPBYTE T = new byte[len + 4];
	memcpy(T, XBin::Int2Bin(len + 4), 4);
	memcpy(T + 4, Title, len);

	ProtobufStruct::TreeNode Node4_3_7{ nullptr,nullptr,7,ProtobufStruct::ProtobufStructType::LENGTH, };//群名片
	ProtobufStruct::TreeNode Node4_3_6{ nullptr,&Node4_3_7,6,ProtobufStruct::ProtobufStructType::VARINT,(void*)4294967295 };
	ProtobufStruct::TreeNode Node4_3_5{ nullptr,&Node4_3_6,5,ProtobufStruct::ProtobufStructType::LENGTH,T };
	ProtobufStruct::TreeNode Node4_3_1{ nullptr,&Node4_3_5,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)2257382492 };
	ProtobufStruct::TreeNode Node4_3{ &Node4_3_1,nullptr,3,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node4_1{ nullptr,&Node4_3,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)Group };
	ProtobufStruct::TreeNode Node4{ &Node4_1,nullptr,4,ProtobufStruct::ProtobufStructType::LENGTH, };
	ProtobufStruct::TreeNode Node2{ nullptr,&Node4,2,ProtobufStruct::ProtobufStructType::VARINT,(void*)2 };
	ProtobufStruct::TreeNode Node1{ nullptr,&Node2,1,ProtobufStruct::ProtobufStructType::VARINT,(void*)2300 };

	Protobuf PB;
	UnProtobuf UnPB(Fun_Send_Sync(11, 1, "OidbSvc.0x8fc_2", PB.Pack(&Node1)));

}

void Android::Un_Tlv_Get(const unsigned short cmd, const byte* bin, const uint len)
{
	::UnPack UnPack(bin, len);
	switch (cmd)
	{
	case 0x103:
		if (QQ.Cookie.StWebSig != nullptr) delete[] QQ.Cookie.StWebSig;
		QQ.Cookie.StWebSig = new byte[len];
		memcpy(QQ.Cookie.StWebSig, bin, len);
		break;
	case 0x104:
		if (QQ.Login->VieryToken2 != nullptr) delete[] QQ.Login->VieryToken2;
		QQ.Login->VieryToken2 = new byte[len];
		memcpy(QQ.Login->VieryToken2, bin, len);
		break;
	case 0x105:
	{
		uint length = UnPack.GetShort();
		if (QQ.Login->VieryToken1 != nullptr) delete[] QQ.Login->VieryToken1;
		QQ.Login->VieryToken1 = new byte[len];
		memcpy(QQ.Login->VieryToken1, bin, len);
		length = UnPack.GetShort();
		if (QQ.Login->Viery_Image != nullptr) delete[] QQ.Login->Viery_Image;
		QQ.Login->Viery_Image = new byte[len];
		memcpy(QQ.Login->Viery_Image, bin, len);
	}
	break;
	case 0x106:
	{
		std::vector<byte> data;
		Tea::decrypt(QQ.Token.md52, bin, len, data);
		UnPack.Reset(&data);
		UnPack.GetShort();
		UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetLong();
		UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetByte();
		UnPack.GetBin(16);
		UnPack.GetBin(16);
		UnPack.GetInt();
		UnPack.GetByte();
		UnPack.GetBin(16);
		UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetBin(UnPack.GetShort());
		UnPack.GetShort();
	}
	break;
	case 0x108:
		if (QQ.Token.ksid != nullptr) delete[] QQ.Token.ksid;
		QQ.Token.ksid = new byte[len];
		memcpy(QQ.Token.ksid, bin, len);
		break;
	case 0x10A:
		if (QQ.Token.TGT != nullptr) delete[] QQ.Token.TGT;
		QQ.Token.TGT = new byte[len];
		memcpy(QQ.Token.TGT, bin, len);
		break;
	case 0x10C:
		if (QQ.Token.TGTkey != nullptr) delete[] QQ.Token.TGTkey;
		QQ.Token.TGTkey = new byte[16];
		memcpy(QQ.Token.TGTkey, UnPack.GetBin(16), 16);
		break;
	case 0x10D:
		if (QQ.Token.TGTkey != nullptr) delete[] QQ.Token.TGTkey;
		QQ.Token.TGTkey = new byte[16];
		memcpy(QQ.Token.TGTkey, UnPack.GetBin(16), 16);
		break;
	case 0x10E:
		if (QQ.Token.StKey != nullptr) delete[] QQ.Token.StKey;
		QQ.Token.StKey = new byte[len];
		memcpy(QQ.Token.StKey, bin, len);
		break;
	case 0x114:
		UnPack.GetShort();
		UnPack.GetInt();
		UnPack.GetBin(UnPack.GetShort());
		break;
	case 0x118:
		UnPack.GetBin(UnPack.GetInt());
		break;
	case 0x119:
	{
		std::vector<byte> data;
		Tea::decrypt(QQ.Token.TGTkey, bin, len, data);
		UnPack.Reset(&data);
		unsigned short Count = UnPack.GetShort();
		for (size_t i = 0; i < Count; i++)
		{
			unsigned short cmd = UnPack.GetShort();
			unsigned short binlen = UnPack.GetShort();
			Un_Tlv_Get(cmd, UnPack.GetBin(binlen), binlen);
		}
	}
	break;
	case 0x11A:
	{
		UnPack.GetShort();
		UnPack.GetByte();
		UnPack.GetByte();
		if (QQ.Nick != nullptr) delete[] QQ.Nick;
		byte length = UnPack.GetByte();
		QQ.Nick = new char[length];
		QQ.Nick[length] = 0;
		memcpy(QQ.Nick, UnPack.GetBin(length), length);
	}
	break;
	case 0x11F:
		UnPack.GetInt();
		UnPack.GetInt();
		UnPack.GetShort();
		break;
	case 0x120:
		if (QQ.Cookie.skey != nullptr) delete[] QQ.Cookie.skey;
		QQ.Cookie.skey = new char[len + 1];
		QQ.Cookie.skey[len] = 0;
		memcpy(QQ.Cookie.skey, bin, len);
		break;
	case 0x130:
		UnPack.GetShort();
		UnPack.GetInt();//time
		UnPack.GetBin(4);//ip
		break;
	case 0x133:
		if (QQ.Token.wtSessionTicket != nullptr) delete[] QQ.Token.wtSessionTicket;
		QQ.Token.wtSessionTicket = new byte[len];
		memcpy(QQ.Token.wtSessionTicket, bin, len);
		break;
	case 0x134:
		if (QQ.Token.wtSessionTicketKey != nullptr) delete[] QQ.Token.wtSessionTicketKey;
		QQ.Token.wtSessionTicketKey = new byte[len];
		memcpy(QQ.Token.wtSessionTicketKey, bin, len);
		break;
	case 0x136:
		if (QQ.Cookie.vkey != nullptr) delete[] QQ.Cookie.vkey;
		QQ.Cookie.vkey = new char[len + 1];
		QQ.Cookie.vkey[len] = 0;
		memcpy(QQ.Cookie.vkey, bin, len);
		break;
	case 0x138:
		for (size_t i = 0; i < UnPack.GetInt(); i++)
		{
			unsigned short tlv_cmd = UnPack.GetShort();
			uint time = UnPack.GetInt();
			UnPack.GetInt();
		}
		break;
	case 0x143:
		if (QQ.Token.A2 != nullptr) delete[] QQ.Token.A2;
		QQ.Token.A2 = new byte[len];
		memcpy(QQ.Token.A2, bin, len);
		break;
	case 0x146:
		UnPack.GetInt();
		UnPack.GetBin(UnPack.GetShort());
		UnPack.GetBin(UnPack.GetShort());
		break;
	case 0x161:
		UnPack.GetShort();
		break;
	case 0x163:
		//未知
		break;
	case 0x164:
		if (QQ.Cookie.sid != nullptr) delete[] QQ.Cookie.sid;
		QQ.Cookie.sid = new byte[len];
		memcpy(QQ.Cookie.sid, bin, len);
		break;
	case 0x165:
		//请输入图中字符，帮助我们完成安全测试
		break;
	case 0x16A:
		if (QQ.Token.token_16A != nullptr) delete[] QQ.Token.token_16A;
		QQ.Token.token_16A = new byte[len];
		memcpy(QQ.Token.token_16A, bin, len);
		break;
	case 0x16D:
		if (QQ.Cookie.superKey != nullptr) delete[] QQ.Cookie.superKey;
		QQ.Cookie.superKey = new char[len + 1];
		QQ.Cookie.superKey[len] = 0;
		memcpy(QQ.Cookie.superKey, bin, len);
		break;
	case 0x174:
		if (QQ.Login->SmsToken != nullptr) delete[] QQ.Login->SmsToken;
		QQ.Login->SmsToken = new char[len + 1];
		QQ.Login->SmsToken[len] = 0;
		memcpy(QQ.Login->SmsToken, bin, len);
		break;
	case 0x178:
	{
		UnPack.GetBin(UnPack.GetShort());
		uint length = UnPack.GetShort();
		if (QQ.Login->PhoneNumber != nullptr) delete[] QQ.Login->PhoneNumber;
		QQ.Login->PhoneNumber = new char[length + 1];
		QQ.Login->PhoneNumber[length] = 0;
		memcpy(QQ.Login->PhoneNumber, UnPack.GetBin(length), length);
	}
	break;
	case 0x179:
		UnPack.GetShort();
		break;
	case 0x17B:
		//未知
		break;
	case 0x17D:
		//网址
		break;
	case 0x17E:
		//为保障你的QQ帐号安全，当前设备需进行身份验证，通过后下次无需验证。
		break;
	case 0x192:
		if (QQ.Login->Viery_Ticket != nullptr) delete[] QQ.Login->Viery_Ticket;
		QQ.Login->Viery_Ticket = new char[len + 1];
		QQ.Login->Viery_Ticket[len] = 0;
		memcpy(QQ.Login->Viery_Ticket, bin, len);
		break;
	case 0x204:
		//网址,过设备锁方式
		break;
	case 0x305:
		if (QQ.Token.D2Key != nullptr) delete[] QQ.Token.D2Key;
		QQ.Token.D2Key = new byte[len];
		memcpy(QQ.Token.D2Key, bin, len);
		break;
	case 0x402:
		if (QQ.Login->token_402 != nullptr) delete[] QQ.Login->token_402;
		QQ.Login->token_402 = new byte[len];
		memcpy(QQ.Login->token_402, bin, len);
		break;
	case 0x403:
		if (QQ.Login->token_403 != nullptr) delete[] QQ.Login->token_403;
		QQ.Login->token_403 = new byte[len];
		memcpy(QQ.Login->token_403, bin, len);
		break;
	case 0x508:
		//懒得整
		break;
	case 0x512:
	{
		unsigned short length = UnPack.GetShort();
		QQ.Cookie.p_skey.resize(length);
		for (size_t i = 0; i < length; i++)
		{
			unsigned short l = UnPack.GetShort();
			QQ.Cookie.p_skey[i].host = new char[l + 1];
			QQ.Cookie.p_skey[i].host[l] = 0;
			memcpy(QQ.Cookie.p_skey[i].host, UnPack.GetBin(l), l);
			l = UnPack.GetShort();
			QQ.Cookie.p_skey[i].p_skey = new char[l + 1];
			QQ.Cookie.p_skey[i].p_skey[l] = 0;
			memcpy(QQ.Cookie.p_skey[i].p_skey, UnPack.GetBin(l), l);
			UnPack.GetShort();
		}
	}
	break;
	case 0x515:
		break;
	case 0x522:
		UnPack.GetInt();
		UnPack.GetInt();  // QQ
		UnPack.GetBin(4);  // IP
		UnPack.GetInt();  // Time
		UnPack.GetInt();  // APPID
		break;
	case 0x528:
		//{"QIM_invitation_bit":"1"}
		break;
	case 0x537:
		UnPack.GetShort();
		UnPack.GetInt();
		UnPack.GetInt();  //QQ
		UnPack.GetByte();
		UnPack.GetBin(4);  //IP
		UnPack.GetInt();  // Time
		UnPack.GetInt();  // appid
		break;
	case 0x543:
		break;
	case 0x546:
		if (QQ.Login->ClientPow != nullptr) delete[] QQ.Login->ClientPow;
		QQ.Login->ClientPow = new byte[len];
		memcpy(QQ.Login->ClientPow, bin, len);
		break;
	case 0x550:

		break;
	default:
		throw "Unknown Tlv";
		break;
	}
}

void Android::Un_Pack_Body_Request_Packet(const LPBYTE BodyBin, LPBYTE& sBuffer)
{
	UnJce UnJce(BodyBin);
	UnJce.Read(sBuffer, 7);
}

void Android::Un_Pack_wtlogin_login(const LPBYTE BodyBin)
{
	::UnPack UnPack(BodyBin);
	UnPack.GetByte();
	const uint len = UnPack.GetShort() - 1 - 2 - 2 - 2 - 2 - 4 - 2 - 1 - 1;
	UnPack.GetShort();
	UnPack.GetShort();
	UnPack.GetShort();
	UnPack.GetInt();
	UnPack.GetShort();
	const byte Result = UnPack.GetByte();

	const byte* Buffer = nullptr;
	Buffer = UnPack.GetBin(len);
	byte key[16] = { 0 };
	memcpy(key, Utils::MD5(QQ.Login->ECDH.sharekey, 24), 16);
	std::vector<byte> data;
	Tea::decrypt(key, Buffer, len, data);
	UnPack.Reset(&data);
	const byte* publickey = nullptr;
	publickey = UnPack.GetBin(UnPack.GetShort());
	const byte* sharekey = Utils::Ecdh_CountSharekey(QQ.Login->ECDH.prikey, publickey);
	memcpy(key, Utils::MD5(sharekey, 24), 16);
	delete[] sharekey;
	std::vector<byte> buffer;
	Tea::decrypt(key, UnPack.GetCurrentPoint(), UnPack.GetLeftLength(), buffer);
	UnPack.Reset(&buffer);
	UnPack.GetShort();
	UnPack.GetByte();
	unsigned short Count = UnPack.GetShort();
	for (size_t i = 0; i < Count; i++)
	{
		unsigned short cmd = UnPack.GetShort();
		unsigned short binlen = UnPack.GetShort();
		Un_Tlv_Get(cmd, UnPack.GetBin(binlen), binlen);
	}
	switch (Result)
	{
	case 0:
		QQ.Login->state = LOGIN_SUCCESS;
		break;
	case 1://密码错误
		QQ.Login->state = LOGIN_ERROR;
		break;
	case 2://验证码
		QQ.Login->state = LOGIN_VERIY;
		break;
	case 32://回收
		QQ.Login->state = LOGIN_ERROR;
		break;
	case 40://冻结
		QQ.Login->state = LOGIN_ERROR;
		break;
	case 160://设备锁
		QQ.Login->state = LOGIN_VERIY_SMS;
		break;
	case 162://短信发送失败
		QQ.Login->state = LOGIN_ERROR;
		break;
	case 180://回滚
		//To do
		break;
	case 204://设备锁 验证
		wtlogin_login_Viery_204();
		break;
	case 235://版本过低
		QQ.Login->state = LOGIN_ERROR;
		break;
	case 237://上网环境异常
		QQ.Login->state = LOGIN_ERROR;
		break;
	case 239://设备锁
		QQ.Login->state = LOGIN_VERIY_SMS;
		break;
	default:
		QQ.Login->state = Result;
		throw "Unknown login result";
		break;
	}
}

void Android::Un_Pack_OnlinePush_PbPushGroupMsg(const LPBYTE BodyBin, const uint sso_seq)
{
	Event::GroupMsg GroupMsg;
	::UnProtobuf UnPB(BodyBin);
	UnPB.StepIn(1);
	UnPB.StepIn(1);
	GroupMsg.FromQQ = UnPB.GetVarint(1);
	GroupMsg.MsgID = UnPB.GetVarint(5);
	GroupMsg.SendTime = UnPB.GetVarint(6);
	UnPB.StepIn(9);
	GroupMsg.FromGroup = UnPB.GetVarint(1);
	GroupMsg.FromQQName = UnPB.GetStr(4);
	GroupMsg.FromGroupName = UnPB.GetStr(8);
	UnPB.StepOut();
	GroupMsg.MsgType = UnPB.GetVarint(10);
	UnPB.StepOut();
	UnPB.StepIn(3);
	UnPB.StepIn(1);
	UnPB.StepIn(1);
	GroupMsg.MsgRand = UnPB.GetVarint(3);
	UnPB.StepOut();
	Message::Msg* ThisMsg = nullptr;
	while (!UnPB.IsEnd())
	{
		UnPB.StepIn(2);
		switch (UnPB.GetField())
		{
		case 1://文字和At
			UnPB.StepIn(1);
			if (ThisMsg != nullptr) ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::text,nullptr,new Message::text };
			else GroupMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::text,nullptr, new Message::text };
			((Message::text*)ThisMsg->Message)->text = UnPB.GetStr(1);
			if (UnPB.GetField() == 3)
			{
				delete[]((Message::text*)ThisMsg->Message)->text;
				((Message::text*)ThisMsg->Message)->text = nullptr;
				UnPack UnPack(UnPB.GetBin(3));
				UnPack.Skip(7);
				((Message::text*)ThisMsg->Message)->AtQQ = UnPack.GetInt();
			}
			UnPB.StepOut();
			break;
		case 2://小黄豆
			UnPB.StepIn(2);
			if (ThisMsg != nullptr)	ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::classcal_face,nullptr,new Message::classcal_face };
			else GroupMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::classcal_face,nullptr,new Message::classcal_face };
			((Message::classcal_face*)ThisMsg->Message)->id = UnPB.GetVarint(1);
			UnPB.StepOut();
			break;
		case 5://文件
			break;
		case 6://原创表情
			UnPB.StepIn(6);
			if (ThisMsg != nullptr)	ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::expression,nullptr,new Message::expression };
			else GroupMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::expression,nullptr,new Message::expression };
			UnPB.GetBin(((Message::expression*)ThisMsg->Message)->MD5, 4);
			((Message::expression*)ThisMsg->Message)->id = UnPB.GetVarint(5);
			UnPB.StepOut();
			break;
		case 8://图片
			UnPB.StepIn(8);
			if (ThisMsg != nullptr)	ThisMsg = ThisMsg->NextPoint = new Message::Msg{ Message::MsgType::picture,nullptr,new Message::picture };
			else GroupMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::picture,nullptr,new Message::picture };
			UnPB.GetBin(((Message::picture*)ThisMsg->Message)->MD5, 13);
			((Message::picture*)ThisMsg->Message)->URL = UnPB.GetStr(16);
			((Message::picture*)ThisMsg->Message)->Width = UnPB.GetVarint(22);
			((Message::picture*)ThisMsg->Message)->Height = UnPB.GetVarint(23);
			((Message::picture*)ThisMsg->Message)->Length = UnPB.GetVarint(25);
			UnPB.StepOut();
			break;
		case 9://气泡消息
			/*
			4a 04 08 00 40 03
			[
			9 {
			  1: 0
			  8: 3
			}
			]
			*/
			break;
		case 12://xml
			UnPB.StepIn(12);
			if (GroupMsg.Msg != nullptr) Message::DestoryMsg(GroupMsg.Msg);
			GroupMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::xml ,nullptr,new Message::xml };
			{
				LPBYTE Bin = UnPB.GetBin(1);
				if (Bin[4] == 1)
				{
					((Message::xml*)ThisMsg->Message)->text = Utils::ZlibUnCompress(Bin + 5, XBin::Bin2Int(Bin) - 5);
					delete Bin;
				}
				else
				{
					uint len = XBin::Bin2Int(Bin) - 4;
					((Message::xml*)ThisMsg->Message)->text = new char[len];
					memcpy(((Message::xml*)ThisMsg->Message)->text, Bin + 5, len - 1);
					((Message::xml*)ThisMsg->Message)->text[len] = 0;
					delete Bin;
				}
			}
			UnPB.StepOut();
			break;
		case 16:
			/*
			82 01 0b 0a 05 65 6d 6d 6d 63 18 01 28 01
			[
			16 {
			  1 {
				12: emmmc //发送人群名片
			  }
			  3: 1
			  5: 1
			}
			]
			*/
			break;
		case 33://小视频
			break;
		case 37:
			/*
			aa 02 3e 50 00 60 00 68 00 9a 01 35 08 07 20 cb
			50 c8 01 00 f0 01 00 f8 01 00 90 02 00 98 03 00
			a0 03 00 b0 03 00 c0 03 00 d0 03 00 e8 03 00 8a
			04 02 10 02 90 04 80 40 b8 04 00 c0 04 00 ca 04
			00
			[
			37 {
			  10: 0
			  12: 0
			  13: 0
			  19 {
				1: 7
				4: 10315
				25: 0
				30: 0
				31: 0
				34: 0
				51: 0
				52: 0
				54: 0
			   56: 0
				58: 0
				61: 0
				65 {
				  2: 2
				}
				66: 8192
				71: 0
				72: 0
				73: ""
			  }
			}
			]
			*/
			break;
		case 45://回复
			UnPB.StepIn(45);
			if (ThisMsg != nullptr) Message::DestoryMsg(GroupMsg.Msg);
			GroupMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::reply ,nullptr,new Message::reply };
			((Message::reply*)ThisMsg->Message)->MsgId = UnPB.GetVarint(1);
			((Message::reply*)ThisMsg->Message)->QQ = UnPB.GetVarint(2);
			((Message::reply*)ThisMsg->Message)->Time = UnPB.GetVarint(3);
			UnPB.GetVarint(4);
			{
				Message::Msg* ReplyMsg = nullptr;
				while (UnPB.GetField() == 5)
				{
					UnPB.StepIn(5);
					if (ReplyMsg != nullptr) ReplyMsg = ReplyMsg->NextPoint = new Message::Msg;
					else ((Message::reply*)ThisMsg->Message)->Msg = ReplyMsg = new Message::Msg;
					switch (UnPB.GetField())
					{
					case 1:
						ReplyMsg->MsgType = Message::MsgType::text;
						ReplyMsg->Message = new Message::text;
						UnPB.StepIn(1);
						((Message::text*)ReplyMsg->Message)->text = UnPB.GetStr(1);
						UnPB.StepOut();
						break;
					case 2:
						ReplyMsg->MsgType = Message::MsgType::classcal_face;
						ReplyMsg->Message = new Message::classcal_face;
						UnPB.StepIn(2);
						((Message::classcal_face*)ReplyMsg->Message)->id = UnPB.GetVarint(1);
						UnPB.StepOut();
						break;
					}
					UnPB.StepOut();
				}
			}
			UnPB.StepOut();
			break;
		case 51://json
			UnPB.StepIn(51);
			if (GroupMsg.Msg != nullptr) Message::DestoryMsg(GroupMsg.Msg);
			GroupMsg.Msg = ThisMsg = new Message::Msg{ Message::MsgType::json ,nullptr,new Message::json };
			{
				LPBYTE Bin = UnPB.GetBin(1);
				if (Bin[4] == 1)
				{
					((Message::json*)ThisMsg->Message)->text = Utils::ZlibUnCompress(Bin + 5, XBin::Bin2Int(Bin) - 5);
					delete Bin;
				}
				else
				{
					uint len = XBin::Bin2Int(Bin) - 4;
					((Message::json*)ThisMsg->Message)->text = new char[len];
					memcpy(((Message::json*)ThisMsg->Message)->text, Bin + 5, len - 1);
					((Message::json*)ThisMsg->Message)->text[len] = 0;
					delete Bin;
				}
			}
			UnPB.StepOut();
			break;
		case 53:
			UnPB.StepIn(53);
			UnPB.GetVarint(1);
			//Todo 吃瓜等新表情,json等解析
			UnPB.StepOut();
			break;
		case 56://红包和转账
			UnPB.StepIn(38);
			UnPB.StepIn(1);
			{
				char* listid = nullptr, * authkey = nullptr;
				uint channel = NULL;
				listid = UnPB.GetStr(9);
				authkey = UnPB.GetStr(10);
				channel = UnPB.GetVarint(51);
				delete[] listid, authkey;
			}
			UnPB.StepOut();
			UnPB.StepOut();
			break;
		default:
			break;
		}
		UnPB.StepOut();
	}
	UnPB.StepOut();
	UnPB.StepOut();
	UnPB.StepOut();
	if (GroupMsg.FromQQ == QQ.QQ)
	{
		Message::DestoryMsg(GroupMsg.Msg);
		return;
	}
	//QQ_SendGroupMsg(GroupMsg.FromGroup, GroupMsg.Msg);
	Event::OnGroupMsg(&GroupMsg);
	if (GroupMsg.Msg != nullptr) Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::_GROUP, L"Simple Message", GroupMsg.Msg);
	Message::DestoryMsg(GroupMsg.Msg);
}

void Android::Un_Pack_OnlinePush_PbPushTransMsg(const LPBYTE BodyBin, const uint sso_seq)
{
	::UnProtobuf UnPB(BodyBin);
	uint Type = UnPB.GetVarint(3);
	UnPack UnPack(UnPB.GetBin(10));
	Event::NoticeEvent::NoticeEvent NoticeEvent;
	switch (Type)
	{
	case 34:
		NoticeEvent = Event::NoticeEvent::NoticeEvent{ Event::NoticeEvent::NoticeEventType::group_memberchange ,new Event::NoticeEvent::group_memberchange };
		((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->FromGroup = UnPack.GetInt();
		UnPack.Skip(1);
		((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
		Type = UnPack.GetByte();
		switch (Type)
		{
		case 3:
			((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->Type = 3;
			((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->OperateQQ = UnPack.GetInt();
			break;
		case 130:
			((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->Type = 2;
			break;
		case 131:
			((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->Type = 3;
			((Event::NoticeEvent::group_memberchange*)NoticeEvent.Information)->OperateQQ = UnPack.GetInt();
			break;
		default:
			throw "Unknown type";
			break;
		}
		break;
	case 44:
		NoticeEvent = Event::NoticeEvent::NoticeEvent{ Event::NoticeEvent::NoticeEventType::group_adminchange ,new Event::NoticeEvent::group_adminchange };
		((Event::NoticeEvent::group_adminchange*)NoticeEvent.Information)->FromGroup = UnPack.GetInt();
		UnPack.Skip(2);
		((Event::NoticeEvent::group_adminchange*)NoticeEvent.Information)->FromQQ = UnPack.GetInt();
		((Event::NoticeEvent::group_adminchange*)NoticeEvent.Information)->Type = UnPack.GetByte();
		break;
	default:
		break;
	}
	Event::OnNoticeMsg(&NoticeEvent);
	Log::AddLog(Log::LogType::INFORMATION, Log::MsgType::OTHER, &NoticeEvent);

}

void Android::Un_Pack_OnlinePush_PbC2CMsgSync(const LPBYTE BodyBin, const uint sso_seq)
{
}

void Android::Un_Pack_OnlinePush_ReqPush(const LPBYTE BodyBin, const uint sso_seq)
{
	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(BodyBin, sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, LPBYTE>> Map;
	UnJce.Read(Map, 0);

	LPBYTE protobuf = (byte*)"\0\0\0\0";
	int a = 0;
	for (size_t i = 0; i < Map.size(); i++)
	{
		UnJce.Reset(Map[i].Value);
		UnJce.Read(UnJce, 0);
		std::vector<::UnJce> ReqPush;
		UnJce.Read(ReqPush, 2);
		for (size_t j = 0; j < ReqPush.size(); j++)
		{
			ReqPush[j].Read(protobuf, 8);
		}
		UnJce.Read(a, 3);
	}
	OnlinePush_RespPush(sso_seq, protobuf, a);
}

void Android::Un_Pack_MessageSvc_PushNotify(const LPBYTE BodyBin, const uint sso_seq)
{
	MessageSvc_PbGetMsg();
}

void Android::Un_Pack_MessageSvc_PushForceOffline(const LPBYTE BodyBin, const uint sso_seq)
{
	QQ_Offline();
}

void Android::Un_Pack_StatSvc_SvcReqMSFLoginNotify(const LPBYTE BodyBin, const uint sso_seq)
{
	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(BodyBin, sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, std::vector<JceStruct::Map<char*, LPBYTE>>>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		for (size_t j = 0; j < Map[i].Value.size(); j++)
		{
			UnJce.Reset(Map[i].Value[j].Value);
			UnJce.Read(UnJce, 0);

			delete[] Map[i].Value[j].Key;
			delete[] Map[i].Value[j].Value;
		}

		delete[] Map[i].Key;
	}
	delete[] sBuffer;
}

void Android::Un_Pack_ConfigPushSvc_PushReq(const LPBYTE BodyBin, const uint sso_seq)
{
	LPBYTE sBuffer;
	Un_Pack_Body_Request_Packet(BodyBin, sBuffer);

	UnJce UnJce(sBuffer);
	std::vector<JceStruct::Map<char*, std::vector<JceStruct::Map<char*, LPBYTE>>>> Map;
	UnJce.Read(Map, 0);

	for (size_t i = 0; i < Map.size(); i++)
	{
		for (size_t j = 0; j < Map[i].Value.size(); j++)
		{
			UnJce.Reset(Map[i].Value[j].Value);
			UnJce.Read(UnJce, 0);

			delete[] Map[i].Value[j].Key;
			delete[] Map[i].Value[j].Value;
		}

		delete[] Map[i].Key;
	}
	delete[] sBuffer;
}

void Android::QQ_Init(const char* Account)
{
	QQ.QQ = std::strtoll(Account, NULL, 0);
	if (QQ.QQ_Str != nullptr) delete[] QQ.QQ_Str;
	QQ.QQ_Str = new char[strlen(Account) + 1];
	memcpy(QQ.QQ_Str, Account, strlen(Account) + 1);
}

byte Android::QQ_Login(const char* Password)
{
	QQ.Token.md5 = new byte[16];
	QQ.Token.md52 = new byte[16];
	memcpy(QQ.Token.md5, Utils::MD5((byte*)Password, strlen(Password)), 16);
	byte tmp[24] = { 0 };
	memcpy(tmp, QQ.Token.md5, 16);
	byte* bin = XBin::Int2Bin(QQ.QQ);
	memcpy(tmp + 20, bin, 4);
	delete[] bin;
	memcpy(QQ.Token.md52, Utils::MD5(tmp, 24), 16);
	QQ.Token.TGTkey = Utils::GetRandomBin(16);
	QQ.Login = new Login;
	QQ.Login->RandKey = Utils::GetRandomBin(16);
	unsigned char PublicKey[] = {
		0x04,0x92,0x8D,0x88,0x50,0x67,0x30,0x88,0xB3,0x43,0x26,0x4E,0x0C,0x6B,0xAC,0xB8,
		0x49,0x6D,0x69,0x77,0x99,0xF3,0x72,0x11,0xDE,0xB2,0x5B,0xB7,0x39,0x06,0xCB,0x08,
		0x9F,0xEA,0x96,0x39,0xB4,0xE0,0x26,0x04,0x98,0xB5,0x1A,0x99,0x2D,0x50,0x81,0x3D,
		0xA8
	};
	Utils::Ecdh_Crypt(QQ.Login->ECDH, PublicKey, 49);
	Fun_Connect();
	this->wtlogin_login();
	return QQ.Login->state;
}

byte Android::QQ_Login_Second()
{
	QQ.Token.md52 = new byte[16];
	byte tmp[24] = { 0 };
	memcpy(tmp, QQ.Token.md5, 16);
	byte* bin = XBin::Int2Bin(QQ.QQ);
	memcpy(tmp + 20, bin, 4);
	delete[] bin;
	memcpy(QQ.Token.md52, Utils::MD5(tmp, 24), 16);
	QQ.Login = new Login;
	Fun_Connect();
	//wtlogin_exchange_emp();
	return QQ.Login->state;
}

byte Android::QQ_Send_Sms()
{
	wtlogin_login_Send_Sms();
	return QQ.Login->state;
}

byte Android::QQ_Viery_Ticket(const char* Ticket)
{
	wtlogin_login_Viery_Ticket(Ticket);
	return QQ.Login->state;
}

byte Android::QQ_Viery_Sms(const char* SmsCode)
{
	wtlogin_login_Viery_Sms(SmsCode);
	return QQ.Login->state;
}

void Android::QQ_Login_Finish()
{
	if (QQ.Login == nullptr) return;
	if (QQ.Login->RandKey != nullptr) delete[] QQ.Login->RandKey;
	if (QQ.Login->VieryToken1 != nullptr) delete[] QQ.Login->VieryToken1;
	if (QQ.Login->VieryToken2 != nullptr) delete[] QQ.Login->VieryToken2;
	if (QQ.Login->token_402 != nullptr) delete[] QQ.Login->token_402;
	if (QQ.Login->token_403 != nullptr) delete[] QQ.Login->token_403;
	if (QQ.Login->Viery_Image != nullptr) delete[] QQ.Login->Viery_Image;
	if (QQ.Login->Viery_Ticket != nullptr) delete[] QQ.Login->Viery_Ticket;
	if (QQ.Login->PhoneNumber != nullptr) delete[] QQ.Login->PhoneNumber;
	if (QQ.Login->SmsToken != nullptr) delete[] QQ.Login->SmsToken;
	delete QQ.Login;
	QQ.Login = nullptr;
}

char* Android::QQ_Get_Viery_Ticket()
{
	return QQ.Login->Viery_Ticket;
}

char* Android::QQ_Get_Viery_PhoneNumber()
{
	return QQ.Login->PhoneNumber;
}

void Android::QQ_Online()
{
	std::thread MsgLoop(&Android::Fun_Msg_Loop, this);
	MsgLoop.detach();

	QQ.Status = 11;
	StatSvc_Register(11);
	//friendlist_getFriendGroupList(0);
	//friendlist_GetTroopListReqV2();
}

void Android::QQ_Offline()
{
	QQ.Status = 21;
	StatSvc_Register(21);
}

/// <summary>
/// 设置在线状态
/// </summary>
/// <param name="Type">11:在线 21:离线 31:离开 41:隐身 50:忙碌 60:Q我吧 70:免打扰 95:接收离线消息(离线)</param>
void Android::QQ_SetOnlineType(const byte Type)
{
	StatSvc_SetStatusFromClient(Type);
}

void Android::QQ_Heart_Beat()
{
	StatSvc_Register();
}

/// <summary>
/// Get QQ Online state
/// </summary>
/// <returns>true:online false:offline</returns>
bool Android::QQ_Status()
{
	return QQ.Status != 21;
}

const char* Android::QQ_GetErrorMsg()
{
	return QQ.ErrorMsg;
}

void Android::QQ_Set_Token(Android::Token* _Token)
{
	if (QQ.Token.A2 != nullptr) delete[] QQ.Token.A2;
	if (QQ.Token.TGT != nullptr) delete[] QQ.Token.TGT;
	if (QQ.Token.D2Key != nullptr) delete[] QQ.Token.D2Key;
	if (QQ.Token.wtSessionTicket != nullptr) delete[] QQ.Token.wtSessionTicket;
	if (QQ.Token.wtSessionTicketKey != nullptr) delete[] QQ.Token.wtSessionTicketKey;
	if (QQ.Token.token_16A != nullptr) delete[] QQ.Token.token_16A;
	if (QQ.Token.md5 != nullptr) delete[] QQ.Token.md5;
	if (QQ.Token.TGTkey != nullptr) delete[] QQ.Token.TGTkey;
	if (QQ.Token.ksid != nullptr) delete[] QQ.Token.ksid;
	QQ.Token = *_Token;
}

const Android::Token* Android::QQ_Get_Token()
{
	return &QQ.Token;
}

/// <summary>
/// 取Cookie(skey,p_skey)
/// </summary>
/// <param name="Host">p_skey的目标域名</param>
/// <returns>使用new,记得delete</returns>
char* Android::QQ_GetCookies(const char* Host)
{
	char* Cookies = new char[50];
	strcpy(Cookies, "skey=");
	strcat(Cookies, QQ.Cookie.skey);
	strcpy(Cookies, ";p_skey=");
	for (size_t i = 0; i < QQ.Cookie.p_skey.size(); i++)
	{
		if (!strcmp(QQ.Cookie.p_skey[i].host, Host))
		{
			strcat(Cookies, QQ.Cookie.p_skey[i].p_skey);
		}
	}
	return Cookies;
}

bool Android::QQ_SendLike(const uint QQ, const int Times)
{
	return VisitorSvc_ReqFavorite(QQ, Times);
}

bool Android::QQ_SendGroupMsg(const uint Group, const Message::Msg* Msg)
{
	return MessageSvc_PbSendMsg(Group, 1, Msg);
}

bool Android::QQ_DrawGroupMsg(const uint Group, const uint MsgId, const uint MsgRand)
{
	return PbMessageSvc_PbMsgWithDraw(Group, MsgId, MsgRand);
}

bool Android::QQ_SendPrivateMsg(const uint QQ, const Message::Msg* Msg)
{
	return MessageSvc_PbSendMsg(QQ, 2, Msg);
}

bool Android::QQ_DrawPrivateMsg(const uint Group, const uint MsgId, const uint MsgRand)
{
	//return PbMessageSvc_PbMsgWithDraw(Group, MsgId, MsgRand);
	return true;
}

bool Android::QQ_KickGroupMember(const uint Group, const uint QQ, const bool Forever)
{
	OidbSvc_0x8a0_0(Group, QQ, Forever);
	return true;
}

bool Android::QQ_SetGroupAdmin(const uint Group, const uint QQ, const bool Set)
{
	OidbSvc_0x55c_1(Group, QQ, Set);
	return true;
}

bool Android::QQ_SetGroupMemberTitle(const uint Group, const uint QQ, const char* Title)
{
	OidbSvc_0x8fc_2(Group, QQ, Title);
	return true;
}

bool Android::QQ_SetGroupMemberCard(const uint Group, const uint QQ, const char* Card)
{
	return friendlist_ModifyGroupCardReq(Group, QQ, Card);
}

bool Android::QQ_SetGroupMemberBan(const uint Group, const uint QQ, const uint Time)
{
	OidbSvc_0x570_8(Group, QQ, Time);
	return true;
}

bool Android::QQ_SetGroupBan(const uint Group, const bool Ban)
{
	OidbSvc_0x89a_0(Group, Ban);
	return true;
}

const std::vector<uint>* Android::QQ_GetGroupAdminList(const uint Group)
{
	return OidbSvc_0x899_0(Group);
}

/*
bool Android::QQ_DrawPrivateMsg(const uint QQ, const uint MsgId, const uint MsgRand)
{
	return PbMessageSvc_PbMsgWithDraw(QQ, MsgId, MsgRand);
}
*/
const std::vector<Android::FriendInfo>* Android::QQ_GetFriendList()
{
	return &QQ.FriendList;
}

const std::vector<Android::GroupInfo>* Android::QQ_GetGroupList()
{
	return &QQ.GroupList;
}

const std::vector<Android::GroupMemberInfo>* Android::QQ_GetGroupMemberList(uint Group)
{
	return nullptr;
}