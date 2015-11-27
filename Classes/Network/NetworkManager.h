#pragma once

#include "Engine/Types.h"

namespace mog
{
	namespace network
	{
		class Buffer;
		class GameSocket;
		class Message;
		class InternetAddress;

		class NetworkManager
		{
		public:
			static NetworkManager *get();

			void update(float dt);

			void setPort(unsigned port);

			void sendMessage(const Message &m, const InternetAddress &address);

			bool setup();
			bool teardown();

		private:
			NetworkManager();
			~NetworkManager();

			ID extractMessageId(char* message, unsigned size);
			Buffer extractMessageData(char* message, unsigned size);

		private:
			GameSocket *socket = nullptr;

		private:
			static NetworkManager *manager;
		};
	}
}