#pragma once

#if defined(_WIN_PLATFORM_)
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#if defined(_LINUX_PLATFORM_)
#include <arpa/inet.h>
#endif

#include "Utils.h"

class Socket
{
private:
    SOCKET Client;

public:
    Socket();

public:
    bool Connect(const char *IP, const unsigned short Port);
    void Close();
    void Send(const byte *data, const uint length);
    void Send(const LPBYTE buffer);
    LPBYTE Receive();
    void DomainGetIP(const wchar_t *Domain, wchar_t *&szHostaddress);
};