#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockMessage.h"
#include "MockNetworkGameObject.h"

#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Network/InternetAddress.h"
#include "Engine/Network/ConstructorDatabase.h"

#include "Engine/Network/Messages/ReplicateInstanceMessage.h"


namespace mog
{
	namespace network
	{

		TEST_GROUP_BASE(NetworkManager, NetworkBase)
		{
		public:
			void setup() override
			{
				NetworkBase::setup();

			}

			void teardown() override
			{
				NetworkBase::teardown();
				MessageDatabase::clear();
				ConstructorDatabase::clear();
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

		TEST(NetworkManager, NetworkInstanceIdIsCorrect)
		{
			auto gameObject = new MockNetworkGameObject();

			clientGame->addGameObject(gameObject);

			CHECK_EQUAL(gameObject, clientManager->findNetworkGameObjectByInstanceId(gameObject->getInstanceId()));
		}

		TEST(NetworkManager, InstantiateNetworkGameObjectToClientWhenAddedToGame)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGameObjectSize = clientGame->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			//NOTE: Client must be added first
			serverManager->addClient(&InternetAddress(clientPort));

			serverGame->addGameObject(gameObject);

			serverManager->update();
			clientManager->update();

			CHECK_TRUE(clientManager->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_EQUAL(clientGameObjectSize + 1, clientGame->getGameObjects().size());
		}

		TEST(NetworkManager, DoesNotInstantiateAlreadyInstantiatedNetworkGameObject)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGameObjectSize = clientGame->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			serverManager->addClient(&InternetAddress(clientPort));
			serverGame->addGameObject(gameObject);

			serverManager->update();
			clientManager->update();

			auto clinetInstantiatedObject = clientManager->findNetworkGameObjectByInstanceId(gameObject->getInstanceId());

			serverManager->update();
			clientManager->update();

			CHECK_EQUAL(clinetInstantiatedObject, clientManager->findNetworkGameObjectByInstanceId(gameObject->getInstanceId()));
			CHECK_TRUE(clientManager->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_EQUAL(clientGameObjectSize + 1, clientGame->getGameObjects().size());
		}
	}
}
