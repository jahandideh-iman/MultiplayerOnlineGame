#include "ReplicateInstance.h"
#include "NetworkGameObject.h"
#include "ConstructorDatabase.h"
#include "Engine/GlobalData.h"
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

void mog::network::ReplicateInstance::execute(const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	if (GlobalData::gameType == GameType::T_Client)
	{
		std::string type = parameters.get("typeId");
		std::string index = parameters.get("instanceId");
		NetworkGameObject* o =  dynamic_cast<NetworkGameObject*> (ConstructorDatabase::get()->create(type));
		o->setIndex(std::stoi(index));
		GlobalData::game->addGameObject(o);
	}
}

void mog::network::ReplicateInstance::fillData(ParameterContainer &parameters) const
{
	parameters.put("typeId", object->getNetworkID());
	parameters.put("instanceId", std::to_string(object->getIndex()));
}
