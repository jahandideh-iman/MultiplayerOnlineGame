#include "MockNetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"



mog::network::MockNetworkGameObject::MockNetworkGameObject()
{
	networkComponent->removeVariable("position");
}

