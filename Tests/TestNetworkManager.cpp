#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockMessage.h"
#include "Network/NetworkGameObject.h"
#include "Network/NetworkComponent.h"

namespace mog
{
	namespace network
	{

		class MockNetworkGameObject : public NetworkGameObject
		{
			AUTOID(MockNetworkGameObject, getNetworkID);
		};

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

		TEST(NetworkManager, DoesNotCallExecuteOnServerMethodInClient)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnServerCommand([&](){isMessageExecuted = true; });

			clientManager->sendMessage(MockMessage(), network::InternetAddress(clientPort));
			serverManager->update(0.5);

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(NetworkManager, DoesNotCallExecuteOnClientMethodInServer)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			clientManager->sendMessage(MockMessage(), network::InternetAddress(serverPort));
			serverManager->update(0.5);

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(NetworkManager, hasTheAddedNetworkGameObject)
		{
			auto gameObject1 = new MockNetworkGameObject();
			auto gameObject2 = new MockNetworkGameObject();

			clientGame->addGameObject(gameObject1);
			clientGame->addGameObject(gameObject2);

			CHECK_TRUE(clientManager->hasNetworkGameObject(gameObject1));
			CHECK_TRUE(clientManager->hasNetworkGameObject(gameObject2));
		}

		TEST(NetworkManager, hasTheAddedNetworkComponents)
		{
			auto gameObject = new MockNetworkGameObject();
			auto networkComponent1 = new NetworkComponent("networkComponent1", gameObject);
			auto networkComponent2 = new NetworkComponent("networkComponent2", gameObject);
		
			gameObject->addComponent(networkComponent1);
			gameObject->addComponent(networkComponent2);

			clientGame->addGameObject(gameObject);

			CHECK_TRUE(clientManager->hasNetworkComponent(networkComponent1));
			CHECK_TRUE(clientManager->hasNetworkComponent(networkComponent2));
		}
	}
}
