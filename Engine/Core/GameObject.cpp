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
	components.clear();
}

std::vector<mog::Component *> GameObject::getComponents()
{
	return components;
}

void mog::GameObject::addComponent(Component *c)
{
	components.push_back(c);
}

void mog::GameObject::addComponentsToGame(Game *game)
{
	for (Component *o : getComponents())
	{
		o->addSelfToGame(game);
	}
}

mog::Component * mog::GameObject::findComponent(ID id)
{
	for (auto c : components)
	{
		if (c->getId() == id)
			return c;
	}

	return nullptr;
}

void mog::GameObject::setPosition(Point pos)
{
	position = pos;
}

mog::Point mog::GameObject::getPosition() const
{
	return position;
}

void mog::GameObject::onAddedToGame(Game *game)
{
	this->owner = game;
	addComponentsToGame(game);
}

void mog::GameObject::update(float dt)
{
	for (auto c : components)
		c->update(dt);
}

mog::Game *mog::GameObject::getOwner()
{
	return owner;
}
