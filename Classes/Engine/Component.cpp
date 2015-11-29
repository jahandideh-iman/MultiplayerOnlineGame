#include "Component.h"


mog::Component::Component(ID id, const GameObject *owner)
{
	setId(id);
	this->owner = owner;
}


mog::Component::~Component()
{
}

mog::ID mog::Component::getId() const
{
	return id;
}

void mog::Component::setId(ID id)
{
	this->id = id;
}

const mog::GameObject * mog::Component::getOwner()
{
	return owner;
}
