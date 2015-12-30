#include "NetworkGameObject.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/NetworkGame.h"
#include "Engine/Network/NetworkComponent.h"


mog::network::NetworkGameObject::NetworkGameObject()
{
	networkComponent = new NetworkComponent("networkComponent", this);
	this->addComponent(networkComponent);
}

mog::network::NetworkGameObject::~NetworkGameObject()
{
}

void mog::network::NetworkGameObject::onAddedToGame(Game *game)
{
	GameObject::onAddedToGame(game);
	NetworkGame *netGame = dynamic_cast<NetworkGame*>(game);
	if (netGame != nullptr)
		netGame->getNetworkManager()->addNetworkGameObject(this);
}

void mog::network::NetworkGameObject::setInstanceId(unsigned i)
{
	this->instanceId = i;
}

unsigned mog::network::NetworkGameObject::getInstanceId() const
{
	return instanceId;
}

void mog::network::NetworkGameObject::setIsReplica(bool isReplical)
{
	bIsReplica = isReplical;
}

bool mog::network::NetworkGameObject::isReplica() const
{
	return bIsReplica;
}

void mog::network::NetworkGameObject::writeState(Buffer *buffer) const
{
	networkComponent->writeReplications(buffer);
}
