#include "NetworkPawnFactory.h"
#include "Engine/Network/NetworkPawn.h"

mog::network::NetworkPawnFactory *mog::network::NetworkPawnFactory::factory = nullptr;

mog::network::NetworkPawnFactory::NetworkPawnFactory()
{
}


mog::network::NetworkPawnFactory::~NetworkPawnFactory()
{
	delete constructor;
}

mog::network::NetworkPawnFactory* mog::network::NetworkPawnFactory::get()
{
	if (factory == nullptr)
		factory = new NetworkPawnFactory();
	return factory;
}

void mog::network::NetworkPawnFactory::clear()
{
	delete factory;
	factory = nullptr;
}

bool mog::network::NetworkPawnFactory::isSet()
{
	return constructor != nullptr;
}

mog::network::NetworkPawn *mog::network::NetworkPawnFactory::create()
{
	return dynamic_cast<NetworkPawn*> (constructor->create());
}
