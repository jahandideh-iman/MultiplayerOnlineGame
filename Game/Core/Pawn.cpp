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

	input->addOnPressAction(cocos2d::EventKeyboard::KeyCode::KEY_W, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveUpPressed", this);
	});

	input->addOnPressAction(cocos2d::EventKeyboard::KeyCode::KEY_S, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveDownPressed", this);
	});

	input->addOnPressAction(cocos2d::EventKeyboard::KeyCode::KEY_A, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveLeftPressed", this);
	});

	input->addOnPressAction(cocos2d::EventKeyboard::KeyCode::KEY_D, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveRightPressed", this);
	});

	input->addOnReleaseAction(cocos2d::EventKeyboard::KeyCode::KEY_W, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveUpReleased", this);
	});

	input->addOnReleaseAction(cocos2d::EventKeyboard::KeyCode::KEY_S, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveDownReleased", this);
	});

	input->addOnReleaseAction(cocos2d::EventKeyboard::KeyCode::KEY_A, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveLeftReleased", this);
	});

	input->addOnReleaseAction(cocos2d::EventKeyboard::KeyCode::KEY_D, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("moveRightReleased", this);
	});

	addComponent(input);
}

mog::Pawn::~Pawn()
{
}

void mog::Pawn::moveUpPressed()
{
	setVelocityY(getVelocity().y + speed.getValue());
}
void mog::Pawn::moveUpReleased()
{
	setVelocityY(getVelocity().y - speed.getValue());
}

void mog::Pawn::moveDownPressed()
{
	setVelocityY(getVelocity().y - speed.getValue());
}

void mog::Pawn::moveDownReleased()
{
	setVelocityY(getVelocity().y + speed.getValue());
}

void mog::Pawn::moveLeftPressed()
{
	setVelocityX(getVelocity().x - speed.getValue());
}

void mog::Pawn::moveLeftReleased()
{
	setVelocityX(getVelocity().x + speed.getValue());
}

void mog::Pawn::moveRightPressed()
{
	setVelocityX(getVelocity().x + speed.getValue());
}

void mog::Pawn::moveRightReleased()
{
	setVelocityX(getVelocity().x - speed.getValue());
}

void mog::Pawn::initialRegisteredMethods()
{
	registerMethod("moveUpPressed", std::bind(&mog::Pawn::moveUpPressed, this));
	registerMethod("moveUpReleased", std::bind(&mog::Pawn::moveUpReleased, this));

	registerMethod("moveDownPressed", std::bind(&mog::Pawn::moveDownPressed, this));
	registerMethod("moveDownReleased", std::bind(&mog::Pawn::moveDownReleased, this));

	registerMethod("moveLeftPressed", std::bind(&mog::Pawn::moveLeftPressed, this));
	registerMethod("moveLeftReleased", std::bind(&mog::Pawn::moveLeftReleased, this));

	registerMethod("moveRightPressed", std::bind(&mog::Pawn::moveRightPressed, this));
	registerMethod("moveRightReleased", std::bind(&mog::Pawn::moveRightReleased, this));

}
