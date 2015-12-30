#include "ParameterContainer.h"
#include "Engine/Core/Buffer.h"
#include <algorithm>
#include <cctype>

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
	auto res = parameters.find(name);
	if (res == parameters.end())
		return "";
	return parameters.find(name)->second;
}

void mog::ParameterContainer::initialWithBuffer(Buffer &buffer)
{
	char *line = new char[buffer.getSize()];

	std::string data;
	while (!buffer.eof())
	{
		buffer.readLine(line, buffer.getSize());
		data += line;
	}
	
	data = data.substr(data.find_first_of("{")+1, data.find_last_of("}") - 1);

	auto pairs = getTokens(data, ",");

	for (auto p : pairs)
	{
		auto pair = getTokens(p, ":");

		pair[0].erase(std::remove_if(pair[0].begin(), pair[0].end(), std::isspace), pair[0].end());
		pair[1].erase(std::remove_if(pair[1].begin(), pair[1].end(), std::isspace), pair[1].end());

		put(pair[0], pair[1]);
	}

	delete[]line;
}

mog::Buffer *mog::ParameterContainer::write(Buffer *buffer) const
{
	bool isFirst = true;
	buffer->write("{");
	for (auto it = parameters.begin(); it != parameters.end(); ++it)
	{
		if (isFirst == false)
			buffer->write(",");
		buffer->write(it->first + " : " + it->second);
		isFirst = false;
	}
	buffer->write("}");
	return buffer;
}

bool mog::ParameterContainer::operator==(const ParameterContainer &other) const
{
	if (other.parameters.size() != this->parameters.size())
		return false;

	for (auto parameter : this->parameters)
	{
		if (parameter.second != other.get(parameter.first))
			return false;
	}

	return true;
}

bool mog::ParameterContainer::operator!=(const ParameterContainer &other) const
{
	return !this->operator==(other);
}

std::vector<std::string> mog::ParameterContainer::getTokens(std::string str, std::string delimiters)
{
	std::vector<std::string> res;
	char *chars = new char[str.size() + 1];
	strcpy_s(chars, str.size() + 1, str.c_str());

	char * token;
	token = strtok(chars, delimiters.c_str());
	while (token != NULL)
	{
		res.push_back(token);
		token = strtok(NULL, delimiters.c_str());
	}
	delete[]chars;
	return res;
}
