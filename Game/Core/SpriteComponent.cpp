#include "SpriteComponent.h"
#include "Engine/Core/Game.h"
#include "Engine/Core/GameObject.h"



mog::SpriteComponent::SpriteComponent(ID id, const GameObject *owner, const std::string &fileName) : Component(id, owner)
{
	this->sprite = cocos2d::Sprite::create(fileName);
}

mog::SpriteComponent::~SpriteComponent()
{
	//TODO: write this.
}

void mog::SpriteComponent::addSelfToGame(Game *g)
{
	//g->addChild(sprite, sprite->getLocalZOrder());
}

void mog::SpriteComponent::update(float dt)
{
	sprite->setPositionX(owner->getPosition().x);
	sprite->setPositionY(owner->getPosition().y);
}
