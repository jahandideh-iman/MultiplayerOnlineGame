#include "NetworkComponent.h"


mog::NetworkComponent::NetworkComponent(ID id, const GameObject *owner) : Component(id, owner)
{
}


mog::NetworkComponent::~NetworkComponent()
{
}

void mog::NetworkComponent::addRepVar(const std::string &name, int *address)
{
	replicationVars.emplace(name, address);
}
