#include "ParameterContainer.h"
#include "Engine/Buffer.h"

mog::ParameterContainer::ParameterContainer()
{
}

mog::ParameterContainer::ParameterContainer(Buffer &buffer)
{
	initialWithBuffer(buffer);
}


mog::ParameterContainer::~ParameterContainer()
{
}


void mog::ParameterContainer::put(std::string name, std::string value)
{
	parameters.emplace(name, value);
}

std::string mog::ParameterContainer::get(std::string name) const
{
	return parameters.find(name)->second;
}

void mog::ParameterContainer::initialWithBuffer(Buffer &buffer)
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

mog::Buffer *mog::ParameterContainer::write(Buffer *buffer) const
{
	for (auto it = parameters.begin(); it != parameters.end(); ++it)
	{
		buffer->write(it->first + "\n" + it->second + "\n");
	}
	return buffer;
}
