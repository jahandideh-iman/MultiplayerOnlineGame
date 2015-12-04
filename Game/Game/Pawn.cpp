#include "Pawn.h"
#include "SpriteComponent.h"
#include "Engine/NetworkComponent.h"

mog::Pawn::Pawn()
{
	addComponent(new SpriteComponent("sprite",this,"pawn.png"));
	addComponent(new NetworkComponent("net",this));

	NetworkComponent *c = dynamic_cast<NetworkComponent*> (findComponent("net"));

	c->addVariable("health",&health);
}


mog::Pawn::~Pawn()
{
}
