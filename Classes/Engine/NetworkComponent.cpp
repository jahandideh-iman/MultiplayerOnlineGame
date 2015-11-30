#include "NetworkComponent.h"


mog::NetworkComponent::NetworkComponent(ID id, const GameObject *owner) : Component(id, owner)
{
}


mog::NetworkComponent::~NetworkComponent()
{
}

void mog::NetworkComponent::addVariable(const std::string &name, Serializable *var)
{
	replicationVars.emplace(name, var);
}
