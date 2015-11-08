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

	static bool InitialNetwork();
	static void CleanUpNetwork();

	bool Open(unsigned short port);
	void Close();
	bool IsOpen() const;
	bool Send(const Address & destination,
		const char * data,
		int size);
	int Receive(Address & sender,
		void * data,
		int size);

private:
	SOCKET socket = 0;

};

