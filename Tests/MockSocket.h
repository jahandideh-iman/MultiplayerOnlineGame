#pragma once

#include "Engine/Network/GameSocket.h"
#include "Engine/Core/Buffer.h"

#include <map>
#include <vector>
#include <string>

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

			void storeMessage(unsigned senderPort, const char * data);

		private:
			unsigned port;

			std::map<unsigned, std::vector<std::string> > messages;
			MockSocketDataBase *db;

		};
	}
}
