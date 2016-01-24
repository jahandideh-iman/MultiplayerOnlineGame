#include "ReplicablePoint.h"
#include "Engine/Core/ParameterContainer.h"
#include <string>


mog::ReplicablePoint::ReplicablePoint()
{
}

mog::ReplicablePoint::ReplicablePoint(float x, float y) : Point(x, y)
{

}


void mog::ReplicablePoint::read(const Buffer *buffer)
{
	ParameterContainer c(buffer);
	setX(atoi(c.get("x").c_str()));
	setY(atoi(c.get("y").c_str()));
}

void mog::ReplicablePoint::write(Buffer *buffer) const
{
	ParameterContainer c;
	c.put("x", std::to_string(getX()));
	c.put("y", std::to_string(getY()));

	c.write(buffer);
}

mog::ReplicablePoint & mog::ReplicablePoint::operator=(const Point &other)
{
	setX(other.getX());
	setY(other.getY());
	return *this;
}

void mog::ReplicablePoint::setX(float x)
{
	if (x != getX())
	{
		Point::setX(x);
		setDirty(true);
	}
}

void mog::ReplicablePoint::setY(float y)
{
	if (y != getY())
	{
		Point::setY(y);
		setDirty(true);
	}
}

void mog::ReplicablePoint::add(Replicable *r)
{
	auto rp = dynamic_cast<ReplicablePoint *> (r);
	setX(getX() + rp->getX());
	setY(getY() + rp->getY());
}

void mog::ReplicablePoint::minus(Replicable *r)
{
	auto rp = dynamic_cast<ReplicablePoint *> (r);
	setX(getX() - rp->getX());
	setY(getY() - rp->getY());
}

void mog::ReplicablePoint::multiply(float r)
{
	setX(getX() * r);
	setY(getY() * r);
}

void mog::ReplicablePoint::setValue(Replicable *r)
{
	auto rp = dynamic_cast<ReplicablePoint *> (r);
	setX(rp->getX());
	setY(rp->getY());
}

mog::ReplicablePoint::~ReplicablePoint()
{
}
