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
		private:

			std::vector<PlayerInfo*> playersInfo;
		};
	}
}
