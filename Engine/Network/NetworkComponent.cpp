#include "NetworkComponent.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/NetworkGame.h"

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

void mog::network::NetworkComponent::addSelfToGame(Game *g)
{
	/*NetworkGame *netGame = dynamic_cast<NetworkGame*>(g);
	if (netGame != nullptr)
		netGame->getNetworkManager()->addNetworkComponent(this);*/
}

void mog::network::NetworkComponent::writeReplications(Buffer *buffer) const
{
	ParameterContainer container;
	Buffer varBuffer;
	for (auto var : replicationVars)
	{
		var.second->write(&varBuffer);
		char *data = varBuffer.getData();
		container.put(var.first, data);
		delete[]data;
		varBuffer.clear();
	}
	container.write(buffer);	
}

void mog::network::NetworkComponent::readReplications(const Buffer *buffer)
{
	ParameterContainer container(*buffer);
	Buffer varBuffer;
	for (auto var : replicationVars)
	{
		varBuffer.write(container.get(var.first));
		var.second->read(&varBuffer);
		varBuffer.clear();
	}
}

