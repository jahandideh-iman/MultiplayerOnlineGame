#pragma once

#include "Engine/Network/NetworkManager.h"

namespace mog
{
	namespace network
	{
		class ClientGame;

		class ClientNetworkManager : public NetworkManager
		{
		public:
			ClientNetworkManager(ClientGame *game);
			virtual ~ClientNetworkManager();

			void addNetworkGameObject(NetworkGameObject *object) override;
			void removeNetworkGameObject(NetworkGameObject *object) override;

			void executeMessage(const Message &message, const ParameterContainer &parameters, const InternetAddress &senderAddress) override;
		};

	}
}

