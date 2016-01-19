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
			virtual ~NetworkManager();

			virtual void update(float dt = 0);

			void sendMessage(const Message &m, const InternetAddress &address);

			void setPort(unsigned port);
			template<typename T>
			bool initialSocket() { socket = new T(); return true; }

			virtual void addNetworkGameObject(NetworkGameObject *object);
			virtual void removeNetworkGameObject(NetworkGameObject *object);
			NetworkGameObject *findNetworkGameObject(unsigned instaceId) const;
		
			virtual void executeMessage(const Message &meesage, const ParameterContainer &parameters, const InternetAddress &senderAddress) = 0;

			//NOTE: For testing
			bool hasNetworkGameObject(const NetworkGameObject *gameObj) const;
			//NOTE: For testing
			bool hasNetworkGameObject(unsigned instanceId) const;
			//NOTE: For testing
			std::vector<const NetworkGameObject *> getNetworkGameObjects() const;

			//NOTE: For testing
			void setSocket(GameSocket *socket);

		private:
			ID extractMessageId(char* message, unsigned size);
			Buffer extractMessageData(char* message, unsigned size);

			void processMessages();

		protected:
			NetworkGame *game = nullptr;
			std::map<unsigned, NetworkGameObject *> networkGameObjects;

		private:
			GameSocket *socket = nullptr;

		};
	}
}