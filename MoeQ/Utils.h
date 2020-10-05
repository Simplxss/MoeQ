#pragma once

static UINT NEAR WM_CREATE_WKE_WINDOWS = RegisterWindowMessage(_T("CREATE_WKE_WINDOWS"));

namespace Utils
{
	struct ECDHKEY
	{
		byte sharekey[24];
		byte pubkey[25];
		byte prikey[29];//Warning:Maybe only 28 bytes
	};
	uint64_t GetRandom(const uint64_t mini = 0, const uint64_t max = 9223372036854775807);
	char* GetRandomLetter(const uint length);
	byte* GetRandomBin(const uint length);

	byte* MD5(const byte* bin, const size_t length);
	byte* Sha256(const byte* bin, const size_t length);

	bool Ecdh_Crypt(ECDHKEY& ECDHKEY, const byte* pubkey, const byte pubkeylen);
	byte* Ecdh_CountSharekey(const byte* prikey, const byte publickey[25]);

	uint DES_ECB_Encrypt(byte* _key, byte* data, uint len, byte*& bin);

	long CurrentTimeMillis();

	LPBYTE ZlibCompress(const char* source);
	LPBYTE ZlibCompress(const LPBYTE bin);
	char* ZlibUnCompress(const byte* source, const uint sourceLen);
	LPBYTE ZlibUnCompress(const LPBYTE bin);
};

namespace XBin
{
	byte* Int2Bin(const uint i);
	void Int2Bin(const uint i, byte* bin);
	uint Bin2Short(const byte* bin);
	uint Bin2Int(const byte* bin);
	char* Bin2Hex(const byte* bin, const uint len);
	uint Hex2Bin(char* hex, byte*& bin);
}

namespace Iconv
{
	char* Ansi2Utf8(const char* szA);
	char* Unicode2Ansi(const wchar_t* szU16);
	wchar_t* Ansi2Unicode(const char* szA);
	wchar_t* Utf82Unicode(const char* szU8);
	char* Unicode2Utf8(const wchar_t* szU16);
}

namespace BigInteger
{
	bool AddOne(byte* BigInteger, int len);
}

namespace SildVerification
{
	char* Load(const HWND Parent, const char* Url);
}