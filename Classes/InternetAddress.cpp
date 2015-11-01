#include "InternetAddress.h"
#include <WinSock2.h>
#include <ws2tcpip.h>


InternetAddress::InternetAddress()
{
}

InternetAddress::InternetAddress(unsigned int address, unsigned short port)
{
	this->address = address;
	this->port = port;
}

InternetAddress::InternetAddress(char *address, unsigned short port)
{
	this->address =inet_addr(address);
	this->port = port;
}

unsigned int InternetAddress::GetAddress() const
{
	return address;
}

unsigned short InternetAddress::GetPort() const
{
	return port;
}
