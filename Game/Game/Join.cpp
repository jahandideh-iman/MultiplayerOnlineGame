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

void mog::network::Join::fillData(ParameterContainer &parameters) const
{
	parameters.put("message", "hello");
}

void mog::network::Join::executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const
{
	std::string name = "name";

	game->joinNewPlayer(new PlayerInfo(name, &address));
}
