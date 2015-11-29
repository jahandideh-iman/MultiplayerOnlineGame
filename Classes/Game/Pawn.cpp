#include "Pawn.h"
#include "Engine/SpriteComponent.h"
#include "Engine/NetworkComponent.h"

mog::Pawn::Pawn()
{
	addComponent(new SpriteComponent("sprite",this,"pawn.png"));
	addComponent(new NetworkComponent("net",this));
}


mog::Pawn::~Pawn()
{
}
