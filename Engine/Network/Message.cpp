#include "Message.h"

using mog::network::Message;

Message::Message()
{
}


Message::~Message()
{
}

void mog::network::Message::write(Buffer *buffer) const
{
	ParameterContainer parameters;
	fillData(parameters);
	parameters.write(buffer);
}
