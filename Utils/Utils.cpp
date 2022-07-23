#include "Utils.h"

uint64_t Utils::GetRandom(const uint64_t mini, const uint64_t max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<uint64_t> u(mini, max);
    return u(mt);
}

//大小写混合
char *Utils::GetRandomLetter(const uint length)
{
    const char LetterTable[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> u(0, 52);
    char *tmp = new char[length + 1];
    for (uint i = 0; i < length; i++)
    {
        tmp[i] = LetterTable[u(mt)];
    }
    tmp[length] = 0;
    return tmp;
}

byte *Utils::GetRandomBin(const uint length)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> u(0, 255);
    byte *tmp = new byte[length];
    for (uint i = 0; i < length; i++)
    {
        tmp[i] = u(mt);
    }
    return tmp;
}

void Utils::MD5(const byte *bin, const size_t length, byte *md5)
{
    MD5_CTX ctx;

    MD5_Init(&ctx);
    MD5_Update(&ctx, bin, length);
    MD5_Final(md5, &ctx);
}

byte *Utils::MD5(const byte *bin, const size_t length)
{
    MD5_CTX ctx;
    byte *md5 = new byte[16];

    MD5_Init(&ctx);
    MD5_Update(&ctx, bin, length);
    MD5_Final(md5, &ctx);
    return md5;
}

LPBYTE Utils::MD5EX(const byte *bin, const size_t length)
{
    MD5_CTX ctx;
    byte *md5 = new byte[20];
    memcpy(md5, "\0\0\0\x14", 4);

    MD5_Init(&ctx);
    MD5_Update(&ctx, bin, length);
    MD5_Final(md5 + 4, &ctx);
    return md5;
}

void Utils::Sha256(const byte *bin, const size_t length, byte *sha256)
{
    SHA256_CTX ctx;

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, bin, length);
    SHA256_Final(sha256, &ctx);
}

byte *Utils::Sha256(const byte *bin, const size_t length)
{
    SHA256_CTX ctx;
    byte *sha256 = new byte[32];
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, bin, length);
    SHA256_Final(sha256, &ctx);
    return sha256;
}

bool Utils::Ecdh_Crypt(ECDHKEY &ECDHKEY, byte* SvrPubKey, int SvrPubKeyLen)
{
    int len;
    int ret;
    EC_KEY *ecdh;
    const EC_GROUP *group;
    EC_POINT *p_ecdh2_public;

    // ecdh = EC_KEY_new_by_curve_name(NID_secp192k1); //old

    ecdh = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1); // new

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

    if (!(ECDHKEY.pubkeyLen = EC_POINT_point2oct(group, EC_KEY_get0_public_key(ecdh), POINT_CONVERSION_UNCOMPRESSED, ECDHKEY.pubkey, 100, NULL)))
    {
        EC_KEY_free(ecdh);
        throw "EC_POINT oct2point error.";
        return false;
    }

    if (!(ECDHKEY.prikey = EC_KEY_get0_private_key(ecdh)))
    {
        EC_KEY_free(ecdh);
        throw "EC_POINT oct2point error.";
        return false;
    }

    p_ecdh2_public = EC_POINT_new(group);
    if (!EC_POINT_oct2point(group, p_ecdh2_public, SvrPubKey, SvrPubKeyLen, NULL))
    {
        EC_POINT_clear_free(p_ecdh2_public);
        EC_KEY_free(ecdh);
        throw "EC_POINT oct2point error.";
        return false;
    }

    EC_KEY_set_public_key(ecdh, p_ecdh2_public);
    
    if(!(ECDHKEY.sharekeyLen = ECDH_compute_key(ECDHKEY.sharekey, 100, p_ecdh2_public, ecdh, NULL)))
    {
        EC_KEY_free(ecdh);
        throw "Ecdh compute key error.";
        return false;
    }

    EC_POINT_clear_free(p_ecdh2_public);

    EC_KEY_free(ecdh);
    CRYPTO_cleanup_all_ex_data();
    return true;
}

