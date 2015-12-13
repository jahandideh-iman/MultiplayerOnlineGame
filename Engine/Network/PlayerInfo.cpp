#include "PlayerInfo.h"



mog::network::PlayerInfo::PlayerInfo(std::string &name, const network::InternetAddress *address)
{
	this->name = name;
	this->address = address;
}


mog::network::PlayerInfo::~PlayerInfo()
{
}
