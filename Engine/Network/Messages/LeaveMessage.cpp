#include "LeaveMessage.h"
#include "Engine/Network/ServerGame.h"


mog::network::LeaveMessage::LeaveMessage()
{

}

mog::network::LeaveMessage::LeaveMessage(std::string playerName)
{
	this->playerName = playerName;
}

mog::network::LeaveMessage::~LeaveMessage()
{

}

void mog::network::LeaveMessage::executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const
{
	std::string name = parameters.get("name");

	game->removePlayer(&Client(name, new InternetAddress(address)));
}

void mog::network::LeaveMessage::fillData(ParameterContainer &parameters) const
{
	parameters.put("name", playerName);
}
