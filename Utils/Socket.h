#pragma once

#if defined(_WIN_PLATFORM_)
#include <WS2tcpip.h>
#endif

#if defined(_LINUX_PLATFORM_)
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "Utils.h"

class Socket
{
private:
#if defined(_WIN_PLATFORM_)
    SOCKET Client;
#endif
#if defined(_LINUX_PLATFORM_)
    int Client;
#endif
public:
    Socket();

public:
    bool Connected = false;

public:
    bool Connect(const char *IP, const unsigned short Port);
    void Close();
    int Send(const byte *data, const uint length);
    int Send(const LPBYTE buffer);
    LPBYTE Receive();
    void DomainGetIP(const
#if defined(_WIN_PLATFORM_)
                     wchar_t
#endif
#if defined(_LINUX_PLATFORM_)
                     char
#endif
                         *Domain,
#if defined(_WIN_PLATFORM_)
                     wchar_t
#endif
#if defined(_LINUX_PLATFORM_)
                     char
#endif
                         *&szHostaddress);
};