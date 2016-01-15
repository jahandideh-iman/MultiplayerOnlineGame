#include "ParameterContainer.h"
#include "Engine/Core/Buffer.h"
#include <algorithm>
#include <cctype>
#include <assert.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


mog::ParameterContainer::ParameterContainer()
{
}

mog::ParameterContainer::ParameterContainer(const Buffer *buffer)
{
	initialWithBuffer(buffer);
}


mog::ParameterContainer::~ParameterContainer()
{
}


void mog::ParameterContainer::put(std::string name, std::string value)
{
	if (value[0] != '{')
		value = quote(value);
	parameters.emplace(quote(name), value);
}

std::string mog::ParameterContainer::get(std::string name) const
{
	auto res = parameters.find(quote(name));
	if (res == parameters.end())
		return "";
	if (res->second[0] != '{')
		return unquote(res->second);
	else
		return res->second;
}

void mog::ParameterContainer::initialWithBuffer(const Buffer *buffer)
{
	char *data = buffer->getData();

	rapidjson::Document jsonDoc;
	jsonDoc.Parse<0>(data);
	assert(jsonDoc.HasParseError() == false);

	for (auto itr = jsonDoc.MemberBegin(); itr != jsonDoc.MemberEnd(); ++itr)
	{
		if (itr->value.IsString())
			put(itr->name.GetString(), itr->value.GetString());
		else
		{
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			itr->value.Accept(writer);

			put(itr->name.GetString(), buffer.GetString());
			buffer.Clear();
		}
	}

	delete []data;
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
		if (this->get(unquote(parameter.first)) != other.get(unquote(parameter.first)))
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

std::string mog::ParameterContainer::quote(const std::string &str) const
{
	return "\"" + str + "\"";
}

std::string mog::ParameterContainer::unquote(const std::string &str) const
{
	return str.substr(str.find_first_of("\"") + 1, str.find_last_of("\"") - 1);
}
