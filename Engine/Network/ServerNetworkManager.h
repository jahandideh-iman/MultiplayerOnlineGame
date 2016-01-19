#pragma once

#include "Engine/Network/NetworkManager.h"

namespace mog
{
	namespace network
	{
		class ServerGame;
		class ClientReplicationInfo;

		class ServerNetworkManager : public NetworkManager
		{
		public:
			ServerNetworkManager(ServerGame *game);
			virtual ~ServerNetworkManager();

			void update(float dt  = 0) override;

			void addNetworkGameObject(NetworkGameObject *object) override;
			void removeNetworkGameObject(NetworkGameObject *object) override;

			void executeMessage(const Message &message, const ParameterContainer &parameters, const InternetAddress &senderAddress) override;

			void addClient(const InternetAddress *address);
			void removeClient(const InternetAddress *address);

			//NOTE: For testing
			std::vector<const InternetAddress *> getClients() const;
			//NOTE: For testing
			bool hasClient(const InternetAddress *address) const;

		private:
			void processInstanceReplications();
			void processInstanceRemoval();
			void processStateReplications();

		private:
			std::vector<ClientReplicationInfo *> clientReplicationInfos;

			unsigned lastNetworkGameObjectId = 0;
		};
	}
}


