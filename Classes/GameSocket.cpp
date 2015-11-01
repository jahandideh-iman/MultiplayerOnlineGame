#include "GameSocket.h"
#include <stdio.h>
#include "cocos2d.h"
#include "InternetAddress.h"

GameSocket::GameSocket()
{
	socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket <= 0)
		CCLOG("!!!!!!!!! COULD NOT CREAT SOCKET !!!!!!!!!!!!!!!");

	DWORD nonBlocking = 1;
	auto res = ioctlsocket(socket, FIONBIO, &nonBlocking);
	if (res != 0)
		CCLOG("!!!!!!!!!!!!! COULD NOT SET NONBLOCKING !!!!!!!!!!!");
}


GameSocket::~GameSocket()
{
}

bool GameSocket::InitialNetwork()
{
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		CCLOG("WSAStartup failed: %d\n", iResult);
		return false;
	}

	return true;
}

void GameSocket::CleanUpNetwork()
{
	::WSACleanup();
}

bool GameSocket::Open(unsigned short port)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port =
		htons((unsigned short)port);


	auto res = ::bind(socket, (const sockaddr*)&address, sizeof(sockaddr_in));
	if (res < 0)
	{
		CCLOG("!!!!!!!!! COULD NOT BIND SOCKET !!!!!!!!!!!!!!!");
		return false;
	}

	return true;
}

int GameSocket::Receive(Address & sender, void * data, int size)
{
	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int bytes = ::recvfrom(socket, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	auto error = WSAGetLastError();

	//CCLOG("Error: %d ", error);
	if (bytes <= 0)
		return 0;

	unsigned int from_address =
		ntohl(from.sin_addr.s_addr);

	unsigned int from_port =
		ntohs(from.sin_port);

	CCLOG("data is %c", (char*)data);

	return bytes;
}

bool GameSocket::Send(const Address & destination, const void * data, int size)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = destination.GetAddress();
	address.sin_port =
		htons((unsigned short)destination.GetPort());

	int sent_bytes =
		sendto(socket,
		(const char*)data,
		size,
		0,
		(sockaddr*)&address,
		sizeof(sockaddr_in));

	if (sent_bytes != size)
	{
		printf("failed to send packet\n");
		return false;
	}

	return true;
}
