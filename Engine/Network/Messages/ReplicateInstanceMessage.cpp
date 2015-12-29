#include "ReplicateInstanceMessage.h"
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/ConstructorDatabase.h"
#include "Engine/Network/ClientGame.h"

#include <sstream>


mog::network::ReplicateInstanceMessage::ReplicateInstanceMessage(const NetworkGameObject *object)
{
	this->object = object;
}

mog::network::ReplicateInstanceMessage::ReplicateInstanceMessage()
{

}


mog::network::ReplicateInstanceMessage::~ReplicateInstanceMessage()
{
}

void mog::network::ReplicateInstanceMessage::fillData(ParameterContainer &parameters) const
{
	parameters.put("typeId", object->getNetworkID());
	parameters.put("instanceId", std::to_string(object->getInstanceId()));
}

void mog::network::ReplicateInstanceMessage::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	std::string type = parameters.get("typeId");
	std::string index = parameters.get("instanceId");
	NetworkGameObject* o = dynamic_cast<NetworkGameObject*> (ConstructorDatabase::get()->create(type));
	o->setInstanceId(std::stoi(index));
	o->setIsReplica(true);
	game->addGameObject(o);
}
