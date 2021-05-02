#include "Pack.h"

ByteInputStream::ByteInputStream(const byte *buffer)
{
	Buffer = buffer;
	Offset = 0;
}

bool ByteInputStream::Check(const uint32_t len, const uint32_t i)
{
	return len >= Offset + i;
}

void ByteInputStream::Set(const byte *buffer)
{
	Buffer = buffer;
	Offset = 0;
}

void ByteInputStream::Skip(uint32_t i)
{
	Offset += i;
}

uint8_t ByteInputStream::GetByte()
{
	return Buffer[Offset++];
}

uint16_t ByteInputStream::GetShort()
{
	uint16_t i;
	i = Buffer[Offset] << 8;
	i |= Buffer[++Offset];
	++Offset;
	return i;
}

uint32_t ByteInputStream::GetInt()
{
	uint32_t i;
	i = Buffer[Offset] << 24;
	i |= Buffer[++Offset] << 16;
	i |= Buffer[++Offset] << 8;
	i |= Buffer[++Offset];
	++Offset;
	return i;
}

uint64_t ByteInputStream::GetLong()
{
	uint64_t i;
	i = (uint64_t)Buffer[Offset] << 56;
	i |= (uint64_t)Buffer[++Offset] << 48;
	i |= (uint64_t)Buffer[++Offset] << 40;
	i |= (uint64_t)Buffer[++Offset] << 32;
	i |= (uint64_t)Buffer[++Offset] << 24;
	i |= (uint64_t)Buffer[++Offset] << 16;
	i |= (uint64_t)Buffer[++Offset] << 8;
	i |= (uint64_t)Buffer[++Offset];
	++Offset;
	return i;
}

float ByteInputStream::GetFloat()
{
	return 0.0f;
}

double ByteInputStream::GetDouble()
{
	return 0.0;
}

const byte *ByteInputStream::GetBin(const uint32_t len)
{
	uint32_t tmp = Offset;
	ByteInputStream::Skip(len);
	return Buffer + tmp;
}

const byte *ByteInputStream::GetCurrentPoint()
{
	return Buffer + Offset;
}

uint32_t ByteInputStream::GetReadedLength()
{
	return Offset;
}

void UnPack::Reset(const byte *buffer, const uint32_t bufferlen)
{
	ByteInputStream::Set(buffer);
	BufferLen = bufferlen;
}

//自动跳长度
void UnPack::Reset(const LPBYTE buffer)
{
	ByteInputStream::Set(buffer);
	ByteInputStream::Skip(4);
	BufferLen = XBin::Bin2Int(buffer);
}

void UnPack::Reset(const std::vector<byte> *buffer)
{
	ByteInputStream::Set((*buffer).data());
	BufferLen = (*buffer).size();
}

uint8_t UnPack::GetByte()
{
	if (Check(BufferLen, 1))
		return ByteInputStream::GetByte();
	return 0;
}

uint16_t UnPack::GetShort()
{
	if (Check(BufferLen, 2))
		return ByteInputStream::GetShort();
	return 0;
}

uint32_t UnPack::GetInt()
{
	if (Check(BufferLen, 4))
		return ByteInputStream::GetInt();
	return 0;
}

uint64_t UnPack::GetLong()
{
	if (Check(BufferLen, 8))
		return ByteInputStream::GetLong();
	return 0;
}

float UnPack::GetFloat()
{
	if (Check(BufferLen, 4))
		return ByteInputStream::GetFloat();
	return 0;
}

double UnPack::GetDouble()
{
	if (Check(BufferLen, 8))
		return ByteInputStream::GetDouble();
	return 0;
}

const char *UnPack::GetStr(const uint32_t len)
{
	if (Check(BufferLen, len))
		return (const char *)ByteInputStream::GetBin(len);
	return 0;
}

const byte *UnPack::GetBin(const uint32_t len)
{
	if (Check(BufferLen, len))
		return ByteInputStream::GetBin(len);
	return 0;
}

const LPBYTE UnPack::GetBin()
{
	uint32_t len = UnPack::GetInt() - 4;
	if (Check(BufferLen, len))
		return (const LPBYTE)(ByteInputStream::GetBin(len) - 4);
	return 0;
}

uint32_t UnPack::GetLeftLength()
{
	return BufferLen - ByteInputStream::GetReadedLength();
}

ByteOutputStream::ByteOutputStream(byte *buffer)
{
	Buffer = buffer;
	Offset = 0;
}

bool ByteOutputStream::Check(const uint32_t len, const uint32_t i)
{
	return len >= Offset + i;
}

void ByteOutputStream::Reset()
{
	Offset = 0;
}

void ByteOutputStream::Set(byte *buffer)
{
	Buffer = buffer;
}

