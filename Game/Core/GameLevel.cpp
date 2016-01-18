#include "GameLevel.h"
#include "SpriteComponent.h"

using mog::GameLevel;

GameLevel::GameLevel()
{
	
}


GameLevel::~GameLevel()
{
}

void mog::GameLevel::initialGameObjects()
{
	GameObject * o = new GameObject();
	o->addComponent(new SpriteComponent("sprite", o, "background.png"));
	addGameObject(o);
}

