#pragma once

#include "Engine/Types.h"
#include "Network/NetworkGameObject.h"
#include "Engine/NetworkComponent.h"
#include <map>

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

			void addClient(const InternetAddress *address);

			bool setup();
			bool teardown();

			void addNetworkGameObject(NetworkGameObject *o);
			void addNetworkComponent(NetworkComponent *c);

		private:
			NetworkManager();
			~NetworkManager();

			ID extractMessageId(char* message, unsigned size);
			Buffer extractMessageData(char* message, unsigned size);

			void processMessages();
			void processReplications();

		private:
			GameSocket *socket = nullptr;

			unsigned lastNetworkGameObjectId = 0;
			unsigned lastNetworkComponentId = 0;
			std::map<unsigned, NetworkGameObject *> networkGameObjects;
			std::map<unsigned, NetworkComponent *> networkComponents;

			std::vector<const InternetAddress *> clientAddresses;

		private:
			static NetworkManager *manager;
		};
	}
}