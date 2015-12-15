#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockMessage.h"

namespace mog
{
	namespace network
	{

		TEST_GROUP_BASE(NetworkManager, NetworkBase)
		{

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
