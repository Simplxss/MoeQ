#pragma once

#include <vector>
#include <chrono>
#include <random>
#include <iostream>

#if defined(_WIN_PLATFORM_)
#include <windows.h>
#include <tchar.h>
#endif

#if defined(_LINUX_PLATFORM_)
#include <iconv.h>
#endif

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

    void MD5(const byte *bin, const size_t length, byte* md5);
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
	std::wstring AnsiToUnicode(const char *str, const int Length);
	std::string UnicodeToAnsi(const wchar_t *str, const int Length);
	std::wstring Utf8ToUnicode(const char8_t *str, const int Length);
	std::u8string UnicodeToUtf8(const wchar_t *str, const int Length);

	inline std::wstring AnsiToUnicode(const char *str)
	{
		return AnsiToUnicode(str, strlen(str));
	}
	inline std::string UnicodeToAnsi(const wchar_t *str)
	{
		return UnicodeToAnsi(str, wcslen(str));
	}
	inline std::wstring Utf8ToUnicode(const char8_t *str)
	{
		return Utf8ToUnicode(str, strlen((char *)str));
	}
	inline std::u8string UnicodeToUtf8(const wchar_t *str)
	{
		return UnicodeToUtf8(str, wcslen(str));
	}

	inline std::wstring AnsiToUnicode(const std::string *str)
	{
		return AnsiToUnicode(str->c_str(), str->length());
	}
	inline std::string UnicodeToAnsi(const std::wstring *str)
	{
		return UnicodeToAnsi(str->c_str(), str->length());
	};
	inline std::wstring Utf8ToUnicode(const std::u8string *str)
	{
		return Utf8ToUnicode(str->c_str(), str->length());
	};
	inline std::u8string UnicodeToUtf8(const std::wstring *str)
	{
		return UnicodeToUtf8(str->c_str(), str->length());
	};

	inline std::string Utf8ToAnsi(const char8_t *str, const int Length)
	{
		std::wstring temp = Utf8ToUnicode(str, Length);
		return UnicodeToAnsi(&temp);
	}
	inline std::u8string AnsiToUtf8(const char *str, const int Length)
	{
		std::wstring temp = AnsiToUnicode(str, Length);
		return UnicodeToUtf8(&temp);
	}

	inline std::string Utf8ToAnsi(const char8_t *str)
	{
		return Utf8ToAnsi(str, strlen((char*)str));
	};
	inline std::u8string AnsiToUtf8(const char *str)
	{
		return AnsiToUtf8(str, strlen(str));
	};

	inline std::string Utf8ToAnsi(const std::u8string *str)
	{
		return Utf8ToAnsi(str->c_str(), str->length());
	};
	inline std::u8string AnsiToUtf8(const std::string *str)
	{
		return AnsiToUtf8(str->c_str(), str->length());
	};
}

namespace BigInteger
{
	bool AddOne(byte *BigInteger, int len);
}
