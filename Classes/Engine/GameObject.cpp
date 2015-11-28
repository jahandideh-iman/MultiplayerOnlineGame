#include "GameObject.h"
#include "Game.h"

using mog::GameObject;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (Component *c : components)
		delete c;
}

std::vector<mog::Component *> GameObject::getComponents()
{
	return components;
}

void mog::GameObject::addComponent(Component *c)
{
	components.push_back(c);
}

void mog::GameObject::addSelfToGame(Game *game)
{
	for (Component *o : getComponents())
	{
		o->addSelfToGame(game);
	}
}

void mog::GameObject::setPosition(Point pos)
{

}
