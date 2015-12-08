#pragma once

#include "InternetAddress.h"

namespace mog
{
	namespace network
	{
		typedef mog::network::InternetAddress Address;

		class GameSocket
		{
		public:

			GameSocket();
			virtual ~GameSocket();

			virtual void open(unsigned short port) = 0;
			virtual void close() {};
			virtual bool isOpen() const { return true; };
			virtual bool send(const Address &destination,
				const char * data,
				int size) = 0;
			virtual int receive(Address &sender,
				void * data,
				int size) = 0;
		};
	}
}
