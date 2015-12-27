#include "NetworkComponent.h"
#include "Network/NetworkManager.h"
#include "Network/NetworkGame.h"

mog::network::NetworkComponent::NetworkComponent(ID id, const GameObject *owner) : Component(id, owner)
{
}


mog::network::NetworkComponent::~NetworkComponent()
{
}

void mog::network::NetworkComponent::addVariable(const std::string &name, Serializable *var)
{
	replicationVars.emplace(name, var);
}

void mog::network::NetworkComponent::networkUpdate(float dt)
{

}

void mog::network::NetworkComponent::addSelfToGame(Game *g)
{
	NetworkGame *netGame = dynamic_cast<NetworkGame*>(g);
	if (netGame != nullptr)
		netGame->getNetworkManager()->addNetworkComponent(this);
}

void mog::network::NetworkComponent::writeReplications(Buffer *buffer) const
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

void mog::network::NetworkComponent::readReplications(const Buffer *buffer)
{

}

unsigned mog::network::NetworkComponent::getIndex() const
{
	return index;
}

void mog::network::NetworkComponent::setIndex(unsigned i)
{
	index = i;
}
