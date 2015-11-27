#pragma once

#include <string>

namespace mog
{
	namespace network
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

			const char *getData() const;
			unsigned getSize() const;

		private:
			std::string data;
		};
	}
}
