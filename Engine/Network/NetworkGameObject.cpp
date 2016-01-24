#include "NetworkGameObject.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/NetworkGame.h"
#include "Engine/Network/NetworkComponent.h"

#include "Engine/Network/ServerGame.h"

#include <assert.h>



mog::network::NetworkGameObject::NetworkGameObject()
{
	setRole(Role_None);
	networkComponent = new NetworkComponent("networkComponent", this);
	networkComponent->addVariable("position", &position);
	networkComponent->addVariable("rotation", &rotation);
	this->addComponent(networkComponent);
}

mog::network::NetworkGameObject::~NetworkGameObject()
{
}

void mog::network::NetworkGameObject::onAddedToGame(Game *game)
{
	GameObject::onAddedToGame(game);

	initialRegisteredMethods();

	auto netGame = getNetworkGame();
	if (netGame != nullptr)
	{
		if (netGame->getType() == Type_Server)
			setRole(Role_Authority);

		netGame->getNetworkManager()->addNetworkGameObject(this);
	}
}


void mog::network::NetworkGameObject::onRemovedFromGame(Game *game)
{
	GameObject::onRemovedFromGame(game);

	NetworkGame *netGame = dynamic_cast<NetworkGame*>(game);
	if (netGame != nullptr)
		netGame->getNetworkManager()->removeNetworkGameObject(this);
}



void mog::network::NetworkGameObject::writeState(Buffer *buffer, bool dirtyOnly) const
{
	networkComponent->writeReplications(buffer, dirtyOnly);
}

mog::network::NetworkComponent * mog::network::NetworkGameObject::getNetworkComponent()
{
	return networkComponent;
}

void mog::network::NetworkGameObject::readState(const Buffer *buffer)
{
	networkComponent->readReplications(buffer);
}

void mog::network::NetworkGameObject::registerMethod(std::string name,Method method)
{
	registeredMethods.emplace(name, method);
}

void mog::network::NetworkGameObject::initialRegisteredMethods()
{

}

void mog::network::NetworkGameObject::callMethod(std::string name)
{
	auto p = registeredMethods.find(name);

	assert(p != registeredMethods.end());

	p->second();
}

void mog::network::NetworkGameObject::updatePosition(float dt)
{
	GameObject::updatePosition(dt);
	//if (dynamic_cast<NetworkGame *> (getOwner()) == nullptr)
	//	GameObject::updatePosition(dt);
	//else
	//{
	//	if (dynamic_cast<ServerGame *> (getOwner()) != nullptr)
	//		GameObject::updatePosition(dt);
	//}
}

void mog::network::NetworkGameObject::setClient(const Client *client)
{
	this->client = client;
}

const mog::network::Client * mog::network::NetworkGameObject::getClient() const
{
	return client;
}

mog::network::Role mog::network::NetworkGameObject::getRole() const
{
	return role;
}

mog::network::NetworkGame * mog::network::NetworkGameObject::getNetworkGame()
{
	return dynamic_cast<NetworkGame*>(getOwner());
}

void mog::network::NetworkGameObject::setRole(Role role)
{
	this->role = role;
}

bool mog::network::NetworkGameObject::isDirty() const
{
	return networkComponent->isDirty();
}

void mog::network::NetworkGameObject::setDirty(bool dirty)
{
	networkComponent->setDirty(dirty);
}
