#include "JceStruct.h"

void Jce::WriteHead(const JceStruct::JceStructType type, const byte tag)
{
	if (tag < 15) {
		Pack::SetByte((tag << 4) | static_cast<int>(type));
	}
	else if (tag < 256) {
		Pack::SetByte(static_cast<int>(type) | 0xF0);
		Pack::SetByte(tag);
	}
	else throw "tag is too large";
}

void Jce::Write(const char i, const byte tag)
{
	if (i == 0) WriteHead(JceStruct::JceStructType::ZERO_TAG, tag);
	else
	{
		WriteHead(JceStruct::JceStructType::BYTE, tag);
		Pack::SetByte((byte)i);//强转保留符号
	}
}

void Jce::Write(const short i, const byte tag)
{
	if (i < -128 || i > 127) {
		WriteHead(JceStruct::JceStructType::SHORT, tag);
		Pack::SetShort((unsigned short)i);//强转保留符号
	}
	else Write((char)i, tag);
}

void Jce::Write(const int i, const byte tag)
{
	if (i < -32768 || i > 32767)
	{
		WriteHead(JceStruct::JceStructType::INT, tag);
		Pack::SetInt((uint32_t)i);//强转保留符号
	}
	else Write((short)i, tag);
}

void Jce::Write(const long long i, const byte tag)
{
	if (i <= -2147483647 || i >= 2147483646) {
		WriteHead(JceStruct::JceStructType::LONG, tag);
		Pack::SetLong((unsigned long long)i);//强转保留符号
	}
	else Write((int)i, tag);
}

void Jce::Write(const float f, const byte tag)
{
	WriteHead(JceStruct::JceStructType::FLOAT, tag);
	Pack::SetFloat(f);
}

void Jce::Write(const double d, const byte tag)
{
	WriteHead(JceStruct::JceStructType::DOUBLE, tag);
	Pack::SetDouble(d);
}

void Jce::Write(const char* str, const byte tag)
{
	unsigned short len = strlen(str);
	if (len <= 225)
	{
		WriteHead(JceStruct::JceStructType::STRING1, tag);
		Pack::SetByte(len);
	}
	else
	{
		WriteHead(JceStruct::JceStructType::STRING4, tag);
		Pack::SetInt(len);
	}
	Pack::SetBin((byte*)str, len);
}

/// <summary>
/// 写自身时新的Jce Length为true,写其他时会销毁
/// </summary>
/// <param name="Jce"></param>
/// <param name="tag"></param>
void Jce::Write(Jce* Jce, const byte tag)
{
	if (Jce == this)
	{
		byte* bin;
		uint32_t len = (*Jce).GetAll_(bin, true);
		WriteHead(JceStruct::JceStructType::STRUCT_BEGIN, tag);
		Pack::SetBin(bin, len);
		WriteHead(JceStruct::JceStructType::STRUCT_END, tag);
		delete[] bin;
	}
	else
	{
		WriteHead(JceStruct::JceStructType::STRUCT_BEGIN, tag);
		byte* bin;
		uint32_t len = (*Jce).GetAll(bin);
		Pack::SetBin(bin, len);
		WriteHead(JceStruct::JceStructType::STRUCT_END, tag);
		delete[] bin;
	}
}

void Jce::Write(const LPBYTE bin, const byte tag)
{
	Jce::Write(bin + 4, XBin::Bin2Int(bin) - 4, tag);
}

void Jce::Write(const byte* bin, const uint32_t len, const byte tag)
{
	WriteHead(JceStruct::JceStructType::SIMPLE_LIST, tag);
	Write(static_cast<int>(JceStruct::JceStructType::SHORT), 0);
	Pack::SetShort(len);
	Pack::SetBin(bin, len);
}

void Jce::Write(const bool b, const byte tag)
{
	if (b)
	{
		WriteHead(JceStruct::JceStructType::BYTE, tag);
		Pack::SetByte(1);
	}
	else
	{
		WriteHead(JceStruct::JceStructType::ZERO_TAG, tag);
	}
}

void Jce::Write(const uint32_t i, const byte tag)
{
	Write((long long)i, tag);
}

/// <summary>
/// 初始化时Length要为true
/// 可以重用,需调用Clean,但要注意返回值会被复写,
/// </summary>
/// <returns></returns>
LPBYTE Jce::GetAll()
{
	Pack::SetLength();
	return Pack::GetAll();
}

/// <summary>
/// 可以重用,需调用Clean,但要注意bin会被复写
/// </summary>
/// <param name="bin"></param>
/// <returns></returns>
uint32_t Jce::GetAll(byte*& bin)
{
	return Pack::GetAll(bin);
}

/// <summary>
/// 初始化时Length要为true
/// 可以重用,无需调用Clean
/// </summary>
/// <returns></returns>
LPBYTE Jce::GetAll_(bool Length)
{
	Pack::SetLength();
	return Pack::GetAll_();
}

/// <summary>
/// 可以重用,无需调用Clean
/// </summary>
/// <returns></returns>
uint32_t Jce::GetAll_(byte*& bin, bool Length)
{
	return Pack::GetAll_(bin, Length);
}

void Jce::Clean(bool Length)
{
	Pack::Reset(Length);
}


