#include "Message.h"

using mog::network::Message;

Message::Message()
{
}


Message::~Message()
{
}

mog::Buffer * mog::network::Message::serialize() const
{
	auto parameters = new ParameterContainer();
	fillData(parameters);
	return parameters->serialize();
}
