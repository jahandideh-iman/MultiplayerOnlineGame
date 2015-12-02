#include "Level.h"

using mog::Level;
using mog::GameObject;

Level::Level()
{
}


Level::~Level()
{
	for (GameObject *o : objects)
		delete o;
}

void mog::Level::addGameObject(GameObject *object)
{
	objects.push_back(object);
}

std::vector<GameObject *> mog::Level::getGameObjects()
{
	return objects;
}
