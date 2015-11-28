#include "Buffer.h"


mog::network::Buffer::Buffer()
{
}


mog::network::Buffer::~Buffer()
{
}

mog::network::Buffer::Buffer(char *data, unsigned size)
{
	//this->data.append(data, size);
	stream.write(data, size);
}

mog::network::Buffer::Buffer(char *data)
{
	//this->data.append(data);
	stream<<data;
}

void mog::network::Buffer::write(const std::string &s)
{
	stream << s;
	//data.append(s);
}

void mog::network::Buffer::write(const Buffer &other)
{
	//data.append(other.getData(), other.getSize());
	stream.write(other.getData(), other.getSize());
}

void mog::network::Buffer::write(const char* c)
{
	stream << c;
}

char * mog::network::Buffer::getData() const
{
	char * data = new char[getSize()];
	strcpy(data, stream.str().c_str());
	return data;
	//return stream.str().c_str();
}

unsigned mog::network::Buffer::getSize() const
{
	return stream.str().size();
}

bool mog::network::Buffer::eof() const
{
	return stream.eof();
}

void mog::network::Buffer::readLine(char *line, int length)
{
	stream.getline(line, length);
}
