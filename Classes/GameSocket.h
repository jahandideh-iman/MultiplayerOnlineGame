#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

class InternetAddress;

class GameSocket
{
	typedef InternetAddress Address;

public:

	GameSocket();
	~GameSocket();

	bool Open(unsigned short port);
	void Close();
	bool IsOpen() const;
	bool Send(const Address & destination,
		const void * data,
		int size);
	int Receive(Address & sender,
		void * data,
		int size);


};

