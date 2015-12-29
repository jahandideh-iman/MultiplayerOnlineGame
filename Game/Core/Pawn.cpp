#include "Pawn.h"
#include "SpriteComponent.h"
#include "Engine/Network/NetworkComponent.h"

mog::Pawn::Pawn()
{
	addComponent(new SpriteComponent("sprite",this,"pawn.png"));
	addComponent(new network::NetworkComponent("net",this));

	auto c = dynamic_cast<network::NetworkComponent*> (findComponent("net"));

	c->addVariable("health",&health);
}


mog::Pawn::~Pawn()
{
}
