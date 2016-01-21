#include "Client.h"



mog::network::Client::Client(std::string name, const network::InternetAddress *address)
{
	this->name = name;
	this->address = address;
}

mog::network::Client::Client(const Client *other)
{
	this->address = new InternetAddress(*other->address);
	this->name = other->name;
}


mog::network::Client::~Client()
{
	delete address;
}

bool mog::network::Client::operator==(const Client &other) const
{
	if (&other == nullptr)
		return false;
	if (this->name == other.name && *address == *other.address)
		return true;
	return false;
}

bool mog::network::Client::operator!=(const Client &other) const
{
	return !this->operator==(other);
}
