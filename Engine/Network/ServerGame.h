#pragma once

#include "Network/NetworkGame.h"
#include "Network/PlayerInfo.h"

namespace mog
{
	namespace network
	{
		class ServerGame : public NetworkGame
		{
		public:
			ServerGame();
			~ServerGame();

			void joinNewPlayer(PlayerInfo *info);

			NetworkGameType getType() const final override{ return T_Server; }
		private:

			std::vector<PlayerInfo*> playersInfo;
		};
	}
}
