#include "CppUTest/TestHarness.h"
#include "Engine/Core/Buffer.h"
#include "NetworkBase.h"
#include "Engine/Network/Messages/JoinMessage.h"

namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(JoinMessage,NetworkBase)
		{
		};

		TEST(JoinMessage, PlayerInfoIsAddedToServerGame)
		{
			REGISTER_MESSAGE(JoinMessage);

			clientManager->sendMessage(JoinMessage("playerName"), InternetAddress(serverPort));
			serverManager->update();

			CHECK_TRUE(serverGame->getPlayerInfoByName("playerName") != nullptr);
		}

		TEST(JoinMessage, ClientAddressIsAddedToNetworkManager)
		{
			REGISTER_MESSAGE(JoinMessage);

			clientManager->sendMessage(JoinMessage("playerName"), InternetAddress(serverPort));
			serverManager->update();

			CHECK_EQUAL(clientPort,serverManager->getClients()[0]->getPort());
		}
	}
	
}