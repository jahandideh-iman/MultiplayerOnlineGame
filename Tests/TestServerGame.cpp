#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockLevel.h"
#include "MockNetworkGameObject.h"

#include "Engine/Network/ServerGame.h"
#include "Engine/Network/NetworkPawn.h"
#include "Engine/Network/NetworkPawnFactory.h"
#include "Engine/Network/ConstructorDatabase.h"

#include "Engine/Core/LevelFactory.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/Messages/RemoveInstanceMessage.h"
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
				ConstructorDatabase::clear();
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

			template<class P>
			bool hasPawnForClient(ServerGame *game, const Client* client)
			{
				for (auto o : game->getGameObjects())
				{
					auto pawn = dynamic_cast<const P*> (o);
					if (pawn != nullptr && pawn->getClient() != nullptr  && *pawn->getClient() == *client)
						return true;
				}

				return false;
			}
		};

		TEST(ServerGame, CreatesDefaultNetworkPawnOnPlayerJoinWhenNetworkPawnIsNotSet)
		{
			ServerGame serverGame;

			auto info = new Client("player", new InternetAddress());
			serverGame.joinNewPlayer(info);

			CHECK_TRUE(hasPawn<NetworkPawn>(&serverGame));
		}

		class CustomNetworkPawn : public NetworkPawn {};

		TEST(ServerGame, CreatesGivenNetworkPawnOnPlayerJoin)
		{
			ServerGame serverGame;

			NetworkPawnFactory::get()->setNetworkPawn<CustomNetworkPawn>();

			auto info = new Client("player", new InternetAddress());
			serverGame.joinNewPlayer(info);

			CHECK_TRUE(hasPawn<CustomNetworkPawn>(&serverGame));
		}

		TEST(ServerGame, CallsOnPawnCreatedWhenPlayerJoined)
		{
			MockServerGame serverGame;

			auto client = new Client("player", new InternetAddress());
			serverGame.joinNewPlayer(client);

			CHECK_TRUE(serverGame.isOnPawnCreatedCalled);
		}

		TEST(ServerGame, SetCreatedPawnClientCorrectly)
		{
			auto client1 = new Client("player1", new InternetAddress(clientAddress1));
			serverGame->joinNewPlayer(client1);

			auto client2 = new Client("player1", new InternetAddress(clientAddress2));
			serverGame->joinNewPlayer(client2);

			CHECK_TRUE(hasPawnForClient<NetworkPawn>(serverGame,client1));
			CHECK_TRUE(hasPawnForClient<NetworkPawn>(serverGame,client2));

		}

		TEST(ServerGame, LoadsGivenLevelInClientWhenPlayerJoined)
		{
			REGISTER_LEVEL(MockLevel);
			REGISTER_MESSAGE(LoadLevelMessage);

			LevelFactory::get()->setObject<MockLevel>();
			MockLevel level;
			level.initialGameObjects(nullptr);

			serverGame->joinNewPlayer(new Client("player1", new InternetAddress(clientAddress1)));
			clientManager1->update();

			CHECK_TRUE(gameHasLevelObjects(clientGame1, &level));
			CHECK_FALSE(gameHasLevelObjects(serverGame, &MockLevel()));

			LevelFactory::clear();
		}

		TEST(ServerGame, RemovesGameObjectFromClientsWhenObjectIsRemovedInServer)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(RemoveInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto networkObject = new MockNetworkGameObject();
			serverGame->addGameObject(networkObject);
			unsigned assignedIndex = networkObject->getInstanceId();

			//NOTE: Client are added to Manager instead of Game to prevent creating Pawn 
			serverManager->addClient(&clientAddress1);
			serverManager->addClient(&clientAddress2);

			serverGame->update();
			clientGame1->update();
			clientGame2->update();

			serverGame->removeGameObject(networkObject);

			serverGame->update();
			clientGame1->update();
			clientGame2->update();
			
			CHECK_FALSE(clientManager1->hasNetworkGameObject(assignedIndex));
			CHECK_FALSE(clientManager2->hasNetworkGameObject(assignedIndex));
		}

		TEST(ServerGame, NetworkGameObjectRoleIsSetCorrectly)
		{
			auto networkObject = new MockNetworkGameObject();
			serverGame->addGameObject(networkObject);

			CHECK_TRUE(networkObject->getRole() == Role_Authority);
		}
	}
}