#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>


namespace mog
{
	namespace network
	{

		class InternetAddress;

		class GameSocket
		{
			typedef InternetAddress Address;

		public:

			GameSocket();
			~GameSocket();

			bool open(unsigned short port);
			void close();
			bool isOpen() const;
			bool send(const Address &destination,
				const char * data,
				int size);
			int receive(Address &sender,
				void * data,
				int size);

		private:
			SOCKET socket = 0;

		};
	}
}