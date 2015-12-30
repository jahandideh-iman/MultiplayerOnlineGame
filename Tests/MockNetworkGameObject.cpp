#include "MockNetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"



mog::network::MockNetworkGameObject::MockNetworkGameObject()
{
	networkComponent->addVariable("var", &variable);
}

mog::Integer mog::network::MockNetworkGameObject::getVariable() const
{
	return variable;
}
