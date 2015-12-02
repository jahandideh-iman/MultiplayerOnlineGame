#include "ReplicateState.h"
#include "Engine/Macros.h"


mog::network::ReplicateState::ReplicateState()
{
}

mog::network::ReplicateState::ReplicateState(unsigned componentIndex, Buffer *variables)
{
	this->variables = variables;
	this->componentIndex = componentIndex;
}


mog::network::ReplicateState::~ReplicateState()
{
}

void mog::network::ReplicateState::fillData(ParameterContainer &parameters) const
{
	parameters.put("index", std::to_string(componentIndex));
	parameters.put("varibles", variables->getData());
}

void mog::network::ReplicateState::execute(const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	MOGLOG("Replicate Instance Message \n %s", parameters.write(&Buffer())->getData());
}
