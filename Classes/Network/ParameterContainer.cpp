#include "ParameterContainer.h"


mog::network::ParameterContainer::ParameterContainer()
{
}

mog::network::ParameterContainer::ParameterContainer(Buffer &buffer)
{
	initialWithBuffer(buffer);
}


mog::network::ParameterContainer::~ParameterContainer()
{
}


void mog::network::ParameterContainer::put(std::string name, std::string value)
{
	parameters.emplace(name, value);
}

mog::network::Buffer *mog::network::ParameterContainer::serialize() const
{
	auto buffer = new Buffer();
	for (auto it = parameters.begin(); it != parameters.end(); ++it)
	{
		buffer->write(it->first +"\n" + it->second + "\n");
	}
	return buffer;
}

std::string mog::network::ParameterContainer::get(std::string name) const
{
	return parameters.find(name)->second;
}

void mog::network::ParameterContainer::initialWithBuffer(Buffer &buffer)
{
	char line[256];
	while (!buffer.eof())
	{
		buffer.readLine(line, 256);
		std::string name(line);

		buffer.readLine(line, 256);
		std::string value(line);

		put(name, value);
	}
}