void ByteOutputStream::Skip(const uint32_t i)
{
	Offset += i;
}

void ByteOutputStream::SetByte(const uint8_t i)
{
	Buffer[Offset++] = i;
}

void ByteOutputStream::SetShort(const uint16_t i)
{
	Buffer[Offset] = i >> 8;
	Buffer[++Offset] = i;
	++Offset;
}

void ByteOutputStream::SetInt(const uint32_t i)
{
	Buffer[Offset] = i >> 24;
	Buffer[++Offset] = i >> 16;
	Buffer[++Offset] = i >> 8;
	Buffer[++Offset] = i;
	++Offset;
}

void ByteOutputStream::SetLong(const uint64_t i)
{
	Buffer[Offset] = i >> 56;
	Buffer[++Offset] = i >> 48;
	Buffer[++Offset] = i >> 40;
	Buffer[++Offset] = i >> 32;
	Buffer[++Offset] = i >> 24;
	Buffer[++Offset] = i >> 16;
	Buffer[++Offset] = i >> 8;
	Buffer[++Offset] = i;
	++Offset;
}

void ByteOutputStream::SetFloat(const float i)
{
	Buffer[Offset] = (uint32_t)i >> 24;
	Buffer[++Offset] = (uint32_t)i >> 16;
	Buffer[++Offset] = (uint16_t)i >> 8;
	Buffer[++Offset] = (uint8_t)i;
	++Offset;
}

void ByteOutputStream::SetDouble(const double i)
{
	Buffer[Offset] = (uint64_t)i >> 56;
	Buffer[++Offset] = (uint64_t)i >> 48;
	Buffer[++Offset] = (uint64_t)i >> 40;
	Buffer[++Offset] = (uint64_t)i >> 32;
	Buffer[++Offset] = (uint32_t)i >> 24;
	Buffer[++Offset] = (uint32_t)i >> 16;
	Buffer[++Offset] = (uint16_t)i >> 8;
	Buffer[++Offset] = (uint8_t)i;
	++Offset;
}

void ByteOutputStream::SetBin(const byte *bin, const uint32_t len)
{
	memcpy(Buffer + Offset, bin, len);
	Offset += len;
}

//带长度写入
void ByteOutputStream::SetBin(const LPBYTE bin)
{
	memcpy(Buffer + Offset, bin, XBin::Bin2Int(bin));
	Offset += XBin::Bin2Int(bin);
}

void ByteOutputStream::SetMD5(const byte *bin, const size_t length)
{
	Utils::MD5(bin, length, Buffer + Offset);
	Offset += 16;
}

byte *ByteOutputStream::GetCurrentPoint()
{
	return Buffer + Offset;
}

uint32_t ByteOutputStream::Length()
{
	return Offset;
}

byte *ByteOutputStream::GetAll()
{
	return Buffer;
}

uint32_t ByteOutputStream::GetAll(byte *&buf)
{
	buf = Buffer;
	return Offset;
}

void Pack::CheckBufferLen(uint32_t len)
{
	if (!Check(BufferLen, len))
		Expansion(!Check(BufferLen + 300, len) ? len : 300);
}

void Pack::SetLength()
{
	uint32_t len = ByteOutputStream::Length();
	byte *Buffer = ByteOutputStream::GetAll();
	Buffer[0] = len >> 24;
	Buffer[1] = len >> 16;
	Buffer[2] = len >> 8;
	Buffer[3] = len;
}

void Pack::Expansion(uint32_t len)
{
	BufferLen += len;
	byte *tmp = new byte[BufferLen];
	memcpy(tmp, ByteOutputStream::GetAll(), ByteOutputStream::Length());
	delete[] ByteOutputStream::GetAll();
	ByteOutputStream::Set(tmp);
}

void Pack::Reset(bool Length = false)
{
	Reset();
	if (Length)
		ByteOutputStream::Skip(4);
}

void Pack::SetByte(const uint8_t i)
{
	CheckBufferLen(1);
	ByteOutputStream::SetByte(i);
}

void Pack::SetShort(const uint16_t i)
{
	CheckBufferLen(2);
	ByteOutputStream::SetShort(i);
}

void Pack::SetInt(const uint32_t i)
{
	CheckBufferLen(4);
	ByteOutputStream::SetInt(i);
}

void Pack::SetLong(const uint64_t i)
{
	CheckBufferLen(8);
	ByteOutputStream::SetLong(i);
}

void Pack::SetFloat(const float i)
{
	CheckBufferLen(4);
	ByteOutputStream::SetFloat(i);
}

void Pack::SetDouble(const double i)
{
	CheckBufferLen(8);
	ByteOutputStream::SetDouble(i);
}

void Pack::SetStr(const char *str)
{
	unsigned int len = strlen(str);
	CheckBufferLen(len);
	ByteOutputStream::SetBin((byte *)str, len);
}

