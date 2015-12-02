#include "PlayerInfo.h"

using namespace mog;

PlayerInfo::PlayerInfo(std::string &name, const network::InternetAddress *address)
{
	this->name = name;
	this->address = address;
}


PlayerInfo::~PlayerInfo()
{
}
