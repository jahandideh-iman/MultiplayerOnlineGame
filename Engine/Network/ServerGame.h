#pragma once

#include "Engine/Network/NetworkGame.h"
#include "Engine/Network/PlayerInfo.h"

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

			void joinNewPlayer(PlayerInfo *info);

			NetworkGameType getType() const final override{ return T_Server; }

			//Note: For testing.
			const PlayerInfo *getPlayerInfoByName(std::string name) const;

		protected:
			virtual void  onPawnCreated(NetworkPawn *p){}

		private:

			std::vector<PlayerInfo*> playersInfo;
		};
	}
}
