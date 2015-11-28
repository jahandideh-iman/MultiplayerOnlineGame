#include "NetworkGameObject.h"
#include "Network/NetworkManager.h"


mog::network::NetworkGameObject::NetworkGameObject()
{
}


mog::network::NetworkGameObject::~NetworkGameObject()
{
}

void mog::network::NetworkGameObject::addSelfToGame(Game *game)
{
	GameObject::addSelfToGame(game);
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
