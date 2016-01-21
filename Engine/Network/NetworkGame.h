#pragma once
#include "Engine/Core/Game.h"

namespace mog
{
	namespace network
	{
		enum NetworkGameType { Type_None, Type_Server, Type_Client };

		class NetworkManager;

		class NetworkGame : public Game
		{
		public:
			NetworkGame();
			virtual ~NetworkGame();

			void internalUpdate(float dt = 0) override;

			virtual NetworkGameType getType() const{ return Type_None; }

			NetworkManager *getNetworkManager();

		protected:
			NetworkManager *networkManager = nullptr;
		};
	}
}
