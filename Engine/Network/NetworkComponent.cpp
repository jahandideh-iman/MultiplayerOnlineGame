#include "NetworkComponent.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/NetworkGame.h"

mog::network::NetworkComponent::NetworkComponent(ID id, const GameObject *owner) : Component(id, owner)
{
}


mog::network::NetworkComponent::~NetworkComponent()
{
}

void mog::network::NetworkComponent::addVariable(const std::string &name, Replicable *var)
{
	replicationVars.emplace(name, var);
}

void mog::network::NetworkComponent::removeVariable(const std::string &name)
{
	replicationVars.erase(name);
}

void mog::network::NetworkComponent::removeAllVariables()
{
	replicationVars.clear();
}


void mog::network::NetworkComponent::addSelfToGame(Game *g)
{
	/*NetworkGame *netGame = dynamic_cast<NetworkGame*>(g);
	if (netGame != nullptr)
		netGame->getNetworkManager()->addNetworkComponent(this);*/
}

void mog::network::NetworkComponent::writeReplications(Buffer *buffer,bool dirtyOnly) const
{
	ParameterContainer container;
	Buffer varBuffer;
	for (auto var : replicationVars)
	{
		//If dirtiesOnly is true then var.second->isDirty() must be true
		if (!dirtyOnly || var.second->isDirty())
		{
			var.second->write(&varBuffer);
			char *data = varBuffer.getData();
			container.put(var.first, data);
			delete[]data;
			varBuffer.clear();
		}
	}
	container.write(buffer);	
}

void mog::network::NetworkComponent::readReplications(const Buffer *buffer)
{
	ParameterContainer container(buffer);
	Buffer varBuffer;
	for (auto var : replicationVars)
	{
		if (container.get(var.first) != "")
		{
			varBuffer.write(container.get(var.first));
			var.second->read(&varBuffer);
			varBuffer.clear();
		}
	}
}

bool mog::network::NetworkComponent::hasVarialbe(const std::string &name)
{
	return replicationVars.find(name) != replicationVars.end();
}

bool mog::network::NetworkComponent::isDirty() const
{
	for (auto var : replicationVars)
	{
		if (var.second->isDirty())
			return true;
	}
	return false;
}

void mog::network::NetworkComponent::setDirty(bool dirty)
{
	for (auto var : replicationVars)
		var.second->setDirty(dirty);
}

