#include "Game.h"
#include "GlobalData.h"


mog::Game::Game()
{
	GlobalData::get()->setGame(this);
}


mog::Game::~Game()
{
	GlobalData::get()->clear();

	for (auto o : gameObjects)
		delete o;
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

bool mog::Game::has(const GameObject *object) const
{
	for (auto o : gameObjects)
	{
		if (o == object)
			return true;
	}
	return false;
}



