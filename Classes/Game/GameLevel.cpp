#include "GameLevel.h"
#include "Engine/SpriteComponent.h"
#include "cocos2d.h"

using mog::GameLevel;

GameLevel::GameLevel()
{
	GameObject * o = new GameObject();
	cocos2d::Sprite *s = cocos2d::Sprite::create("background.png");
	o->addComponent(new SpriteComponent(s));
	addGameObject(o);
}


GameLevel::~GameLevel()
{
}

char * mog::GameLevel::getName() const
{
	return "level1";
}
