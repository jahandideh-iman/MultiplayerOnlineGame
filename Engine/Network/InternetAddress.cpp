#include "InternetAddress.h"


using mog::network::InternetAddress;

InternetAddress::InternetAddress()
{
	this->port = 0;
	this->address = 0;
}

mog::network::InternetAddress::InternetAddress(unsigned short port)
{
	this->port = port;
	this->address = 0;
}


InternetAddress::InternetAddress(unsigned int address, unsigned short port)
{
	this->address = address;
	this->port = port;
}

//InternetAddress::InternetAddress(char *address, unsigned short port)
//{
//	this->address = ntohl(inet_addr(address));
//	this->port = port;
//}

unsigned int InternetAddress::getAddress() const
{
	return address;
}

unsigned short InternetAddress::getPort() const
{
	return port;
}

void mog::network::InternetAddress::setAddress(unsigned address)
{
	this->address = address;
}

void mog::network::InternetAddress::setPort(unsigned short port)
{
	this->port = port;
}

mog::network::InternetAddress::InternetAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
{
	this->address = (a << 24) |
		(b << 16) |
		(c << 8) |
		d;
	this->port = port;
}

mog::network::InternetAddress::InternetAddress(const InternetAddress&other)
{
	this->address = other.getAddress();
	this->port = other.getPort();
}

bool mog::network::InternetAddress::operator==(const InternetAddress &other) const
{
	if (address == other.address && port == other.port)
		return true;
	return false;
}

bool mog::network::InternetAddress::operator!=(const InternetAddress &other) const
{
	return !this->operator==(other);
}

