#include "Pawn.h"
#include "Engine/SpriteComponent.h"
#include "Engine/NetworkComponent.h"

mog::Pawn::Pawn()
{
	addComponent(new SpriteComponent("pawn.png"));
	addComponent(new NetworkComponent());
}


mog::Pawn::~Pawn()
{
}
