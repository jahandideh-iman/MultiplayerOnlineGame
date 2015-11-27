#include "SpriteComponent.h"
#include "Game.h"



mog::SpriteComponent::SpriteComponent(std::string &fileName)
{
	this->sprite = cocos2d::Sprite::create(fileName);
}

mog::SpriteComponent::~SpriteComponent()
{
	//TODO: write this.
}

void mog::SpriteComponent::addSelfToGame(Game *g)
{
	g->addChild(sprite, sprite->getLocalZOrder());
}
