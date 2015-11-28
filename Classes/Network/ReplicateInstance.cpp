#include "ReplicateInstance.h"
#include "NetworkGameObject.h"
#include <sstream>


mog::network::ReplicateInstance::ReplicateInstance(NetworkGameObject *object)
{
	this->object = object;
}


mog::network::ReplicateInstance::~ReplicateInstance()
{
}

void mog::network::ReplicateInstance::execute(const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	std::string type  = parameters.get("typeId");
	std::string index = parameters.get("instanceId");
	int a = 2;
}

void mog::network::ReplicateInstance::fillData(ParameterContainer *parameters) const
{
	parameters->put("typeId", object->getNetworkID());
	parameters->put("instanceId", std::to_string(object->getIndex()));
}
