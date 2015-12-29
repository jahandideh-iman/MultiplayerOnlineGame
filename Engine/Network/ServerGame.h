#pragma once

#include "Engine/Network/NetworkGame.h"
#include "Engine/Network/PlayerInfo.h"

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

			//Note: For testing.
			const PlayerInfo *getPlayerInfoByName(std::string name) const;

		private:

			std::vector<PlayerInfo*> playersInfo;
		};
	}
}
