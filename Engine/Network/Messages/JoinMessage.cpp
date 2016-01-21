#include "JoinMessage.h"
#include "Engine/Network/ServerGame.h"
#include "Engine/Network/InternetAddress.h"

using mog::network::JoinMessage;
using namespace mog;


network::JoinMessage::JoinMessage(std::string playerName)
{
	this->playerName = playerName;
}

network::JoinMessage::JoinMessage()
{
}


JoinMessage::~JoinMessage()
{
}

void mog::network::JoinMessage::fillData(ParameterContainer &parameters) const
{
	parameters.put("name", playerName);
}

void mog::network::JoinMessage::executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const
{
	std::string name = parameters.get("name");

	game->joinNewPlayer(new Client(name, new InternetAddress(address)));
}
