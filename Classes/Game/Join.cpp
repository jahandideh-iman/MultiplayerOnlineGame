#include "Join.h"
#include "cocos2d.h"
#include "Engine/GlobalData.h"
#include "ServerGame.h"
#include "Network/InternetAddress.h"

using mog::network::Join;
using namespace mog;


network::Join::Join()
{
}


Join::~Join()
{
}

network::NetworkData *Join::write() const
{

	auto data = new char[20];
	auto s = sprintf(data, "%u", this->getCode());
	strcpy(&data[s+1], "Hello");

	NetworkData *nd = new NetworkData(data, s+1+6);
	return nd;
}

void Join::execute(const network::NetworkData &data, const network::InternetAddress &address) const
{
	CCLOG("join is %s",data.data);
	auto server = dynamic_cast<ServerGame*> (GlobalData::game);
	std::string name = "name";

	if (server != nullptr)
		server->joinNewPlayer(new PlayerInfo(name, &address));	
}

unsigned Join::getCode() const
{
	return 1000;
}
