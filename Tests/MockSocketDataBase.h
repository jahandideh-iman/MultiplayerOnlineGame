#pragma once

#include <map>

namespace mog
{
	namespace network
	{
		class MockSocket;

		class MockSocketDataBase
		{
		public:
			~MockSocketDataBase();
			MockSocketDataBase();

			void add(unsigned short port, MockSocket *socket);
			MockSocket *find(unsigned short port);

		private:
			std::map<unsigned short, MockSocket*> sockets;
		};
	}
}
