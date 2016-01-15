#pragma once

#include "Engine/Core/Types.h"
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"
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

			void update(float dt = 0);

			//NOTE: For testing
			void setSocket(GameSocket *socket);

			void setPort(unsigned port);

			void sendMessage(const Message &m, const InternetAddress &address);

			void addClient(const InternetAddress *address);
			//NOTE: For testing
			const std::vector<const InternetAddress *> &getClients() const;

			template<typename T>
			bool initialSocket() { socket = new T(); return true; }


			void addNetworkGameObject(NetworkGameObject *o);
			//void addNetworkComponent(NetworkComponent *c);

			NetworkGameObject * findNetworkGameObjectByInstanceId(unsigned instaceId) const;

			//NOTE: For testing
			bool hasNetworkGameObject(const NetworkGameObject *gameObj) const;

		private:
			ID extractMessageId(char* message, unsigned size);
			Buffer extractMessageData(char* message, unsigned size);

			void processMessages();
			void processReplications();

		private:
			NetworkGame *game = nullptr;
			GameSocket *socket = nullptr;

			unsigned lastNetworkGameObjectId = 0;
			std::map<unsigned, NetworkGameObject *> networkGameObjects;

			std::vector<const InternetAddress *> clientAddresses;

		};
	}
}