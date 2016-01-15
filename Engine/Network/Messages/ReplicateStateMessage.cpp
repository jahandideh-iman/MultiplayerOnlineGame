#include "ReplicateStateMessage.h"
#include "Engine/Core/Macros.h"
#include "Engine/Core/Buffer.h"
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/ClientGame.h"
#include "Engine/Network/NetworkManager.h"

mog::network::ReplicateStateMessage::ReplicateStateMessage()
{
}

mog::network::ReplicateStateMessage::ReplicateStateMessage(const NetworkGameObject *object) : networkGameObject(object)
{

}


mog::network::ReplicateStateMessage::~ReplicateStateMessage()
{
}

void mog::network::ReplicateStateMessage::fillData(ParameterContainer &parameters) const
{
	Buffer buffer;

	networkGameObject->writeState(&buffer);

	char *data = buffer.getData();

	parameters.put("instanceId", std::to_string(networkGameObject->getInstanceId()));
	parameters.put("states", data);

	delete []data;
}

void mog::network::ReplicateStateMessage::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	std::string instanceId = parameters.get("instanceId");
	std::string states = parameters.get("states");

	auto networkObject = game->getNetworkManager()->findNetworkGameObjectByInstanceId(std::stoi(instanceId));
	networkObject->readState(&Buffer(states));
}
