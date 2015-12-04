#include "GameLevel.h"
#include "SpriteComponent.h"

using mog::GameLevel;

GameLevel::GameLevel()
{
	GameObject * o = new GameObject();
	o->addComponent(new SpriteComponent("sprite",o,"background.png"));
	addGameObject(o);
}


GameLevel::~GameLevel()
{
}

char * mog::GameLevel::getName() const
{
	return "level1";
}
