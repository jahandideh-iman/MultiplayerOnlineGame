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

void mog::network::Join::fillData(ParameterContainer *parameters) const
{
	parameters->put("message", "hello");
}

void mog::network::Join::execute(const ParameterContainer &parameters, const InternetAddress& address) const
{
	auto server = dynamic_cast<ServerGame*> (GlobalData::game);
	std::string name = "name";

	if (server != nullptr)
		server->joinNewPlayer(new PlayerInfo(name, &address));
}