void Pack::SetStr_(const char *str)
{
	unsigned int len = strlen(str);
	CheckBufferLen(len);
	ByteOutputStream::SetBin((byte *)str, len);
	delete str;
}

void Pack::SetBin(const byte *bin, const uint32_t len)
{
	CheckBufferLen(len);
	ByteOutputStream::SetBin(bin, len);
}

//带长度写入
void Pack::SetBin(const LPBYTE bin)
{
	CheckBufferLen(XBin::Bin2Int(bin));
	ByteOutputStream::SetBin(bin);
}

void Pack::SetBin(const std::vector<byte> *bin)
{
	uint32_t len = (*bin).size();
	CheckBufferLen(len);
	ByteOutputStream::SetBin((*bin).data(), len);
}

//会自动delete参数
void Pack::SetBin_(const byte *bin, const uint32_t len)
{
	CheckBufferLen(len);
	ByteOutputStream::SetBin(bin, len);
	delete[] bin;
}

//带长度写入,会自动delete参数
void Pack::SetBin_(const LPBYTE bin)
{
	CheckBufferLen(XBin::Bin2Int(bin));
	ByteOutputStream::SetBin(bin);
	delete[] bin;
}

//申请新的内存返回且清空
byte *Pack::GetAll_(bool Length)
{
	byte *bin = new byte[ByteOutputStream::Length()];
	memcpy(bin, ByteOutputStream::GetAll(), ByteOutputStream::Length());
	ByteOutputStream::Reset();
	if (Length)
		ByteOutputStream::Skip(4);
	return bin;
}

uint32_t Pack::GetAll_(byte *&bin, bool Length)
{
	uint32_t len = ByteOutputStream::Length();
	bin = new byte[len];
	memcpy(bin, ByteOutputStream::GetAll(), len);
	ByteOutputStream::Reset();
	if (Length)
		ByteOutputStream::Skip(4);
	return len;
}

uint32_t Pack::GetLeftSpace()
{
	return BufferLen - ByteOutputStream::Length();
}

void TlvPack::SetByte(const uint8_t i)
{
	if (Check(BufferLen, 1))
		ByteOutputStream::SetByte(i);
}

void TlvPack::SetShort(const uint16_t i)
{
	if (Check(BufferLen, 2))
		ByteOutputStream::SetShort(i);
}

void TlvPack::SetInt(const uint32_t i)
{
	if (Check(BufferLen, 4))
		ByteOutputStream::SetInt(i);
}

void TlvPack::SetLong(const uint64_t i)
{
	if (Check(BufferLen, 8))
		ByteOutputStream::SetLong(i);
}

void TlvPack::SetStr(const char *str)
{
	if (Check(BufferLen, strlen(str)))
		ByteOutputStream::SetBin((byte *)str, strlen(str));
}

void TlvPack::SetBin(const byte *bin, const uint32_t len)
{
	if (Check(BufferLen, len))
		ByteOutputStream::SetBin(bin, len);
}

void TlvPack::SetBin(const LPBYTE bin)
{
	if (Check(BufferLen, XBin::Bin2Int(bin)))
		ByteOutputStream::SetBin(bin, XBin::Bin2Int(bin));
}

void TlvPack::SetBin(const std::vector<byte> *bin)
{
	uint32_t len = (*bin).size();
	if (Check(BufferLen, len))
		ByteOutputStream::SetBin((*bin).data(), len);
}

void TlvPack::SetBin_(const byte *bin, const uint32_t len)
{
	if (Check(BufferLen, len))
		ByteOutputStream::SetBin(bin, len);
	delete[] bin;
}

void TlvPack::SetBin_(const LPBYTE bin)
{
	if (Check(BufferLen, XBin::Bin2Int(bin)))
		ByteOutputStream::SetBin(bin, XBin::Bin2Int(bin));
	delete[] bin;
}

void TlvPack::SetBinEx_(const LPBYTE bin)
{
	if (Check(BufferLen, XBin::Bin2Int(bin) - 4))
		ByteOutputStream::SetBin(bin + 4, XBin::Bin2Int(bin) - 4);
	delete[] bin;
}

void TlvPack::SetMD5(const byte *bin, const size_t length)
{
	if (Check(BufferLen, 16))
		ByteOutputStream::SetMD5(bin, length);
}

uint16_t TlvPack::Pack(const unsigned short cmd)
{
	uint32_t len = ByteOutputStream::Length() - 4; //去掉头
	byte *Buffer = ByteOutputStream::GetAll();
	Buffer[0] = cmd >> 8;
	Buffer[1] = cmd;
	Buffer[2] = len >> 8;
	Buffer[3] = len;
	return len + 4;
}