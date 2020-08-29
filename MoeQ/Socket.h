#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Utils.h"

#pragma comment(lib, "ws2_32.lib") 

class Socket
{
private:
	SOCKET Client;
public:
	Socket();
public:
	bool Connect(const char* IP, const unsigned short Port);
	bool IsConnected();
	void Close();
	void Send(LPBYTE buffer);
	LPBYTE Receive();
	void DomainGetIP(const wchar_t* Domain, wchar_t*& szHostaddress);
};