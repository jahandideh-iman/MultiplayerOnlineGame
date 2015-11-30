#pragma once

#include "Engine/Types.h"
#include "Network/NetworkGameObject.h"
#include "Engine/NetworkComponent.h"
#include <map>
#include "Engine/Buffer.h"

namespace mog
{
	namespace network
	{
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

			void addNetworkGameObject(NetworkGameObject *o);
			void addNetworkComponent(NetworkComponent *c);

		private:
			NetworkManager();
			~NetworkManager();

			ID extractMessageId(char* message, unsigned size);
			Buffer extractMessageData(char* message, unsigned size);

		private:
			GameSocket *socket = nullptr;

			unsigned id = 0;
			std::map<unsigned, NetworkGameObject*> networkGameObjects;

		private:
			static NetworkManager *manager;
		};
	}
}