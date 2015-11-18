#include "GameObject.h"

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
