#include "Pawn.h"
#include "SpriteComponent.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Network/ClientGame.h"
#include "Engine/Network/ServerGame.h"
#include "InputComponent.h"
#include "Core/Macros.h"

#include <math.h>

#include "cocos2d.h"

#include "Bullet.h"

mog::Pawn::Pawn()
{
	addComponent(new SpriteComponent("sprite",this,"pawn.png"));

	getNetworkComponent()->addVariable("health", &health);

}

mog::Pawn::~Pawn()
{
}

void mog::Pawn::moveUpPressed()
{
	setVelocityY(getVelocity().getY() + speed.getValue());
}
void mog::Pawn::moveUpReleased()
{
	setVelocityY(getVelocity().getY() - speed.getValue());
}

void mog::Pawn::moveDownPressed()
{
	setVelocityY(getVelocity().getY() - speed.getValue());
}

void mog::Pawn::moveDownReleased()
{
	setVelocityY(getVelocity().getY() + speed.getValue());
}

void mog::Pawn::moveLeftPressed()
{
	setVelocityX(getVelocity().getX() - speed.getValue());
}

void mog::Pawn::moveLeftReleased()
{
	setVelocityX(getVelocity().getX() + speed.getValue());
}

void mog::Pawn::moveRightPressed()
{
	setVelocityX(getVelocity().getX() + speed.getValue());
}

void mog::Pawn::moveRightReleased()
{
	setVelocityX(getVelocity().getX() - speed.getValue());
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

	registerMethod("shoot", std::bind(&mog::Pawn::shoot, this));
}

void mog::Pawn::shoot()
{
	getOwner()->addGameObject(new Bullet(this,getRoation(),getPosition()+ Point(0,0)));
}

void mog::Pawn::addInputComponent()
{
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

	input->addOnPressAction(cocos2d::EventKeyboard::KeyCode::KEY_SPACE, [this](){
		auto clientGame = dynamic_cast<mog::network::ClientGame *> (this->getOwner());
		if (clientGame != nullptr)
			clientGame->callRemoteMethod("shoot", this);
	});

	addComponent(input);
}

void mog::Pawn::onAddedToGame(Game *game)
{
	NetworkPawn::onAddedToGame(game);
	if (this->getRole() == network::Role_Proxy)
		addInputComponent();
		
}

void mog::Pawn::updatePosition(float dt)
{
	if (PREDICION_ON)
		GameObject::updatePosition(dt);
	else
	{
		if (dynamic_cast<network::NetworkGame *> (getOwner()) == nullptr)
			GameObject::updatePosition(dt);
		else
		{
			if (dynamic_cast<network::ServerGame *> (getOwner()) != nullptr)
				GameObject::updatePosition(dt);
		}
	}

}
