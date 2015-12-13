#pragma once

#include "Network/NetworkGame.h"

namespace mog
{
	namespace network
	{
		class ClientGame : public NetworkGame
		{
		public:
			ClientGame();
			~ClientGame();

			NetworkGameType getType() const final override { return T_Client; }
		};
	}
}
