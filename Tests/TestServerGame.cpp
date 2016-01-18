#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"

#include "Engine/Network/ServerGame.h"
#include "Engine/Network/NetworkPawn.h"
#include "Engine/Network/NetworkPawnFactory.h"


namespace mog
{
	namespace network
	{
		TEST_GROUP(ServerGame)
		{

			void teardown() override
			{
				NetworkPawnFactory::clear();
			}

			template<class P>
			bool hasPawn(ServerGame *game)
			{
				for (auto o : game->getGameObjects())
				{
					if (dynamic_cast<const P*> (o) != nullptr)
						return true;
				}

				return false;
			}
		};

		TEST(ServerGame, CreatesDefaultNetworkPawnOnPlayerJoinWhenNetworkPawnIsNotSet)
		{
			ServerGame serverGame;

			auto info = new PlayerInfo(std::string("player"), new InternetAddress());
			serverGame.joinNewPlayer(info);

			CHECK_TRUE(hasPawn<NetworkPawn>(&serverGame));
		}

		class CustomNetworkPawn : public NetworkPawn {};

		TEST(ServerGame, CreatesGivenNetworkPawnOnPlayerJoin)
		{
			ServerGame serverGame;

			NetworkPawnFactory::get()->setNetworkPawn<CustomNetworkPawn>();

			auto info = new PlayerInfo(std::string("player"), new InternetAddress());
			serverGame.joinNewPlayer(info);

			CHECK_TRUE(hasPawn<CustomNetworkPawn>(&serverGame));
		}
	}
}