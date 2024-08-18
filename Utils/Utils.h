#pragma once

#include <chrono>
#include <random>
#include <iostream>

#include <zlib.h>
#include <sqlite3.h>
#include <openssl/ecdh.h>
#include <openssl/evp.h>

#include "../include/rapidjson/document.h"

#if defined(_WIN_PLATFORM_)
#include <tchar.h>
#include <stringapiset.h>
#endif

typedef unsigned char byte;
typedef unsigned int uint;
typedef byte *LPBYTE;

namespace Utils
{
	struct ECDHKEY
	{
		const BIGNUM *prikey;
		byte pubkey[100];
		int pubkeyLen;
		byte sharekey[100];
		int sharekeyLen;
	};
	uint64_t GetRandom(const uint64_t mini = 0, const uint64_t max = 9223372036854775807);
	char *GetRandomLetter(const uint length);
	byte *GetRandomBin(const uint length);

	void MD5(const byte *bin, const size_t length, byte *md5);
	byte *MD5(const byte *bin, const size_t length);
	LPBYTE MD5EX(const byte *bin, const size_t length);
	
	void Sha256(const byte *bin, const size_t length, byte *sha256);
	byte *Sha256(const byte *bin, const size_t length);

	bool Ecdh_Crypt(ECDHKEY &ECDHKEY, byte *SvrPubKey, int SvrPubKeyLen);
	bool Ecdh_CountSharekey(ECDHKEY &ECDHKEY);

	std::pair<std::vector<byte>, std::vector<byte>> Aes_256_Gcm_Encrypt(const std::vector<byte> &data, const std::vector<byte> &aad, const byte key[32], const byte iv[16]);

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
	char *Bin2Hex(const byte *bin, const uint len);
	char *Bin2HexEx(const byte *bin, const uint len);
	uint Hex2Bin(const char *hex, byte *&bin);
	uint Hex2BinEx(const char *hex, byte *&bin);
}

#if defined(_WIN_PLATFORM_)
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
		return Utf8ToAnsi(str, strlen((char *)str));
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
#endif

namespace BigInteger
{
	bool Add(byte *BigInteger, int len, int value);
	bool AddOne(byte *BigInteger, int len);
}
