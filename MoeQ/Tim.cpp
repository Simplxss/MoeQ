#include "pch.h"
#include "Tim.h"
/*
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

Tim::Tim(const char* IMEI, const char IMSI[16], const byte GUID[16], const byte MAC[6], const char* _device, const char* Brand)
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

bool Tim::Fun_Connect(const char* IP, const unsigned short Port)
{
	if (IP == nullptr || Port == 0)
	{
		wchar_t* IP;
		try {
			TCP.DomainGetIP(L"msfwifi.3g.qq.com", IP);
		}
		catch (...)
		{
			IP = new wchar_t[] {L"1l3.96.l3.79"};
		}
		if (Connected) TCP.Close();
		if (!TCP.Connect(Iconv::Unicode2Ansi(IP), 8080)) {
			delete[] IP;
			return false;
		};
		Connected = true;
		delete[] IP;
	}
	else
	{
		if (Connected) TCP.Close();
		if (!TCP.Connect(IP, Port)) return false;
		Connected = true;
	}
	std::thread MsgLoop(&Android::Fun_Msg_Loop, this);
	MsgLoop.detach();
	return true;
}

int Tim::Fun_Send(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer)
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
LPBYTE Tim::Fun_Send_Sync(const uint PacketType, const byte EncodeType, const char* ServiceCmd, LPBYTE Buffer)
{
	int SsoSeq = Fun_Send(PacketType, EncodeType, ServiceCmd, Buffer);

	std::mutex lock;
	std::unique_lock<std::mutex> ulock(lock);
	SendList[SsoSeq & 0x3F].cv.wait(ulock);
	return SendList[SsoSeq & 0x3F].BodyBin;
}

void Tim::Fun_Msg_Loop()
{
	LPBYTE bin;
	while ((bin = TCP.Receive()) != nullptr) { HandleThreads.exec(std::bind(&Android::Fun_Receice, this, bin), bin); }
	Connected = false;
}

void Tim::Fun_Receice(const LPBYTE bin)
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

void Tim::Fun_Handle(char* serviceCmd, const LPBYTE BodyBin, const uint sso_seq)
{
	char* buf;
	char* first = strtok_s(serviceCmd, ".", &buf);
	char* second = strtok_s(NULL, ".", &buf);
	if (!strcmp(first, "OnlinePush"))
	{
		if (!strcmp(second, "PbPushGroupMsg")) Unpack_OnlinePush_PbPushGroupMsg(BodyBin, sso_seq);
		if (!strcmp(second, "PbC2CMsgSync")) Unpack_OnlinePush_PbC2CMsgSync(BodyBin, sso_seq);
		if (!strcmp(second, "ReqPush")) Unpack_OnlinePush_ReqPush(BodyBin, sso_seq);
		if (!strcmp(second, "PbPushTransMsg")) Unpack_OnlinePush_PbPushTransMsg(BodyBin, sso_seq);
	}
	if (!strcmp(first, "MessageSvc"))
	{
		if (!strcmp(second, "PushNotify")) Unpack_MessageSvc_PushNotify(BodyBin, sso_seq);
		if (!strcmp(second, "PushForceOffline")) Unpack_MessageSvc_PushForceOffline(BodyBin, sso_seq);
	}
	if (!strcmp(first, "StatSvc"))
	{
		if (!strcmp(second, "SvcReqMSFLoginNotify")) Unpack_StatSvc_SvcReqMSFLoginNotify(BodyBin, sso_seq);
	}
	if (!strcmp(first, "ConfigPushSvc"))
	{
		if (!strcmp(second, "PushReq")) Unpack_ConfigPushSvc_PushReq(BodyBin, sso_seq);
	}
}

void Tim::Fun_Life_Event()
{
	uint time = 1;
	do
	{
		Sleep(45000);
		StatSvc_Register();
		if (!(time % 1919)) QQ_SyncCookie(); //提前45s防止plugin用了失效的cookie
		++time;
	} while (QQ_Status());
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
LPBYTE Tim::Make_Body_Request_Packet(const byte iVersion, const int iRequestId, const char* sServantName, const char* sFuncName, byte* sBuffer, uint Bufferlen)
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
LPBYTE Tim::Make_Body_PC(byte* Buffer, const uint BufferLen, const bool emp)
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
*/