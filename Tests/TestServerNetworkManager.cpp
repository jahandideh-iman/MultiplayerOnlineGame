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

		TEST_GROUP_BASE(ServerNetworkManager, NetworkBase)
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

		TEST(ServerNetworkManager, CallsExecuteOnServerMethodInServer)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnServerCommand([&](){isMessageExecuted = true; });

			clientManager1->sendMessage(MockMessage(), network::InternetAddress(serverAddress));
			serverManager->update();

			CHECK_TRUE(isMessageExecuted);
		}

		TEST(ServerNetworkManager, DoesNotCallExecuteOnClientMethodInServer)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			clientManager1->sendMessage(MockMessage(), network::InternetAddress(serverAddress));
			serverManager->update();

			CHECK_FALSE(isMessageExecuted);
		}


		TEST(ServerNetworkManager, hasTheAddedNetworkGameObject)
		{
			auto gameObject1 = new MockNetworkGameObject();
			auto gameObject2 = new MockNetworkGameObject();


			serverGame->addGameObject(gameObject1);
			serverGame->addGameObject(gameObject2);

			CHECK_TRUE(serverManager->hasNetworkGameObject(gameObject1));
			CHECK_TRUE(serverManager->hasNetworkGameObject(gameObject2));
		}

		TEST(ServerNetworkManager, NetworkInstanceIdIsCorrect)
		{
			auto gameObject = new MockNetworkGameObject();
			//initialClientNetworkGameObject(gameObject);

			serverGame->addGameObject(gameObject);

			CHECK_EQUAL(gameObject, serverManager->findNetworkGameObject(gameObject->getInstanceId()));
		}

		TEST(ServerNetworkManager, CanProcessMultipleMessagesInOneUpdate)
		{
			REGISTER_MESSAGE(MockMessage);

			unsigned numberOfExecutions = 0;
			MockMessage::setExecuteOnServerCommand([&](){numberOfExecutions++; });

			clientManager1->sendMessage(MockMessage(), serverAddress);
			clientManager1->sendMessage(MockMessage(), serverAddress);

			serverManager->update();

			CHECK_EQUAL(2, numberOfExecutions);
		}

		TEST(ServerNetworkManager, InstantiateNetworkGameObjectToClientWhenAddedToGame)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			//NOTE: Clients are added first
			serverManager->addClient(client1);
			serverManager->addClient(client2);

			serverGame->addGameObject(gameObject);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_TRUE(clientManager2->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_EQUAL(clientGame1ObjectSize + 1, clientGame1->getGameObjects().size());
			CHECK_EQUAL(clientGame2ObjectSize + 1, clientGame2->getGameObjects().size());
		}

		TEST(ServerNetworkManager, InstantiateNetworkGameObjectToClientWhenJoinedToGame)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			//NOTE: Network game object is added first
			serverGame->addGameObject(gameObject);

			serverManager->addClient(client1);
			serverManager->addClient(client2);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			CHECK_TRUE(clientManager1->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_TRUE(clientManager2->hasNetworkGameObject(gameObject->getInstanceId()));
			CHECK_EQUAL(clientGame1ObjectSize + 1, clientGame1->getGameObjects().size());
			CHECK_EQUAL(clientGame2ObjectSize + 1, clientGame2->getGameObjects().size());
		}

		TEST(ServerNetworkManager, DoesNotInstantiateAlreadyInstantiatedNetworkGameObjectToClients)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();
			auto gameObject = new MockNetworkGameObject();

			serverManager->addClient(client1);
			serverManager->addClient(client2);
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

		TEST(ServerNetworkManager, IntegrationTestForInstanceReplication)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto clientGame1ObjectSize = clientGame1->getGameObjects().size();
			auto clientGame2ObjectSize = clientGame2->getGameObjects().size();

			auto gameObject1 = new MockNetworkGameObject();
			auto gameObject2 = new MockNetworkGameObject();

			serverManager->addClient(client1);
			serverGame->addGameObject(gameObject1);

			serverManager->addClient(client2);
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


		TEST(ServerNetworkManager, ReplicatesStateOfNetworkGameObjectToClientWhenAddedToGame)
		{
			//NOTE: ReplicateInstaceMessage is needed because first instances must be replicated
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			auto gameObject = new MockNetworkGameObjectWithState();
			gameObject->variable1 = 5;

			serverManager->addClient(client1);
			serverGame->addGameObject(gameObject);
			serverManager->addClient(client2);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			auto client1Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
			auto client2Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager2->findNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(gameObject->variable1.getValue(), client1Object->variable1.getValue());
			CHECK_EQUAL(gameObject->variable1.getValue(), client2Object->variable1.getValue());
		}

		TEST(ServerNetworkManager, RemovesRemovedClinetObjectsFromServer)
		{
			//NOTE: ReplicateInstaceMessage is needed because first instances must be replicated
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			auto gameObject = new MockNetworkGameObjectWithState();
			gameObject->variable1 = 5;

			serverManager->addClient(client1);
			serverGame->addGameObject(gameObject);
			serverManager->addClient(client2);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			auto client1Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
			auto client2Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager2->findNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(gameObject->variable1.getValue(), client1Object->variable1.getValue());
			CHECK_EQUAL(gameObject->variable1.getValue(), client2Object->variable1.getValue());
		}

		TEST(ServerNetworkManager, CorrectllySetObjectRolesInClient)
		{
			//NOTE: ReplicateInstaceMessage is needed because first instances must be replicated
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto gameObject = new MockNetworkGameObject();

			gameObject->setClient(client1);

			serverGame->addGameObject(gameObject);

			serverManager->addClient(client1);
			serverManager->addClient(client2);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			auto client1Object = dynamic_cast<MockNetworkGameObject *> (clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
			auto client2Object = dynamic_cast<MockNetworkGameObject *> (clientManager2->findNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(Role_Proxy, client1Object->getRole());
			CHECK_EQUAL(Role_Simulated, client2Object->getRole());
		}

		TEST(ServerNetworkManager, DoesNotReplicateStateWhenObjectIsNotDirty)
		{
			//NOTE: ReplicateInstaceMessage is needed because first instances must be replicated
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			auto gameObject = new MockNetworkGameObjectWithState();
			gameObject->variable1 = 1;

			serverManager->addClient(client1);
			serverGame->addGameObject(gameObject);
			serverManager->addClient(client2);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			gameObject->variable1 = 2;
			gameObject->setDirty(false);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			auto client1Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
			auto client2Object = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager2->findNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(1, client1Object->variable1.getValue());
			CHECK_EQUAL(1, client2Object->variable1.getValue());
		}

		TEST(ServerNetworkManager, ResetsNetworkObjectDirtyFlagAfterReplication)
		{
			//NOTE: ReplicateInstaceMessage is needed because first instances must be replicated
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			auto gameObject = new MockNetworkGameObjectWithState();
			gameObject->variable1 = 1;
			
			gameObject->setDirty(true);

			serverManager->addClient(client1);
			serverGame->addGameObject(gameObject);
			serverManager->addClient(client2);

			serverManager->update();
			clientManager1->update();
			clientManager2->update();

			CHECK_FALSE(gameObject->isDirty());
		}
	}
}
