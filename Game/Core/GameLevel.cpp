#include "GameLevel.h"
#include "SpriteComponent.h"

#include "CCClientGame.h"

using mog::GameLevel;

GameLevel::GameLevel()
{
	
}


GameLevel::~GameLevel()
{
}

void mog::GameLevel::initialGameObjects(Game *game)
{
	GameObject * o = new GameObject();
	o->addComponent(new SpriteComponent("sprite", o, "background.png"));
	addGameObject(o);

	auto cocosGame = dynamic_cast<CCClientGame*> (game);
	if (cocosGame != nullptr)
	{
		auto size = cocosGame->getVisibleSize();
		o->setPosition(Point(size.width * 0.5, size.height *0.5));
	}

}

