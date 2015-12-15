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
			MockSocketDataBase db;

			ServerGame *serverGame;
			ClientGame *clientGame;

			NetworkManager *serverManager;
			NetworkManager *clientManager;

			unsigned clientPort = 8082;
			unsigned serverPort = 8081;

			void setup() override
			{
				
				serverGame = new ServerGame();
				clientGame = new ClientGame();

				serverManager = serverGame->getNetworkManager();
				clientManager = clientGame->getNetworkManager();

				serverManager->setSocket(new MockSocket(&db));
				clientManager->setSocket(new MockSocket(&db));

				serverManager->setPort(serverPort);
				clientManager->setPort(clientPort);



				
			}

			void teardown() override
			{
				delete serverGame;
				delete clientGame;

				MessageDatabase::clear();
			}
		};

		TEST(NetworkManager, CallsExecuteOnClientMethodInClient)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			serverManager->sendMessage(MockMessage(), network::InternetAddress(clientPort));
			clientManager->update(0.5);

			CHECK_TRUE(isMessageExecuted);
		}

		TEST(NetworkManager, CallsExecuteOnServerMethodInServer)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnServerCommand([&](){isMessageExecuted = true; });

			clientManager->sendMessage(MockMessage(), network::InternetAddress(serverPort));
			serverManager->update(0.5);

			CHECK_TRUE(isMessageExecuted);
		}

		TEST(NetworkManager, DoesNotCallsExecuteOnServerMethodInClient)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnServerCommand([&](){isMessageExecuted = true; });

			clientManager->sendMessage(MockMessage(), network::InternetAddress(clientPort));
			serverManager->update(0.5);

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(NetworkManager, DoesNotCallsExecuteOnClientMethodInServer)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			clientManager->sendMessage(MockMessage(), network::InternetAddress(serverPort));
			serverManager->update(0.5);

			CHECK_FALSE(isMessageExecuted);
		}
	}
}
