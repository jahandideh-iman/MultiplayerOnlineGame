#pragma once

#include "Engine/Buffer.h"
#include <map>
namespace mog
{
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

	private:
		std::map<std::string, std::string> parameters;
	};
}
