#include "RemoteMethodCallMessage.h"

#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/ServerGame.h"
#include "Engine/Network/NetworkManager.h"

mog::network::RemoteMethodCallMessage::RemoteMethodCallMessage(const NetworkGameObject *object, std::string methodName)
{
	this->object = object;
	this->methodName = methodName;
}

mog::network::RemoteMethodCallMessage::RemoteMethodCallMessage()
{

}

mog::network::RemoteMethodCallMessage::~RemoteMethodCallMessage()
{
}

void mog::network::RemoteMethodCallMessage::executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const
{
	std::string instanceId = parameters.get("instanceId");
	std::string method = parameters.get("method");

	auto networkObject = game->getNetworkManager()->findNetworkGameObjectByInstanceId(std::stoi(instanceId));
	networkObject->callMethod(method);
}

void mog::network::RemoteMethodCallMessage::fillData(ParameterContainer &parameters) const
{
	parameters.put("instanceId", std::to_string(object->getInstanceId()));
	parameters.put("method", methodName);
}
