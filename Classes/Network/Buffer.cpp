#include "Buffer.h"


mog::network::Buffer::Buffer()
{
}


mog::network::Buffer::~Buffer()
{
}

mog::network::Buffer::Buffer(char *data, unsigned size)
{
	this->data.append(data, size);
}

mog::network::Buffer::Buffer(char *data)
{
	this->data.append(data);
}

void mog::network::Buffer::write(const std::string &s)
{
	data.append(s);
}

void mog::network::Buffer::write(const Buffer &other)
{
	data.append(other.getData(), other.getSize());
}

void mog::network::Buffer::write(const char* c)
{
	data.append(c);
}

const char * mog::network::Buffer::getData() const
{
	return data.c_str();
}

unsigned mog::network::Buffer::getSize() const
{
	return data.size();
}
