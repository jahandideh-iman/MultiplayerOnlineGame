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

void mog::GameObject::privateOnAddedToGame(Game *game)
{
	this->owner = game;
	onAddedToGame(game);
	addComponentsToGame(game);
}

void mog::GameObject::update(float dt)
{
	for (auto c : components)
		c->update(dt);

	updatePosition(dt);
	updateRotation(dt);
}

void mog::GameObject::updatePosition(float dt)
{
	setPosition(getPosition() + velocity*dt);
}

void mog::GameObject::updateRotation(float dt)
{
	if (getVelocity().getX() != 0 || getVelocity().getY() != 0)
		setRoation(atan2(getVelocity().getY(), getVelocity().getX()) * 180 / M_PI);
}


mog::Game *mog::GameObject::getOwner() const
{
	return owner;
}

void mog::GameObject::onRemovedFromGame(Game *game)
{

}

void mog::GameObject::setRoation(Float r)
{
	rotation = r;
}

mog::Float mog::GameObject::getRoation() const
{
	return rotation;
}

void mog::GameObject::setVelocity(Vector velocity)
{
	this->velocity = velocity;
}

mog::Vector mog::GameObject::getVelocity() const
{
	return velocity;
}

void mog::GameObject::setVelocityX(float x)
{
	velocity.setX(x);
}

void mog::GameObject::setVelocityY(float y)
{
	velocity.setY(y);
}


