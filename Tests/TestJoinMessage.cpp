#include "CppUTest/TestHarness.h"
#include "Engine/Buffer.h"
#include "NetworkBase.h"
#include "Network/Messages/JoinMessage.h"

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

			clientManager->sendMessage(JoinMessage("playerName"), network::InternetAddress(serverPort));
			serverManager->update();

			CHECK_TRUE(serverGame->getPlayerInfoByName("playerName") != nullptr);
		}

		TEST(JoinMessage, ClientAddressIsAddedToNetworkManager)
		{
			//NOTE: This test is not complete because MockSocket has no mechanism for determining sender's address
			REGISTER_MESSAGE(JoinMessage);

			clientManager->sendMessage(JoinMessage("playerName"), network::InternetAddress(serverPort));
			serverManager->update();

			CHECK_TRUE(serverManager->getClients().size() == 1);
		}
	}
	
}