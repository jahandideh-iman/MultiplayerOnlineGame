#include "Pawn.h"
#include "SpriteComponent.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Network/ClientGame.h"
#include "InputComponent.h"

#include "cocos2d.h"

mog::Pawn::Pawn()
{
	addComponent(new SpriteComponent("sprite",this,"pawn.png"));

	getNetworkComponent()->addVariable("health",&health);

	auto input = new InputComponent("input", this);
	input->addAction(cocos2d::EventKeyboard::KeyCode::KEY_W, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveUp", this);
	});

	addComponent(input);
}

mog::Pawn::~Pawn()
{
}

void mog::Pawn::moveUp()
{
	position.x += 10;
}

void mog::Pawn::initialRegisteredMethods()
{
	registerMethod("moveUp", std::bind(&mog::Pawn::moveUp, this));
}
