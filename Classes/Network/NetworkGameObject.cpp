#include "NetworkGameObject.h"
#include "Network/NetworkManager.h"


mog::network::NetworkGameObject::NetworkGameObject()
{
}


mog::network::NetworkGameObject::~NetworkGameObject()
{
}

void mog::network::NetworkGameObject::onAddedToGame(Game *game)
{
	GameObject::onAddedToGame(game);
	NetworkManager::get()->addNetworkGameObject(this);
}

void mog::network::NetworkGameObject::setIndex(unsigned i)
{
	this->index = i;
}

unsigned mog::network::NetworkGameObject::getIndex()
{
	return index;
}
