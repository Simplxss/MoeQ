#include "pch.h"
#include "Utils.h"

uint64_t Utils::GetRandom(const uint64_t mini, const uint64_t max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int<uint64_t>u(mini, max);
	return u(mt);
}

//大小写混合
char* Utils::GetRandomLetter(const uint length)
{
	const char LetterTable[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O','P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' ,'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o','p' , 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int<int>u(0, 52);
	char* tmp = new char[length + 1];
	for (uint i = 0; i < length; i++)
	{
		tmp[i] = LetterTable[u(mt)];
	}
	return tmp;
}

byte* Utils::GetRandomBin(const uint length)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int<int>u(0, 255);
	byte* tmp = new byte[length];
	for (uint i = 0; i < length; i++)
	{
		tmp[i] = u(mt);
	}
	return tmp;
}

byte* Utils::MD5(const byte* bin, const size_t length)
{
	MD5_CTX ctx;
	byte md5[16];

	MD5_Init(&ctx);
	MD5_Update(&ctx, bin, length);
	MD5_Final(md5, &ctx);
	return md5;
}

byte* Utils::Sha256(const byte* bin, const size_t length)
{
	SHA256_CTX ctx;
	byte sha256[32];
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, bin, length);
	SHA256_Final(sha256, &ctx);
	return sha256;
}

bool Utils::Ecdh_Crypt(ECDHKEY& ECDHKEY, const byte* pubkey, const byte pubkeylen)
{
	int len;
	int ret;
	EC_KEY* ecdh;
	const EC_GROUP* group;
	EC_POINT* p_ecdh2_public;

	//generate key
	ecdh = EC_KEY_new_by_curve_name(711);
	if (ecdh == NULL)
	{
		EC_KEY_free(ecdh);
		throw "Ecdh key by curve name error.";
		return false;
	}
	if (!EC_KEY_generate_key(ecdh))
	{
		EC_KEY_free(ecdh);
		throw "Failed to generate EC key.";
		return false;
	}

	group = EC_KEY_get0_group(ecdh);
	/* 1==> Set ecdh1's public and privat key. */
	if (!EC_POINT_point2oct(group, EC_KEY_get0_public_key(ecdh), POINT_CONVERSION_COMPRESSED, ECDHKEY.pubkey, 25, NULL))
	{
		EC_KEY_free(ecdh);
		throw "EC_POINT oct2point error.";
		return false;
	}

	if (!BN_bn2mpi(EC_KEY_get0_private_key(ecdh), ECDHKEY.prikey))
	{
		EC_KEY_free(ecdh);
		throw "EC_POINT oct2point error.";
		return false;
	}
	/* 2==> Set ecdh2's public key */
	p_ecdh2_public = EC_POINT_new(group);
	if (!EC_POINT_oct2point(group, p_ecdh2_public, pubkey, pubkeylen, NULL))
	{
		EC_POINT_clear_free(p_ecdh2_public);
		EC_KEY_free(ecdh);
		throw "EC_POINT oct2point error.";
		return false;
	}
	EC_KEY_set_public_key(ecdh, p_ecdh2_public);
	/* 3==> Calculate the shared key of ecdh1 and ecdh2 */
	ECDH_compute_key(ECDHKEY.sharekey, 24, p_ecdh2_public, ecdh, NULL);

	EC_POINT_clear_free(p_ecdh2_public);
	EC_KEY_free(ecdh);
	CRYPTO_cleanup_all_ex_data();
	return true;
}

byte* Utils::Ecdh_CountSharekey(const byte* prikey, const byte publickey[25])
{
	int len;
	EC_KEY* ecdh;
	const EC_GROUP* group;
	BIGNUM* p_ecdh1_private;
	EC_POINT* p_ecdh2_public;
	byte* sharekey = new byte[24];

	ecdh = EC_KEY_new_by_curve_name(711);
	p_ecdh1_private = BN_new();
	BN_mpi2bn(prikey, XBin::Bin2Int(prikey) + 4, p_ecdh1_private);
	EC_KEY_set_private_key(ecdh, p_ecdh1_private);
	//BN_free(p_ecdh1_private);
	BN_free(p_ecdh1_private);

	/* 2==> Set ecdh2's public key */
	group = EC_KEY_get0_group(ecdh);
	p_ecdh2_public = EC_POINT_new(group);
	EC_POINT_oct2point(group, p_ecdh2_public, publickey, 25, NULL);

	if (!EC_KEY_set_public_key(ecdh, p_ecdh2_public))
	{
		//CRYPTO_ERR("Ecdh set public key error.");
		goto err;
	}
	/*------------*/

	/* 3==> Calculate the shared key of ecdh1 and ecdh2 */
	len = ECDH_compute_key(sharekey, 24, p_ecdh2_public, ecdh, NULL);
	if (len != 24)
	{
		//CRYPTO_ERR("Ecdh compute key error.");
		goto err;
	}
	EC_POINT_clear_free(p_ecdh2_public);
	goto err;
err:
	EC_KEY_free(ecdh);
	return sharekey;
}

