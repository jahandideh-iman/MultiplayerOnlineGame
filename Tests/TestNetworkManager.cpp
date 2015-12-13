#include "CppUTest/TestHarness.h"
#include "Network/NetworkManager.h"

#include "Network/ClientGame.h"
#include "Network/ServerGame.h"
#include "Network/MessageDatabase.h"

#include "MockSocketDataBase.h"
#include "MockSocket.h"
#include "MockMessage.h"

namespace mog
{
	namespace network
	{

		TEST_GROUP(NetworkManager)
		{

		};

		TEST(NetworkManager, ExecutesMessageOnRecieve)
		{

			MockSocketDataBase db;
			ServerGame serverGame;
			ClientGame clientGame;

			bool isMessageExecuted = false;

			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			auto serverManager = serverGame.getNetworkManager();
			auto clientManager = clientGame.getNetworkManager();;

			serverManager->setSocket(new MockSocket(&db));
			clientManager->setSocket(new MockSocket(&db));

			serverManager->setPort(8081);
			clientManager->setPort(8082);


			REGISTER_MESSAGE(MockMessage);
			serverManager->sendMessage(MockMessage(), network::InternetAddress(8082));
			clientManager->update(0.5);

			CHECK_TRUE(isMessageExecuted);

			MessageDatabase::clear();
		}
	}
}
