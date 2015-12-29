#pragma once

#include "Engine/Network/GameSocket.h"
#include <winsock2.h>
#include <ws2tcpip.h>


namespace mog
{
	namespace network
	{

		class UDPGameSocket : public GameSocket
		{
		public:

			UDPGameSocket();
			~UDPGameSocket();

			void open(unsigned short port) override;
			void close()override;
			bool isOpen() const override;
			bool send(const Address &destination,
				const char * data,
				int size) override;
			int receive(Address &sender,
				void * data,
				int size) override;

			static bool setup();
			static bool teardown();


		private:
			SOCKET socket = 0;

		};
	}
}