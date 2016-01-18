#include "NetworkPawn.h"


mog::network::NetworkPawn::NetworkPawn()
{
}

mog::network::NetworkPawn::~NetworkPawn()
{
}

void mog::network::NetworkPawn::update(float dt)
{
	setPosition(getPosition() + velocity*dt);
}

void mog::network::NetworkPawn::setVelocity(Vector velocity)
{
	this->velocity = velocity;
}

mog::Vector mog::network::NetworkPawn::getVelocity() const
{
	return velocity;
}
