#pragma once

#include "Engine/Network/GameSocket.h"
#include "Engine/Core/Buffer.h"

namespace mog
{
	namespace network
	{
		class MockSocketDataBase;

		class MockSocket : public network::GameSocket
		{
		public:

			MockSocket(MockSocketDataBase *db);
			~MockSocket();

			virtual void open(unsigned short port) override;
			virtual bool send(const Address &destination, const char * data, int size);
			virtual int receive(Address &sender, void * data, int size);

		private:
			unsigned short port;
			Buffer buffer;
			MockSocketDataBase *db;

		};
	}
}
