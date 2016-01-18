#include "SerializablePoint.h"
#include "Engine/Core/ParameterContainer.h"
#include <string>


mog::SerializablePoint::SerializablePoint()
{
}

mog::SerializablePoint::SerializablePoint(float x, float y) : Point(x, y)
{

}


mog::SerializablePoint::~SerializablePoint()
{
}

void mog::SerializablePoint::read(const Buffer *buffer)
{
	ParameterContainer c(buffer);
	x = atoi(c.get("x").c_str());
	y = atoi(c.get("y").c_str());
}

void mog::SerializablePoint::write(Buffer *buffer) const
{
	ParameterContainer c;
	c.put("x", std::to_string(this->x));
	c.put("y", std::to_string(this->y));

	c.write(buffer);
}

mog::SerializablePoint & mog::SerializablePoint::operator=(const Point &other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}
