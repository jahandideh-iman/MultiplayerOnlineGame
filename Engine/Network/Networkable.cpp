#include "Networkable.h"

mog::network::Networkable::Networkable()
{

}

mog::network::Networkable::~Networkable()
{

}


void mog::network::Networkable::setInstanceId(unsigned i)
{
	this->instanceId = i;
}

unsigned mog::network::Networkable::getInstanceId() const
{
	return instanceId;
}
