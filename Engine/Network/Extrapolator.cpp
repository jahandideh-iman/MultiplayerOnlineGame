#include "Extrapolator.h"

#include "Engine/Core/Buffer.h"

mog::network::Extrapolator::Extrapolator(Replicable *var)
{
	setVar(var);
}

mog::network::Extrapolator::Extrapolator()
{

}


mog::network::Extrapolator::~Extrapolator()
{
}

void mog::network::Extrapolator::read(const Buffer *buffer, float time)
{
	char *data;

	data = buffer->getData();

	if (point2.data == "")
	{
		point2.time = time;
		point2.data = data;
	}
	else
	{
		point2.time = point1.time;
		point2.data = point1.data;
	}

	point1.time = time;
	point1.data = data;

	delete []data;
}

void mog::network::Extrapolator::update()
{
	if (point1.data == "" && point2.data == "")
		return;
	auto v1 = var->clone();
	Buffer buffer(point1.data);

	v1->read(&buffer);

	auto v2 = var->clone();
	buffer.clear();
	buffer.write(point2.data);
	v2->read(&buffer);

	float elapedTime = time - point1.time;
	float deltaTime = point1.time - point2.time;

	v2->minus(v1);
	v2->multiply(-1);
	v2->multiply(elapedTime);
	v2->multiply(1.0 / deltaTime);
	v1->add(v2);
	var->setValue(v1);
	delete v1;
	delete v2;
}

