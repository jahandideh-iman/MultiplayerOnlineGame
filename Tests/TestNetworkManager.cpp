#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockMessage.h"
#include "MockNetworkGameObject.h"
#include "MockNetworkGameObjectWithState.h"
#include "MockNetworkGameObjectWithMethod.h"

#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Network/InternetAddress.h"
#include "Engine/Network/ConstructorDatabase.h"

#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/Messages/ReplicateStateMessage.h"
#include "Engine/Network/Messages/RemoteMethodCallMessage.h"


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

			serverManager->sendMessage(MockMessage(), network::InternetAddress(clientPort1));
			clientManager1->update();

			CHECK_TRUE(isMessageExecuted);
		}

		TEST(NetworkManager, CallsExecuteOnServerMethodInServer)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnServerCommand([&](){isMessageExecuted = true; });

			clientManager1->sendMessage(MockMessage(), network::InternetAddress(serverPort));
			serverManager->update();

			CHECK_TRUE(isMessageExecuted);
		}

		TEST(NetworkManager, DoesNotCallExecuteOnServerMethodInClient)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnServerCommand([&](){isMessageExecuted = true; });

			clientManager1->sendMessage(MockMessage(), network::InternetAddress(clientPort1));
			serverManager->update();

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(NetworkManager, DoesNotCallExecuteOnClientMethodInServer)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			clientManager1->sendMessage(MockMessage(), network::InternetAddress(serverPort));
			serverManager->update();

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(NetworkManager, DoesNotCallUnRegisteredMessage)
		{
			//REGISTER_MESSAGE(MockMessage);
			bool isMessageExecuted = false;

			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			serverManager->sendMessage(MockMessage(), InternetAddress(clientPort1));

			clientManager1->update();

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(NetworkManager, hasTheAddedNetworkGameObject)
		{
			auto gameObject1 = new MockNetworkGameObject();
			auto gameObject2 = new MockNetworkGameObject();

			initialClientNetworkGameObject(gameObject1);
			initialClientNetworkGameObject(gameObject2);

			clientGame1->addGameObject(gameObject1);
			clientGame1->addGameObject(gameObject2);

			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject1));
			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject2));
		}

		TEST(NetworkManager, NetworkInstanceIdIsCorrect)
		{
			auto gameObject = new MockNetworkGameObject();
			initialClientNetworkGameObject(gameObject);

			clientGame1->addGameObject(gameObject);

			CHECK_EQUAL(gameObject, clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
		}

		TEST(NetworkManager, InstantiateNetworkGameObjectToClientWhenAddedToGame)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			//NOTE: Clients are added first
			serverManager->addClient(&InternetAddress(clientPort1));
			serverManager->addClient(&InternetAddress(clientPort2));

			serverGame->addGameObject(gameObject);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_TRUE(clientManager2->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_EQUAL(clientGame1ObjectSize + 1, clientGame1->getGameObjects().size());
			CHECK_EQUAL(clientGame2ObjectSize + 1, clientGame2->getGameObjects().size());
		}

		TEST(NetworkManager, InstantiateNetworkGameObjectToClientWhenJoinedToGame)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			//NOTE: Network game object is added first
			serverGame->addGameObject(gameObject);

			serverManager->addClient(&InternetAddress(clientPort1));
			serverManager->addClient(&InternetAddress(clientPort2));

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_TRUE(clientManager2->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_EQUAL(clientGame1ObjectSize + 1, clientGame1->getGameObjects().size());
			CHECK_EQUAL(clientGame2ObjectSize + 1, clientGame2->getGameObjects().size());
		}

		TEST(NetworkManager, DoesNotInstantiateAlreadyInstantiatedNetworkGameObject)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			serverManager->addClient(&InternetAddress(clientPort1));
			serverManager->addClient(&InternetAddress(clientPort2));
			serverGame->addGameObject(gameObject);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			auto client1InstantiatedObject = clientManager1->findNetworkGameObject(gameObject->getInstanceId());
			auto client2InstantiatedObject = clientManager2->findNetworkGameObject(gameObject->getInstanceId());

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_TRUE(clientManager2->hasNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(client1InstantiatedObject, clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
			CHECK_EQUAL(client2InstantiatedObject, clientManager2->findNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(clientGame1ObjectSize + 1, clientGame1->getGameObjects().size());
			CHECK_EQUAL(clientGame2ObjectSize + 1, clientGame2->getGameObjects().size());
		}

		TEST(NetworkManager, IntegrationTestForInstaceReplication)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();

			auto gameObject1 = new MockNetworkGameObject();
			auto gameObject2 = new MockNetworkGameObject();

			serverManager->addClient(&InternetAddress(clientPort1));
			serverGame->addGameObject(gameObject1);

			serverManager->addClient(&InternetAddress(clientPort2));
			serverGame->addGameObject(gameObject2);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject1->getInstanceId()));
			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject2->getInstanceId()));

			CHECK_TRUE(clientManager2->hasNetworkGameObject(gameObject1->getInstanceId()));
			CHECK_TRUE(clientManager2->hasNetworkGameObject(gameObject2->getInstanceId()));

			CHECK_EQUAL(clientGame1ObjectSize + 2, clientGame1->getGameObjects().size());
			CHECK_EQUAL(clientGame2ObjectSize + 2, clientGame2->getGameObjects().size());
		}


		TEST(NetworkManager, CanProcessMultipleMessagesInOneUpdate)
		{
			REGISTER_MESSAGE(MockMessage);

			unsigned numberOfExecutions = 0;
			MockMessage::setExecuteOnClientCommand([&](){numberOfExecutions++; });

			serverManager->sendMessage(MockMessage(), InternetAddress(clientPort1));
			serverManager->sendMessage(MockMessage(), InternetAddress(clientPort1));

			clientManager1->update();

			CHECK_EQUAL(2, numberOfExecutions);
		}

		TEST(NetworkManager, ReplicatesStateOfNetworkGameObjectToClientWhenAddedToGame)
		{
			//NOTE: ReplicateInstaceMessage is needed because first instaces must be replicated
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			auto gameObject = new MockNetworkGameObjectWithState();
			gameObject->variable1 = 5;

			serverManager->addClient(&InternetAddress(clientPort1));
			serverGame->addGameObject(gameObject);
			serverManager->addClient(&InternetAddress(clientPort2));

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			auto client1Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
			auto client2Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager2->findNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(gameObject->variable1.getValue(), client1Object->variable1.getValue());
			CHECK_EQUAL(gameObject->variable1.getValue(), client2Object->variable1.getValue());
		}
	}
}
