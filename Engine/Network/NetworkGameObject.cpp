#include "NetworkGameObject.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/NetworkGame.h"


mog::network::NetworkGameObject::NetworkGameObject()
{
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

void mog::network::NetworkGameObject::setIndex(unsigned i)
{
	this->index = i;
}

unsigned mog::network::NetworkGameObject::getIndex()
{
	return index;
}
