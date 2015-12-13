#include "ReplicateInstance.h"
#include "NetworkGameObject.h"
#include "ConstructorDatabase.h"
#include "Network/ClientGame.h"

#include <sstream>


mog::network::ReplicateInstance::ReplicateInstance(NetworkGameObject *object)
{
	this->object = object;
}

mog::network::ReplicateInstance::ReplicateInstance()
{

}


mog::network::ReplicateInstance::~ReplicateInstance()
{
}

void mog::network::ReplicateInstance::fillData(ParameterContainer &parameters) const
{
	parameters.put("typeId", object->getNetworkID());
	parameters.put("instanceId", std::to_string(object->getIndex()));
}

void mog::network::ReplicateInstance::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	std::string type = parameters.get("typeId");
	std::string index = parameters.get("instanceId");
	NetworkGameObject* o = dynamic_cast<NetworkGameObject*> (ConstructorDatabase::get()->create(type));
	o->setIndex(std::stoi(index));
	game->addGameObject(o);
}
