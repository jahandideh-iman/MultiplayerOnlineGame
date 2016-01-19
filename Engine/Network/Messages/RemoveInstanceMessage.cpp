#include "RemoveInstanceMessage.h"

#include "Engine/Network/ClientGame.h"
#include "Engine/Network/NetworkManager.h"

mog::network::RemoveInstanceMessage::RemoveInstanceMessage(const NetworkGameObject *gameObject)
{
	this->gameObject = gameObject;
}

mog::network::RemoveInstanceMessage::RemoveInstanceMessage()
{

}

mog::network::RemoveInstanceMessage::~RemoveInstanceMessage()
{

}

void mog::network::RemoveInstanceMessage::fillData(ParameterContainer &parameters) const
{
	parameters.put("instanceId", std::to_string(gameObject->getInstanceId()));
}

void mog::network::RemoveInstanceMessage::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const InternetAddress &address) const
{
	unsigned instanceId = atoi(parameters.get("instanceId").c_str());
	auto object = game->getNetworkManager()->findNetworkGameObject(instanceId);
	game->removeGameObject(object);
}
