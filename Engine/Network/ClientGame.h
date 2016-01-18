#pragma once

#include "Engine/Network/NetworkGame.h"
#include "Engine/Network/InternetAddress.h"

namespace mog
{
	namespace network
	{
		class NetworkGameObject;
		class ClientGame : public NetworkGame
		{
		public:
			ClientGame();
			~ClientGame();
			
			void remoteMethodCall(std::string method, const NetworkGameObject *obj);

			NetworkGameType getType() const final override { return T_Client; }

			InternetAddress getServerAddress();

		protected:
			void setServerAddress(InternetAddress address);
		private:
			InternetAddress serverAddress;
		};
	}
}
