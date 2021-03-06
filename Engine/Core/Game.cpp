#include "Game.h"

#include <assert.h>


mog::Game::Game()
{
}


mog::Game::~Game()
{
	for (auto o : gameObjects)
		delete o;
	//gameObjects.clear();
}

void mog::Game::loadLevel(Level *level)
{
	currentLevel = level;
	for (GameObject *o : level->getGameObjects())
	{
		addGameObject(o);
	}
	level->setIsloaded(true);
}

void mog::Game::addGameObject(GameObject *object)
{
	assert(object->getOwner() == nullptr);

	gameObjects.push_back(object);
	object->privateOnAddedToGame(this);
}

void mog::Game::update(float dt)
{
	for (GameObject * o : gameObjects)
		o->update(dt);

	internalUpdate(dt);

	while (!toBeRemovedAtEndOfUpdate.empty())
	{
		auto obj = toBeRemovedAtEndOfUpdate.begin();
		removeGameObject(*obj);
		toBeRemovedAtEndOfUpdate.erase(obj);
	}
}

void mog::Game::internalUpdate(float dt)
{

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

const std::vector<mog::GameObject *> &mog::Game::getGameObjects()
{
	return gameObjects;
}

void mog::Game::removeGameObject(GameObject *object)
{
	assert(this == object->getOwner());

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		if (*it == object)
		{
			gameObjects.erase(it);
			object->onRemovedFromGame(this);
			delete object;
			break;
		}
	}
}

void mog::Game::removeGameObjectAtEndOfUpdate(GameObject *object)
{
	toBeRemovedAtEndOfUpdate.push_back(object);
}
