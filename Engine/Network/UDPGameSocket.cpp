#include "UDPGameSocket.h"
#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>


mog::network::UDPGameSocket::UDPGameSocket()
{
	socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	/*if (socket <= 0)
		CCLOG("!!!!!!!!! COULD NOT CREAT SOCKET !!!!!!!!!!!!!!!");*/

	DWORD nonBlocking = 1;
	auto res = ioctlsocket(socket, FIONBIO, &nonBlocking);
	//if (res != 0)
	//	CCLOG("!!!!!!!!!!!!! COULD NOT SET NONBLOCKING !!!!!!!!!!!");
}


mog::network::UDPGameSocket::~UDPGameSocket()
{
	closesocket(socket);
}

void mog::network::UDPGameSocket::open(unsigned short port)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port =
		htons((unsigned short)port);


	auto res = ::bind(socket, (const sockaddr*)&address, sizeof(sockaddr_in));
	if (res < 0)
	{
		//CCLOG("!!!!!!!!! COULD NOT BIND SOCKET !!!!!!!!!!!!!!!");
	}

}

int mog::network::UDPGameSocket::receive(Address &sender, void *data, int size)
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

	sender.setPort(from_port);
	sender.setAddress(from_address);

	//CCLOG("data is %c", (char*)data);

	return bytes;
}

bool mog::network::UDPGameSocket::send(const mog::network::InternetAddress & destination, const char * data, int size)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination.getAddress());
	address.sin_port =
		htons((unsigned short)destination.getPort());

	int wtf = ntohs(address.sin_port);

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

bool mog::network::UDPGameSocket::setup()
{
	WSADATA wsaData;

	// Initialize Winsock
	auto iResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	return true;
}

bool mog::network::UDPGameSocket::teardown()
{
	::WSACleanup();
	return true;
}

void mog::network::UDPGameSocket::close()
{

}

bool mog::network::UDPGameSocket::isOpen() const
{
	return true;
}
