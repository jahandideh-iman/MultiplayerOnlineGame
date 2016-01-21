#include "GameLevel.h"
#include "SpriteComponent.h"

#include "CCClientGame.h"
#include <assert.h>

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

	auto ccNetGame = dynamic_cast<CCNetworkGame*> (game);
	assert(ccNetGame != nullptr);
	auto ccClientGame = dynamic_cast<CCClientGame*> (ccNetGame->getGame());

	assert(ccClientGame != nullptr);

	auto size = ccClientGame->getVisibleSize();
	o->setPosition(Point(size.width * 0.5, size.height *0.5));

}

