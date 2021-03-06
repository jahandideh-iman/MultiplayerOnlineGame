#include "SpriteComponent.h"
#include "Engine/Core/Game.h"
#include "Engine/Core/GameObject.h"
#include "CCGame.h"
#include <assert.h>


mog::SpriteComponent::SpriteComponent(ID id, const GameObject *owner, const std::string &fileName) : Component(id, owner)
{
	this->sprite = cocos2d::Sprite::create(fileName);
}

mog::SpriteComponent::~SpriteComponent()
{
	if (ccGame != nullptr)
		ccGame->removeChild(sprite);
}

void mog::SpriteComponent::addSelfToGame(Game *g)
{
	auto ccNetGame = dynamic_cast<CCNetworkGame*> (g);
	assert(ccNetGame != nullptr);
	this->ccGame = ccNetGame->getGame();

	ccGame->addChild(sprite, sprite->getLocalZOrder());
}

void mog::SpriteComponent::update(float dt)
{
	Component::update(dt);
	sprite->setPositionX(owner->getPosition().getX());
	sprite->setPositionY(owner->getPosition().getY());

	sprite->setRotation(90 - owner->getRoation().getValue());

	auto rect = cocos2d::CCRectMake(
		sprite->getPosition().x - (sprite->getContentSize().width / 2),
		sprite->getPosition().y - (sprite->getContentSize().height / 2),
		sprite->getContentSize().width,
		sprite->getContentSize().height);


	if (!ccGame->getVisibleViewRect().intersectsRect(rect))
	{
		for (auto c : outOfViewCallbacks)
			c();
	}
}

void mog::SpriteComponent::addOutOfViewCallback(Callback callback)
{
	outOfViewCallbacks.push_back(callback);
}
