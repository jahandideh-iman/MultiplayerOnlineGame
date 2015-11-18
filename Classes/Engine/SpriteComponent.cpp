#include "SpriteComponent.h"
#include "Game.h"

using mog::SpriteComponent;
using mog::Game;

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::SpriteComponent(cocos2d::Sprite *sprite)
{
	this->sprite = sprite;
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::addSelfToGame(Game *g)
{
	g->addChild(sprite, sprite->getZOrder());
}
