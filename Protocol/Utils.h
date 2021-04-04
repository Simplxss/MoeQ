#pragma once

#include <vector>
#include <chrono>
#include <random>
#include <locale>
#include <codecvt>
#include <iostream>

#include <tchar.h>

#include <zlib.h>
#include <sqlite3.h>
#include <openssl\sha.h>
#include <openssl\md5.h>
#include <openssl\ecdh.h>
#include <openssl\des.h>
#include "..\include\rapidjson\document.h"

#include "Defined.h"

namespace Utils
{
	struct ECDHKEY
	{
		byte sharekey[24];
		byte pubkey[25];
		byte prikey[29]; //Warning:Maybe only 28 bytes
	};
	uint64_t GetRandom(const uint64_t mini = 0, const uint64_t max = 9223372036854775807);
	char *GetRandomLetter(const uint length);
	byte *GetRandomBin(const uint length);

	byte *MD5(const byte *bin, const size_t length);
	LPBYTE MD5EX(const byte *bin, const size_t length);
	byte *Sha256(const byte *bin, const size_t length);

	bool Ecdh_Crypt(ECDHKEY &ECDHKEY, const byte *pubkey, const byte pubkeylen);
	byte *Ecdh_CountSharekey(const byte *prikey, const byte publickey[25]);

	uint DES_ECB_Encrypt(byte *_key, byte *data, uint len, byte *&bin);

	long CurrentTimeMillis();

	LPBYTE ZlibCompress(const char *source);
	LPBYTE ZlibCompress(const LPBYTE bin);
	char *ZlibUnCompress(const byte *source, const uint sourceLen);
	LPBYTE ZlibUnCompress(const LPBYTE bin);
};

namespace XBin
{
	byte *Int2Bin(const uint i);
	void Int2Bin(const uint i, byte *bin);
	char *Int2IP(const uint i);
	byte *IP2Bin(const char *IP);
	uint Bin2Short(const byte *bin);
	uint Bin2Int(const byte *bin);
	char *Bin2HexEx(const byte *bin, const uint len);
	uint Hex2Bin(const char *hex, byte *&bin);
	uint Hex2BinEx(const char *hex, byte *&bin);
}

namespace Iconv
{
	std::u8string Ansi2Utf8(const std::string *str);
	std::string Utf82Ansi(const std::u8string *str);
	std::wstring Ansi2Unicode(const std::string *str);
	std::string Unicode2Ansi(const std::wstring *str);
	std::wstring Utf82Unicode(const std::u8string *str);
	std::u8string Unicode2Utf8(const std::wstring *str);

    inline std::u8string Ansi2Utf8(const char *str)
	{
		std::string temp(str);
		return Ansi2Utf8(&temp);
	};
	inline std::string Utf82Ansi(const char8_t *str)
	{
		std::u8string temp(str);
		return Utf82Ansi(&temp);
	};
	inline std::wstring Ansi2Unicode(const char *str)
	{
		std::string temp(str);
		return Ansi2Unicode(&temp);
	};
	inline std::string Unicode2Ansi(const wchar_t *str)
	{
		std::wstring temp(str);
		return Unicode2Ansi(&temp);
	};
	inline std::wstring Utf82Unicode(const char8_t *str)
	{
		std::u8string temp(str);
		return Utf82Unicode(&temp);
	};
	inline std::u8string Unicode2Utf8(const wchar_t *str)
	{
		std::wstring temp(str);
		return Unicode2Utf8(&temp);
	};
}

namespace BigInteger
{
	bool AddOne(byte *BigInteger, int len);
}
