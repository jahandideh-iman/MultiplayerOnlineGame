#include "ReplicateStateMessage.h"
#include "Engine/Core/Macros.h"
#include "Engine/Core/Buffer.h"
#include "Engine/Network/NetworkGameObject.h"

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

	parameters.put("instanceId", std::to_string(networkGameObject->getInstanceId()));
	parameters.put("states", buffer.getData());
}

void mog::network::ReplicateStateMessage::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	int a = 5;
	//MOGLOG("Replicate Instance Message \n %s", parameters.write(&Buffer())->getData());
}
