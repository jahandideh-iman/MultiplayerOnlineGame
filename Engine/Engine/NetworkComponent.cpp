#include "NetworkComponent.h"
#include "Network/NetworkManager.h"

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

void mog::NetworkComponent::networkUpdate(float dt)
{

}

void mog::NetworkComponent::addSelfToGame(Game *g)
{
	//network::NetworkManager::get()->addNetworkComponent(this);
}

void mog::NetworkComponent::writeReplications(Buffer *buffer) const
{
	ParameterContainer container;
	Buffer varBuffer;
	for (auto var : replicationVars)
	{
		var.second->write(&varBuffer);
		container.put(var.first, varBuffer.getData());
		varBuffer.clear();
	}
	container.write(buffer);	
}

void mog::NetworkComponent::readReplications(const Buffer *buffer)
{

}

unsigned mog::NetworkComponent::getIndex() const
{
	return index;
}

void mog::NetworkComponent::setIndex(unsigned i)
{
	index = i;
}