uint Utils::DES_ECB_Encrypt(byte* _key, byte* data, uint len, byte*& bin)
{
	DES_cblock key;
	DES_key_schedule schedule;
	//转换成schedule
	memcpy(key, _key, 8);
	DES_set_odd_parity(&key);
	DES_set_key_unchecked(&key, &schedule);

	int i = 0, j = len / 8 + 1, k = len % 8;
	int nPidding_size = 8 - k;
	char* szArray;
	szArray = (char*)malloc(len + nPidding_size);
	memcpy(szArray, data, len);
	memset(szArray + len, 0, j * 8 - len);
	bin = new byte[j * 8];

	const_DES_cblock sInput;
	DES_cblock sOutput;
	for (int i = 0; i < j; ++i)
	{
		memcpy(sInput, szArray + (i * 8), 8);
		DES_ecb_encrypt(&sInput, &sOutput, &schedule, DES_ENCRYPT);
		memcpy(bin + (i * 8), sOutput, 8);
	}
	delete[] szArray;
	return j * 8;
}

long Utils::CurrentTimeMillis()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

LPBYTE Utils::ZlibCompress(const char* source)
{
	uint sourceLen = strlen(source) - 1;//去掉尾部0
	uLong destLen = compressBound(sourceLen);
	LPBYTE dest = new byte[destLen+4];
	if (compress(dest+4, &destLen, (byte*)source, sourceLen) == 0)
	{
		memcpy(dest, XBin::Int2Bin(destLen + 4), 4);
		return dest;
	}
	else
	{
		delete[] dest;
		return new byte[4];
	}
}

LPBYTE Utils::ZlibCompress(const LPBYTE source)
{
	uint sourceLen = XBin::Bin2Int(source) - 4;
	uLong destLen = compressBound(sourceLen);
	LPBYTE dest = new byte[destLen + 4];
	if (compress(dest + 4, &destLen, source + 4, sourceLen) == 0)
	{
		memcpy(dest, XBin::Int2Bin(destLen + 4), 4);
		return dest;
	}
	else
	{
		delete[] dest;
		return new byte[4];
	}
}

char* Utils::ZlibUnCompress(const byte* source, const uint sourceLen)
{
	uLong destLen = sourceLen * 3;
	byte* dest = new byte[destLen];
	int result = uncompress(dest, &destLen, source, sourceLen);
	while (result == Z_BUF_ERROR)
	{
		delete[] dest;
		destLen += sourceLen * 3;
		dest = new byte[destLen];
		result = uncompress(dest + 4, &destLen, source, sourceLen);
	}
	if (result == 0)
	{
		dest[destLen] = 0;
		return (char*)dest;
	}
	else
	{
		delete[] dest;
		return new char[0];
	}
}

LPBYTE Utils::ZlibUnCompress(const LPBYTE source)
{
	uint sourceLen = XBin::Bin2Int(source) - 4;
	uLong destLen = sourceLen * 3;
	LPBYTE dest = new byte[destLen + 4];
	int result = uncompress(dest + 4, &destLen, source + 4, sourceLen);
	while (result == Z_BUF_ERROR)
	{
		delete[] dest;
		destLen += sourceLen * 3;
		dest = new byte[destLen + 4];
		result = uncompress(dest + 4, &destLen, source + 4, sourceLen);
	}
	if (result == 0)
	{
		memcpy(dest, XBin::Int2Bin(destLen + 4), 4);
		return dest;
	}
	else
	{
		delete[] dest;
		return new byte[4];
	}
}

byte* XBin::Int2Bin(const uint i)
{
	byte* bin = new byte[4];
	bin[0] = i >> 24;
	bin[1] = i >> 16;
	bin[2] = i >> 8;
	bin[3] = (byte)i;
	return bin;
}

void XBin::Int2Bin(const uint i, byte* bin)
{
	bin[0] = i >> 24;
	bin[1] = i >> 16;
	bin[2] = i >> 8;
	bin[3] = (byte)i;
}

uint XBin::Bin2Short(const byte* bin)
{
	return bin[0] << 8 | bin[1];
}

uint XBin::Bin2Int(const byte* bin)
{
	return bin[0] << 24 | bin[1] << 16 | bin[2] << 8 | bin[3];
}

