#pragma once
#include "Engine/Game.h"

namespace mog
{
	namespace network
	{
		enum NetworkGameType { T_None, T_Server, T_Client };

		class NetworkManager;

		class NetworkGame :
			public Game
		{
		public:
			NetworkGame();
			virtual ~NetworkGame();

			NetworkGameType getType();

			NetworkManager *getNetworkManager();

		private:
			NetworkGameType type = T_None;
			NetworkManager *networkManager = nullptr;
		};
	}
}
