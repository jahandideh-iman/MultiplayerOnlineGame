#include "NetworkPawn.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Network/ServerGame.h"


mog::network::NetworkPawn::NetworkPawn()
{
	getNetworkComponent()->addVariable("velocity", &velocity);
}

mog::network::NetworkPawn::~NetworkPawn()
{
}

