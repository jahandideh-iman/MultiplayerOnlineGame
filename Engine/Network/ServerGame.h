#pragma once

#include "Engine/Network/NetworkGame.h"
#include "Engine/Network/Client.h"

namespace mog
{
	namespace network
	{
		class NetworkPawn;

		class ServerGame : public NetworkGame
		{
		public:
			ServerGame();
			~ServerGame();

			void joinNewPlayer(Client *info);
			void removePlayer(const Client *info);

			NetworkGameType getType() const final override{ return Type_Server; }

			//Note: For testing.
			const Client *getPlayerInfoByName(std::string name) const;
			//Note: For testing.
			bool hasClient(const Client* info) const;

		protected:
			virtual void  onPawnCreated(NetworkPawn *p){}

		private:

			std::vector<Client*> playersInfo;
		};
	}
}
