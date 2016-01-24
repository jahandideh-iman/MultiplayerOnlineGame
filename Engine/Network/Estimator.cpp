#include "Estimator.h"


mog::network::Estimator::Estimator()
{
}


mog::network::Estimator::~Estimator()
{
}

void mog::network::Estimator::setCurrentTime(float time)
{
	this->time = time;
}

void mog::network::Estimator::setVar(Replicable *var)
{
	this->var = var;
}