bool Utils::Ecdh_CountSharekey(ECDHKEY &ECDHKEY)
{
    EC_KEY *ecdh;
    const EC_GROUP *group;
    EC_POINT *p_ecdh2_public;

    // ecdh = EC_KEY_new_by_curve_name(NID_secp192k1); //old

    ecdh = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1); // new

    EC_KEY_set_private_key(ecdh, ECDHKEY.prikey);

    group = EC_KEY_get0_group(ecdh);
    p_ecdh2_public = EC_POINT_new(group);
    EC_POINT_oct2point(group, p_ecdh2_public, ECDHKEY.pubkey, ECDHKEY.pubkeyLen, NULL);

    if (!EC_KEY_set_public_key(ecdh, p_ecdh2_public))
    {
        EC_KEY_free(ecdh);
        throw "Ecdh set public key error.";
        return false;
    }

    if(!(ECDHKEY.sharekeyLen = ECDH_compute_key(ECDHKEY.sharekey, 100, p_ecdh2_public, ecdh, NULL)))
    {
        EC_KEY_free(ecdh);
        throw "Ecdh compute key error.";
        return false;
    }
    EC_POINT_clear_free(p_ecdh2_public);
    return true;
}

uint Utils::DES_ECB_Encrypt(byte *_key, byte *data, uint len, byte *&bin)
{
    DES_cblock key;
    DES_key_schedule schedule;
    //转换成schedule
    memcpy(key, _key, 8);
    DES_set_odd_parity(&key);
    DES_set_key_unchecked(&key, &schedule);

    int i = 0, j = len / 8 + 1, k = len % 8;
    int nPidding_size = 8 - k;
    char *szArray;
    szArray = (char *)malloc(len + nPidding_size);
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

LPBYTE Utils::ZlibCompress(const char *source)
{
    uint sourceLen = strlen(source) - 1; //去掉尾部0
    uLong destLen = compressBound(sourceLen);
    LPBYTE dest = new byte[destLen + 4];
    if (compress(dest + 4, &destLen, (byte *)source, sourceLen) == 0)
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

char *Utils::ZlibUnCompress(const byte *source, const uint sourceLen)
{
    uLong destLen = sourceLen * 3;
    byte *dest = new byte[destLen];
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
        return (char *)dest;
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

byte *XBin::Int2Bin(const uint i)
{
    byte *bin = new byte[4];
    bin[0] = i >> 24;
    bin[1] = i >> 16;
    bin[2] = i >> 8;
    bin[3] = (byte)i;
    return bin;
}

void XBin::Int2Bin(const uint i, byte *bin)
{
    bin[0] = i >> 24;
    bin[1] = i >> 16;
    bin[2] = i >> 8;
    bin[3] = (byte)i;
}

char *XBin::Int2IP(const uint i)
{
    char *IP = new char[16];
    sprintf(IP, "%d.%d.%d.%d", ((i & 0xff000000) >> 24), ((i & 0xff0000) >> 16), ((i & 0xff00) >> 8), (i & 0xff));
    return IP;
}

byte *XBin::IP2Bin(const char *IP_)
{
    char IP[16];
    strcpy(IP, IP_);
    byte *ip = new byte[4];
    ip[0] = atoi(strtok(IP, "."));
    for (size_t i = 1; i < 4; i++)
    {
        ip[i] = atoi(strtok(NULL, "."));
    }
    return ip;
}

uint XBin::Bin2Short(const byte *bin)
{
    return bin[0] << 8 | bin[1];
}

uint XBin::Bin2Int(const byte *bin)
{
    return bin[0] << 24 | bin[1] << 16 | bin[2] << 8 | bin[3];
}

/// <summary>
/// 无空格小写字母
/// </summary>
/// <param name="bin"></param>
/// <param name="len"></param>
/// <returns></returns>
char *XBin::Bin2Hex(const byte *bin, const uint len)
{
    const char Table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char *Hex = new char[(len << 1) + 1];
    Hex[len << 1] = 0;
    for (size_t i = 0; i < len; i++)
    {
        Hex[i << 1] = Table[(bin[i] & 0xf0) >> 4];
        Hex[(i << 1) + 1] = Table[bin[i] & 0x0f];
    }
    return Hex;
}

/// <summary>
/// 无空格大写字母
/// </summary>
/// <param name="bin"></param>
/// <param name="len"></param>
/// <returns></returns>
char *XBin::Bin2HexEx(const byte *bin, const uint len)
{
    const char Table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char *Hex = new char[(len << 1) + 1];
    Hex[len << 1] = 0;
    for (size_t i = 0; i < len; i++)
    {
        Hex[i << 1] = Table[(bin[i] & 0xf0) >> 4];
        Hex[(i << 1) + 1] = Table[bin[i] & 0x0f];
    }
    return Hex;
}

//传入无空格,小写
uint XBin::Hex2Bin(const char *hex, byte *&bin)
{
#pragma warning(disable : 4996)
    const byte Table1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const byte Table2[] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    uint len = strlen(hex);
    if (len & 0x1)
        throw "len error";
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
            else if (tmp < 10)
                bin[i] = Table1[tmp] << 4;
            else
            {
                tmp = hex[i << 1] - 'a';
                if (tmp < 0)
                {
                    throw "not hex";
                    return -1;
                }
                else if (tmp < 6)
                    bin[i] = Table2[tmp] << 4;
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
            else if (tmp < 10)
                bin[i] |= Table1[tmp];
            else
            {
                tmp = hex[(i << 1) + 1] - 'a';
                if (tmp < 0)
                {
                    throw "not hex";
                    return -1;
                }
                else if (tmp < 6)
                    bin[i] |= Table2[tmp];
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

//传入无空格,大写
uint XBin::Hex2BinEx(const char *hex, byte *&bin)
{
    const byte Table1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const byte Table2[] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    uint len = strlen(hex);
    if (len == 0)
        throw "empty string";
    if (len & 0x1)
        throw "len error";
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
            else if (tmp < 10)
                bin[i] = Table1[tmp] << 4;
            else
            {
                tmp = hex[i << 1] - 'A';
                if (tmp < 0)
                {
                    throw "not hex";
                    return -1;
                }
                else if (tmp < 6)
                    bin[i] = Table2[tmp] << 4;
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
            else if (tmp < 10)
                bin[i] |= Table1[tmp];
            else
            {
                tmp = hex[(i << 1) + 1] - 'A';
                if (tmp < 0)
                {
                    throw "not hex";
                    return -1;
                }
                else if (tmp < 6)
                    bin[i] |= Table2[tmp];
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

#if defined(_WIN_PLATFORM_)

std::wstring Iconv::AnsiToUnicode(const char *str, const int Length)
{
    int utf16Length = ::MultiByteToWideChar(936, 0, str, Length, nullptr, 0);

    std::wstring utf16;
    utf16.resize(utf16Length);
    ::MultiByteToWideChar(936, 0, str, Length, &utf16[0], utf16Length);
    return utf16;
}

std::string Iconv::UnicodeToAnsi(const wchar_t *str, const int Length)
{
    int ansiLength = ::WideCharToMultiByte(936, 0, str, Length, nullptr, 0, nullptr, nullptr);

    std::string ansi;
    ansi.resize(ansiLength);
    ::WideCharToMultiByte(936, 0, str, Length, &ansi[0], ansiLength, nullptr, nullptr);
    return ansi;
}

std::wstring Iconv::Utf8ToUnicode(const char8_t *str, const int Length)
{
    int utf16Length = ::MultiByteToWideChar(CP_UTF8, 0, (LPCCH)str, Length, nullptr, 0);

    std::wstring utf16;
    utf16.resize(utf16Length);
    ::MultiByteToWideChar(CP_UTF8, 0, (LPCCH)str, Length, &utf16[0], utf16Length);
    return utf16;
}

std::u8string Iconv::UnicodeToUtf8(const wchar_t *str, const int Length)
{
    int utf8Length = ::WideCharToMultiByte(CP_UTF8, 0, str, Length, nullptr, 0, nullptr, nullptr);

    std::u8string utf8;
    utf8.resize(utf8Length);
    ::WideCharToMultiByte(CP_UTF8, 0, str, Length, (LPSTR)&utf8[0], utf8Length, nullptr, nullptr);
    return utf8;
}

#endif

bool BigInteger::AddOne(byte *BigInteger, int len)
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
