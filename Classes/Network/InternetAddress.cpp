#include "InternetAddress.h"
#include <WinSock2.h>
#include <ws2tcpip.h>

using mog::network::InternetAddress;

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

unsigned int InternetAddress::getAddress() const
{
	return address;
}

unsigned short InternetAddress::getPort() const
{
	return port;
}
