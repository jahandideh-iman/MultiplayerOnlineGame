#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockLevel.h"

#include "Engine/Network/ServerGame.h"
#include "Engine/Network/NetworkPawn.h"
#include "Engine/Network/NetworkPawnFactory.h"

#include "Engine/Core/LevelFactory.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Core/LevelDatabase.h"


namespace mog
{
	namespace network
	{
		class MockServerGame : public ServerGame
		{
		public:
			bool isOnPawnCreatedCalled = false;

			void onPawnCreated(NetworkPawn *p)
			{
				isOnPawnCreatedCalled = true;
			}
		};
		TEST_GROUP_BASE(ServerGame,NetworkBase)
		{

			void teardown() override
			{
				NetworkBase::teardown();
				NetworkPawnFactory::clear();
				LevelDatabase::clear();
				LevelFactory::clear();
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

		TEST(ServerGame, CallsOnPawnCreatedWhenPlayerJoined)
		{
			MockServerGame serverGame;

			auto info = new PlayerInfo(std::string("player"), new InternetAddress());
			serverGame.joinNewPlayer(info);

			CHECK_TRUE(serverGame.isOnPawnCreatedCalled);
		}

		TEST(ServerGame, LoadsGivenLevelInClientWhenPlayerJoined)
		{
			REGISTER_LEVEL(MockLevel);
			REGISTER_MESSAGE(LoadLevelMessage);

			LevelFactory::get()->setObject<MockLevel>();
			MockLevel level;
			level.initialGameObjects();

			serverGame->joinNewPlayer(new PlayerInfo(std::string("player1"), new InternetAddress(clientAddress1)));
			clientManager1->update();

			CHECK_TRUE(gameHasLevelObjects(clientGame1, &level));
			CHECK_FALSE(gameHasLevelObjects(serverGame, &MockLevel()));

			LevelFactory::clear();
		}
	}
}