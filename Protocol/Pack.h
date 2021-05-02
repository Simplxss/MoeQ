#pragma once
#include "Utils.h"

class ByteInputStream
{
private:
	const byte* Buffer;
	uint32_t Offset;
public:
	ByteInputStream(const byte* buffer);
public:
	bool Check(const uint32_t len, const uint32_t i);
	void Set(const byte* buffer);
	void Skip(const uint32_t i);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const byte* GetBin(const uint32_t len);
	const byte* GetCurrentPoint();
	uint32_t GetReadedLength();
};

class UnPack :public ByteInputStream
{
private:
	uint32_t BufferLen;
public:
	UnPack(const byte* buffer, const uint32_t bufferlen) :ByteInputStream(buffer)
	{
		BufferLen = bufferlen;
	};
	UnPack(const LPBYTE buffer) :ByteInputStream(buffer)//自动跳掉长度
	{
		ByteInputStream::Skip(4);
		BufferLen = XBin::Bin2Int(buffer);
	};
public:
	void Reset(const byte* buffer, const uint32_t bufferlen);
	void Reset(const LPBYTE buffer);
	void Reset(const std::vector<byte>* buffer);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const char* GetStr(const uint32_t len);
	const byte* GetBin(const uint32_t len);
	const LPBYTE GetBin();
	uint32_t GetLeftLength();
};

class ByteOutputStream
{
private:
	byte* Buffer;
	uint32_t Offset;
public:
	ByteOutputStream(byte* buffer);
public:
	bool Check(const uint32_t len, const uint32_t i);
	void Reset();
	void Set(byte* buffer);
	void Skip(const uint32_t i);
	void SetByte(const uint8_t i);
	void SetShort(const uint16_t i);
	void SetInt(const uint32_t i);
	void SetLong(const uint64_t i);
	void SetFloat(const float i);
	void SetDouble(const double i);
	void SetBin(const byte* bin, const uint32_t len);
	void SetBin(const LPBYTE bin);
	void SetMD5(const byte *bin, const size_t length);
	byte* GetCurrentPoint();
	uint32_t Length();
	byte* GetAll();
	uint32_t GetAll(byte*& buf);
};

class Pack :public ByteOutputStream
{
private:
	uint32_t BufferLen;
public:
	Pack(const uint32_t bufferlen = 300, bool Length = false) :ByteOutputStream(new byte[bufferlen])
	{
		if (Length) ByteOutputStream::Skip(4);
		BufferLen = bufferlen;
	};
public:
	void CheckBufferLen(uint32_t len);
	void SetLength();
	void Expansion(uint32_t len);
	void Reset(bool Length);
	void SetByte(const uint8_t i);
	void SetShort(const uint16_t i);
	void SetInt(const uint32_t i);
	void SetLong(const uint64_t i);
	void SetFloat(const float i);
	void SetDouble(const double i);
	void SetStr(const char* str);
	void SetStr_(const char* str);
	void SetBin(const byte* bin, const uint32_t len);
	void SetBin(const LPBYTE bin);
	void SetBin(const std::vector<byte>* bin);
	void SetBin_(const byte* bin, const uint32_t len);
	void SetBin_(const LPBYTE bin);
	byte* GetAll_(bool Length = false);
	uint32_t GetAll_(byte*& bin, bool Length = false);
	uint32_t GetLeftSpace();
};

class TlvPack :public ByteOutputStream
{
private:
	uint32_t BufferLen;
public:
	TlvPack(byte* ByteStream, const uint32_t bufferlen) :ByteOutputStream(ByteStream)
	{
		ByteOutputStream::Skip(4);
		BufferLen = bufferlen;
	};
public:
	void SetByte(const uint8_t i);
	void SetShort(const uint16_t i);
	void SetInt(const uint32_t i);
	void SetLong(const uint64_t i);
	void SetStr(const char* str);
	void SetBin(const byte* bin, const uint32_t len);
	void SetBin(const LPBYTE bin);
	void SetBin(const std::vector<byte>* bin);
	void SetBin_(const byte* bin, const uint32_t len);
	void SetBin_(const LPBYTE bin);
	void SetBinEx_(const LPBYTE bin);
	void SetMD5(const byte *bin, const size_t length);
	uint16_t Pack(const unsigned short cmd);
};
