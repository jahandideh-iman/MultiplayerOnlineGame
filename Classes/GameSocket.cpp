#include "GameSocket.h"
#include <stdio.h>
#include "cocos2d.h"


GameSocket::GameSocket()
{
	socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket <= 0)
		CCLOG("!!!!!!!!! COULD NOT CREAT SOCKET !!!!!!!!!!!!!!!");
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

	CCLOG("Receiving ... ");

	int bytes = ::recvfrom(socket, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	CCLOG("Read %d bytes", bytes);

	if (bytes <= 0)
		return 0;

	unsigned int from_address =
		ntohl(from.sin_addr.s_addr);

	unsigned int from_port =
		ntohs(from.sin_port);

	CCLOG("data is %c", (char*)data);

	return bytes;
}
