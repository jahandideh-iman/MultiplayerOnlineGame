#include "NetworkComponent.h"


mog::NetworkComponent::NetworkComponent()
{
}


mog::NetworkComponent::~NetworkComponent()
{
}

void mog::NetworkComponent::addRepVar(const std::string &name, int *address)
{
	replicationVars.emplace(name, address);
}
