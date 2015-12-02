#include "Game.h"
#include "GlobalData.h"


mog::Game::Game()
{
	GlobalData::game = this;
}


mog::Game::~Game()
{
	GlobalData::game = nullptr;
}

void mog::Game::loadLevel(Level *level)
{
	currentLevel = level;
	for (GameObject *o : level->getGameObjects())
	{
		addGameObject(o);
	}
}

void mog::Game::addGameObject(GameObject *o)
{
	gameObjects.push_back(o);
	o->onAddedToGame(this);
}

void mog::Game::update(float dt)
{
	for (GameObject * o : gameObjects)
		o->update(dt);
}



