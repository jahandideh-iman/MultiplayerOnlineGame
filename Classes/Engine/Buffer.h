#pragma once

#include <string>
#include <sstream>

namespace mog
{

	class Buffer
	{
	public:
		Buffer();
		Buffer(char *data);
		Buffer(char *data, unsigned size);

		~Buffer();

		void write(const std::string &s);
		void write(const Buffer &other);
		void write(const char* c);

		void readLine(char *line, int length);
		bool eof() const;

		char *getData() const;
		unsigned getSize() const;

	private:
		//std::string data;
		std::stringstream stream;

	};
}
