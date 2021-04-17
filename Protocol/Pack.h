#pragma once
#include "Utils.h"

class ByteInputStream
{
private:
	const byte* Buffer;
	uint Offset;
public:
	ByteInputStream(const byte* buffer);
public:
	bool Check(const uint len, const uint i);
	void Set(const byte* buffer);
	void Skip(const uint i);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const byte* GetBin(const uint len);
	const byte* GetCurrentPoint();
	uint GetReadedLength();
};

class UnPack :public ByteInputStream
{
private:
	uint BufferLen;
public:
	UnPack(const byte* buffer, const uint bufferlen) :ByteInputStream(buffer)
	{
		BufferLen = bufferlen;
	};
	UnPack(const LPBYTE buffer) :ByteInputStream(buffer)//自动跳掉长度
	{
		ByteInputStream::Skip(4);
		BufferLen = XBin::Bin2Int(buffer);
	};
public:
	void Reset(const byte* buffer, const uint bufferlen);
	void Reset(const LPBYTE buffer);
	void Reset(const std::vector<byte>* buffer);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const char* GetStr(const uint len);
	const byte* GetBin(const uint len);
	const LPBYTE GetBin();
	uint GetLeftLength();
};

class ByteOutputStream
{
private:
	byte* Buffer;
	uint Offset;
public:
	ByteOutputStream(byte* buffer);
public:
	bool Check(const uint len, const uint i);
	void Reset();
	void Set(byte* buffer);
	void Skip(const uint i);
	void SetByte(const uint8_t i);
	void SetShort(const uint16_t i);
	void SetInt(const uint32_t i);
	void SetLong(const uint64_t i);
	void SetFloat(const float i);
	void SetDouble(const double i);
	void SetBin(const byte* bin, const uint len);
	void SetBin(const LPBYTE bin);
	void SetMD5(const byte *bin, const size_t length);
	byte* GetCurrentPoint();
	uint Length();
	byte* GetAll();
	uint GetAll(byte*& buf);
};

class Pack :public ByteOutputStream
{
private:
	uint BufferLen;
public:
	Pack(const uint bufferlen = 300, bool Length = false) :ByteOutputStream(new byte[bufferlen])
	{
		if (Length) ByteOutputStream::Skip(4);
		BufferLen = bufferlen;
	};
public:
	void CheckBufferLen(uint len);
	void SetLength();
	void Expansion(uint len);
	void Reset(bool Length);
	void SetByte(const uint8_t i);
	void SetShort(const uint16_t i);
	void SetInt(const uint32_t i);
	void SetLong(const uint64_t i);
	void SetFloat(const float i);
	void SetDouble(const double i);
	void SetStr(const char* str);
	void SetStr_(const char* str);
	void SetBin(const byte* bin, const uint len);
	void SetBin(const LPBYTE bin);
	void SetBin(const std::vector<byte>* bin);
	void SetBin_(const byte* bin, const uint len);
	void SetBin_(const LPBYTE bin);
	byte* GetAll_(bool Length = false);
	uint GetAll_(byte*& bin, bool Length = false);
	uint GetLeftSpace();
};

class TlvPack :public ByteOutputStream
{
private:
	uint BufferLen;
public:
	TlvPack(byte* ByteStream, const uint bufferlen) :ByteOutputStream(ByteStream)
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
	void SetBin(const byte* bin, const uint len);
	void SetBin(const LPBYTE bin);
	void SetBin(const std::vector<byte>* bin);
	void SetBin_(const byte* bin, const uint len);
	void SetBin_(const LPBYTE bin);
	void SetBinEx_(const LPBYTE bin);
	void SetMD5(const byte *bin, const size_t length);
	uint16_t Pack(const unsigned short cmd);
};
