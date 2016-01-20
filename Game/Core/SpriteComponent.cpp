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
	
}

void mog::SpriteComponent::addSelfToGame(Game *g)
{
	auto ccGame = dynamic_cast<CCGame*> (g);
	assert(ccGame != nullptr);
	this->ccGame = ccGame;

	ccGame->addChild(sprite, sprite->getLocalZOrder());
}

void mog::SpriteComponent::update(float dt)
{
	Component::update(dt);
	sprite->setPositionX(owner->getPosition().x);
	sprite->setPositionY(owner->getPosition().y);

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
