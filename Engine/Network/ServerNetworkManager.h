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

			virtual void update(float dt  = 0) override;

			virtual void addNetworkGameObject(NetworkGameObject *o) override;

			virtual void executeMessage(const Message &message, const ParameterContainer &parameters, const InternetAddress &senderAddress) override;

			void addClient(const InternetAddress *address);
			//NOTE: For testing
			std::vector<const InternetAddress *> getClients() const;

		private:
			void processReplications();

		private:
			std::vector<ClientReplicationInfo *> clientReplicationInfos;

			unsigned lastNetworkGameObjectId = 0;
		};
	}
}


