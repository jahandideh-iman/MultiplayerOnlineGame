#include "CppUTest/TestHarness.h"
#include "Engine/Core/Buffer.h"
#include "NetworkBase.h"

#include "Engine/Network/ConstructorDatabase.h"

#include "Engine/Network/Messages/JoinMessage.h"
#include "Engine/Network/NetworkPawn.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"

namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(JoinMessage,NetworkBase)
		{
			bool hasPawn(NetworkManager *manager)
			{
				for (auto o : manager->getNetworkGameObjects())
				{
					if (dynamic_cast<const NetworkPawn*> (o) != nullptr)
						return true;
				}

				return false;
			}
		};

		TEST(JoinMessage, PlayerInfoIsAddedToServerGame)
		{
			REGISTER_MESSAGE(JoinMessage);

			clientManager1->sendMessage(JoinMessage("playerName"), InternetAddress(serverPort));
			serverManager->update();

			CHECK_TRUE(serverGame->getPlayerInfoByName("playerName") != nullptr);
		}

		TEST(JoinMessage, ClientAddressIsAddedToNetworkManager)
		{
			REGISTER_MESSAGE(JoinMessage);

			clientManager1->sendMessage(JoinMessage("playerName"), InternetAddress(serverPort));
			serverManager->update();

			CHECK_EQUAL(clientPort1,serverManager->getClients()[0]->getPort());
		}

		TEST(JoinMessage, PawnIsAddedToClientAndServer)
		{
			//NOTE: ReplicateInstanceMessage is needed to replicating pawn to client
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(JoinMessage);
			REGISTER_CONSTRUCTOR(NetworkPawn);

			clientManager1->sendMessage(JoinMessage("playerName"), InternetAddress(serverPort));
			serverManager->update();
			clientManager1->update();

			CHECK_TRUE(hasPawn(serverManager));
			CHECK_TRUE(hasPawn(clientManager1));

			ConstructorDatabase::clear();
		}
	}
	
}