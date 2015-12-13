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
		class NetworkGame;
		class NetworkManager
		{

		public:
			NetworkManager(NetworkGame *game);
			~NetworkManager();

			static NetworkManager *get();
			static void clear();

			void update(float dt);

			void setSocket(GameSocket *socket);

			void setPort(unsigned port);

			void sendMessage(const Message &m, const InternetAddress &address);

			void addClient(const InternetAddress *address);

			template<typename T>
			bool initialSocket() { socket = new T(); return true; }


			void addNetworkGameObject(NetworkGameObject *o);
			void addNetworkComponent(NetworkComponent *c);


		private:


			ID extractMessageId(char* message, unsigned size);
			Buffer extractMessageData(char* message, unsigned size);

			void processMessages();
			void processReplications();

		private:
			NetworkGame *game = nullptr;
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