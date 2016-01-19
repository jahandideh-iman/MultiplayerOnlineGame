#include "PlayerInfo.h"



mog::network::PlayerInfo::PlayerInfo(std::string name, const network::InternetAddress *address)
{
	this->name = name;
	this->address = address;
}


mog::network::PlayerInfo::~PlayerInfo()
{
	delete address;
}

bool mog::network::PlayerInfo::operator==(const PlayerInfo &other) const
{
	if (this->name == other.name && *address == *other.address)
		return true;
	return false;
}

bool mog::network::PlayerInfo::operator!=(const PlayerInfo &other) const
{
	return !this->operator==(other);
}
