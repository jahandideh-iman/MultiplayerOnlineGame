#include "Buffer.h"


mog::Buffer::Buffer()
{
}


mog::Buffer::~Buffer()
{
}

mog::Buffer::Buffer(char *data, unsigned size)
{
	//this->data.append(data, size);
	stream.write(data, size);
}

mog::Buffer::Buffer(char *data)
{
	//this->data.append(data);
	stream<<data;
}

void mog::Buffer::write(const std::string &s)
{
	stream << s;
	//data.append(s);
}

void mog::Buffer::write(const Buffer &other)
{
	//data.append(other.getData(), other.getSize());
	stream.write(other.getData(), other.getSize());
}

void mog::Buffer::write(const char* c)
{
	stream << c;
}

char * mog::Buffer::getData() const
{
	char * data = new char[getSize()];
	strcpy(data, stream.str().c_str());
	return data;
	//return stream.str().c_str();
}

unsigned mog::Buffer::getSize() const
{
	return stream.str().size();
}

bool mog::Buffer::eof() const
{
	return stream.eof();
}

void mog::Buffer::readLine(char *line, int length)
{
	stream.getline(line, length);
}

bool mog::Buffer::isEmpty() const
{
	return stream.str().empty();
}

void mog::Buffer::clear()
{
	stream.clear();
}
