#pragma once
#include "Engine/Core/Game.h"

namespace mog
{
	namespace network
	{
		enum NetworkGameType { T_None, T_Server, T_Client };

		class NetworkManager;

		class NetworkGame : public Game
		{
		public:
			NetworkGame();
			virtual ~NetworkGame();

			virtual NetworkGameType getType() const{ return T_None; }

			NetworkManager *getNetworkManager();

		private:
			NetworkManager *networkManager = nullptr;
		};
	}
}
