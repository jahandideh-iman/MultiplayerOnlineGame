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

void mog::network::NetworkPawn::update(float dt)
{
	NetworkGameObject::update(dt);
	if (dynamic_cast<NetworkGame *> (getOwner()) == nullptr)
		setPosition(getPosition() + velocity*dt);
	else
	{
		if (dynamic_cast<ServerGame *> (getOwner()) != nullptr)
			setPosition(getPosition() + velocity*dt);
	}
}

void mog::network::NetworkPawn::setVelocity(Vector velocity)
{
	this->velocity = velocity;
}

mog::Vector mog::network::NetworkPawn::getVelocity() const
{
	return velocity;
}

void mog::network::NetworkPawn::setVelocityX(float x)
{
	velocity.x = x;
}

void mog::network::NetworkPawn::setVelocityY(float y)
{
	velocity.y = y;
}