/// <summary>
/// 
/// </summary>
/// <param name="bin"></param>
/// <param name="len"></param>
/// <returns>无空格大写字母</returns>
char* XBin::Bin2Hex(const byte* bin, const uint len)
{
	const char Table[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	char* Hex = new char[(len << 1) + 1];
	Hex[len << 1] = 0;
	for (size_t i = 0; i < len; i++)
	{
		Hex[i << 1] = Table[(bin[i] & 0xf0) >> 4];
		Hex[(i << 1) + 1] = Table[bin[i] & 0x0f];
	}
	return Hex;
}

//传入无空格,大小写无所谓
uint XBin::Hex2Bin(char* hex, byte*& bin)
{
#pragma warning(disable:4996)
	strlwr(hex);
	const byte Table1[] = { 0,1,2,3,4,5,6,7,8,9 };
	const byte Table2[] = { 0xa,0xb,0xc,0xd,0xe,0xf };
	uint len = strlen(hex);
	if (len & 0x1) throw "len error";
	else
	{
		len = len >> 1;
		bin = new byte[len];
		for (size_t i = 0; i < len; i++)
		{
			byte tmp = hex[i << 1] - '0';
			if (tmp < 0)
			{
				throw "not hex";
				return -1;
			}
			else if (tmp < 10) bin[i] = Table1[tmp] << 4;
			else
			{
				tmp = hex[i << 1] - 'a';
				if (tmp < 0)
				{
					throw "not hex";
					return -1;
				}
				else if (tmp < 6) bin[i] = Table2[tmp] << 4;
				else
				{
					throw "not hex";
					return -1;
				}
			}
			tmp = hex[(i << 1) + 1] - '0';
			if (tmp < 0)
			{
				throw "not hex";
				return -1;
			}
			else if (tmp < 10) bin[i] |= Table1[tmp];
			else
			{
				tmp = hex[(i << 1) + 1] - 'a';
				if (tmp < 0)
				{
					throw "not hex";
					return -1;
				}
				else if (tmp < 6) bin[i] |= Table2[tmp];
				else
				{
					throw "not hex";
					return -1;
				}
			}
		}
		return len;
	}
}

/// <summary>
/// Ansi字符串转Utf8
/// </summary>
/// <param name="szA">Ansi字符串</param>
/// <returns>函数内使用了new,记得用delete释放</returns>
char* Iconv::Ansi2Utf8(const char* szA)
{
	wchar_t* szU16 = Ansi2Unicode(szA);
	char* szU8 = Unicode2Utf8(szU16);
	delete[] szU16;
	return szU8;
}

char* Iconv::Unicode2Ansi(const wchar_t* szU16)
{
	uint aLen = ::WideCharToMultiByte(936, NULL, szU16, lstrlenW(szU16), NULL, NULL, NULL, NULL);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	char* szString = new char[aLen + 1];
	//转换
	::WideCharToMultiByte(936, NULL, szU16, lstrlenW(szU16), szString, aLen, NULL, NULL);
	szString[aLen] = '\0';
	return szString;
}

/// <summary>
/// Ansi字符串转Windows Unicode
/// </summary>
/// <param name="szA">Ansi字符串</param>
/// <returns>函数内使用了new,记得用delete释放</returns>
wchar_t* Iconv::Ansi2Unicode(const char* szA)
{
	uint wcsLen = ::MultiByteToWideChar(936, NULL, szA, strlen(szA), NULL, NULL);
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(936, NULL, szA, strlen(szA), wszString, wcsLen);
	wszString[wcsLen] = '\0';
	return wszString;
}

/// <summary>
/// Utf8字符串转Windows Unicode
/// </summary>
/// <param name="szU8">Utf8字符串</param>
/// <returns>函数内使用了new,记得用delete释放</returns>
wchar_t* Iconv::Utf82Unicode(const char* szU8)
{
	uint wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';
	return wszString;
}

/// <summary>
/// Windows Unicode字符串转Utf8
/// </summary>
/// <param name="szU16">Unicode字符串</param>
/// <returns>函数内使用了new,记得用delete释放</returns>
char* Iconv::Unicode2Utf8(const wchar_t* szU16)
{
	uint u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, szU16, lstrlenW(szU16), NULL, NULL, NULL, NULL);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	char* u8String = new char[u8Len + 1];
	//转换
	::WideCharToMultiByte(CP_UTF8, NULL, szU16, lstrlenW(szU16), u8String, u8Len, NULL, NULL);
	//最后加上'\0'
	u8String[u8Len] = '\0';
	return u8String;
}

bool BigInteger::AddOne(byte* BigInteger, int len)
{
	for (size_t i = len - 1; i >= 0; i--)
	{
		if (BigInteger[i] == 0xFF)
		{
			BigInteger[i] = 0;
		}
		else
		{
			BigInteger[i]++;
			return true;
		}
	}
	return false;
}

char* SildVerification::Load(const HWND Parent, const char* Url)
{
	return (char*)SendMessage(Parent, WM_CREATE_WKE_WINDOWS, NULL, (LPARAM)Url);
};