#pragma once

#include <map>
#include <vector>

namespace mog
{
	class Buffer;

	class ParameterContainer
	{
	public:
		ParameterContainer();
		ParameterContainer(Buffer &buffer);
		~ParameterContainer();

		void put(std::string name, std::string value);
		std::string get(std::string name) const;

		Buffer *write(Buffer *buffer) const;

		void initialWithBuffer(Buffer &buffer);

		bool operator== (const ParameterContainer &other) const;
		bool operator!= (const ParameterContainer &other) const;

	private:
		std::vector<std::string> getTokens(std::string str, std::string delimiters);

		std::string quote(const std::string &str) const;
		std::string unquote(const std::string &str) const;

	private:
		std::map<std::string, std::string> parameters;
	};
}
