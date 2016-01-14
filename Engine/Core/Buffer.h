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
		Buffer(std::string data);

		~Buffer();

		void write(const std::string &s);
		void write(const Buffer &other);
		void write(const char* c);

		//void readLine(char *line, int length);

		bool isEmpty() const;
		void clear();

		char *getData() const;
		unsigned getSize() const;

	private:
		//std::string data;
		std::stringstream stream;
	};
}