void UnJce::SkipField(JceStruct::JceStructType type)
{
	switch (type)
	{
	case JceStruct::JceStructType::BYTE:
		GetByte();
		break;
	case JceStruct::JceStructType::SHORT:
		GetShort();
		break;
	case JceStruct::JceStructType::INT:
		GetInt();
		break;
	case JceStruct::JceStructType::LONG:
		GetLong();
		break;
	case JceStruct::JceStructType::FLOAT:
		GetFloat();
		break;
	case JceStruct::JceStructType::DOUBLE:
		GetDouble();
		break;
	case JceStruct::JceStructType::STRING1:
		GetBin(GetByte());
		break;
	case JceStruct::JceStructType::STRING4:
		GetBin(GetInt());
		break;
	case JceStruct::JceStructType::MAP:
	{
		int len = 0;
		Read(len, 0);
		for (size_t i = 0; i < len; i++)
		{
			SkipField(SkipToTag(1));
		}
	}
	break;
	case JceStruct::JceStructType::LIST:
	{
		int len = 0;
		Read(len, 0);
		for (size_t i = 0; i < len; i++)
		{
			SkipField(SkipToTag(0));
		}
	}
	break;
	case JceStruct::JceStructType::STRUCT_BEGIN:
	{
		JceStruct::JceStructType type = SkipToTag(0);
		if (type == JceStruct::JceStructType::STRUCT_END) break;
		else
		{
			SkipField(type);
			if (SkipToTag(0) == JceStruct::JceStructType::STRUCT_END) break;
			else throw "No Jce Struct End";
		}
	}
	break;
	case JceStruct::JceStructType::STRUCT_END:
		break;
	case JceStruct::JceStructType::ZERO_TAG:
		break;
	case JceStruct::JceStructType::SIMPLE_LIST:
	{
		byte type = 0;
		Read(type, 0);
		uint32_t len;
		switch (static_cast<JceStruct::JceStructType>(type))
		{
		case JceStruct::JceStructType::BYTE:
			len = GetByte();
			break;
		case JceStruct::JceStructType::SHORT:
			len = GetShort();
			break;
		case JceStruct::JceStructType::INT:
			len = GetInt();
			break;
		case JceStruct::JceStructType::LONG:
			len = GetLong();
			break;
		case JceStruct::JceStructType::ZERO_TAG:
			return;
		default:
			throw "Not len type";
			break;
		}
		GetBin(len);
	}
	break;
	default:
		throw "UnKnown type";
		break;
	}
}

JceStruct::JceStructType UnJce::SkipToTag(const byte tag)
{
	while (GetLeftLength())
	{
		byte b = GetByte();
		byte t = b & 0xF0;
		if (t == 0XF0)
		{
			t = GetByte();
			if (t == tag) return static_cast<JceStruct::JceStructType>(b & 0x0F);
		}
		else if (t >> 4 == tag) return static_cast<JceStruct::JceStructType>(b & 0x0F);
		SkipField(static_cast<JceStruct::JceStructType>(b & 0x0F));
	}
	throw "No this tag";
}

void UnJce::Reset(const LPBYTE buffer)
{
	UnPack::Reset(buffer);
}

void UnJce::Reset(const byte* buffer, const uint32_t bufferlen)
{
	UnPack::Reset(buffer, bufferlen);
}

void UnJce::Read(float& f, const byte tag)
{
	if (SkipToTag(tag) != JceStruct::JceStructType::FLOAT) throw "type error";
	f = 0.0f;
}

void UnJce::Read(double& d, const byte tag)
{
	if (SkipToTag(tag) != JceStruct::JceStructType::DOUBLE) throw "type error";
	d = 0.0;
}

/// <summary>
/// read STRING1&STRING4
/// </summary>
/// <param name="str">用完记得delete</param>
/// <param name="tag"></param>
void UnJce::Read(char*& str, const byte tag)
{
	uint32_t len;
	switch (SkipToTag(tag))
	{
	case JceStruct::JceStructType::STRING1:
		len = GetByte();
		break;
	case JceStruct::JceStructType::STRING4:
		len = GetInt();
		break;
	default:
		throw "not str type";
		return;
	};
	str = new char[len + 1];
	memcpy(str, GetStr(len), len);
	str[len] = 0;
}

void UnJce::Read(UnJce& UnJce, const byte tag)
{
	if (SkipToTag(tag) != JceStruct::JceStructType::STRUCT_BEGIN) throw "type error";
	const byte* Start = GetCurrentPoint();
	JceStruct::JceStructType type = SkipToTag(0);
	if (type == JceStruct::JceStructType::STRUCT_END) UnJce.Reset(Start, GetCurrentPoint() - Start - 1);
	else
	{
		SkipField(type);
		if (SkipToTag(0) == JceStruct::JceStructType::STRUCT_END) UnJce.Reset(Start, GetCurrentPoint() - Start - 1);
		else throw "No Jce Struct End";
	}
}

/// <summary>
/// read SIMPLE_LIST
/// </summary>
/// <param name="bin">用完记得delete</param>
/// <param name="tag"></param>
void UnJce::Read(LPBYTE& bin, const byte tag)
{
	if (SkipToTag(tag) != JceStruct::JceStructType::SIMPLE_LIST) throw "type error";
	byte type = 0;
	Read(type, 0);
	int len;
	switch (static_cast<JceStruct::JceStructType>(type))
	{
	case JceStruct::JceStructType::BYTE:
		len = GetByte();
		break;
	case JceStruct::JceStructType::SHORT:
		len = GetShort();
		break;
	case JceStruct::JceStructType::INT:
		len = GetInt();
		break;
	case JceStruct::JceStructType::LONG:
		len = GetLong();
		break;
	case JceStruct::JceStructType::ZERO_TAG:
		return;
	default:
		throw "Not len type";
		break;
	}
	bin = new byte[len + 4];
	memcpy(bin, XBin::Int2Bin(len + 4), 4);
	memcpy(bin + 4, GetBin(len), len);
}
