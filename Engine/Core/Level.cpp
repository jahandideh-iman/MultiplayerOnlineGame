#include "Level.h"

using mog::Level;
using mog::GameObject;

Level::Level()
{
}


Level::~Level()
{
	if (isLoaded == false)
	{
		for (GameObject *o : objects)
			delete o;
	}
}

void mog::Level::addGameObject(GameObject *object)
{
	objects.push_back(object);
}

std::vector<GameObject *> mog::Level::getGameObjects()
{
	return objects;
}

void mog::Level::setIsloaded(bool isLoaded)
{
	if (this->isLoaded == true)
	{
		//TODO: Raise and exception
	}
	else
		this->isLoaded = isLoaded;
}
