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

		TEST_GROUP_BASE(ClientNetworkManager, NetworkBase)
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

		TEST(ClientNetworkManager, CallsExecuteOnClientMethodInClient)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			serverManager->sendMessage(MockMessage(), clientAddress1);
			clientManager1->update();

			CHECK_TRUE(isMessageExecuted);
		}

		TEST(ClientNetworkManager, DoesNotCallExecuteOnServerMethodInClient)
		{
			bool isMessageExecuted = false;

			REGISTER_MESSAGE(MockMessage);
			MockMessage::setExecuteOnServerCommand([&](){isMessageExecuted = true; });

			clientManager1->sendMessage(MockMessage(), network::InternetAddress(clientAddress1));
			serverManager->update();

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(ClientNetworkManager, DoesNotCallNotRegisteredMessage)
		{
			//REGISTER_MESSAGE(MockMessage);
			bool isMessageExecuted = false;

			MockMessage::setExecuteOnClientCommand([&](){isMessageExecuted = true; });

			serverManager->sendMessage(MockMessage(), clientAddress1);

			clientManager1->update();

			CHECK_FALSE(isMessageExecuted);
		}

		TEST(ClientNetworkManager, hasTheAddedNetworkGameObject)
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

		TEST(ClientNetworkManager, NetworkInstanceIdIsCorrect)
		{
			auto gameObject = new MockNetworkGameObject();
			initialClientNetworkGameObject(gameObject);

			clientGame1->addGameObject(gameObject);

			CHECK_EQUAL(gameObject, clientManager1->findNetworkGameObject(gameObject->getInstanceId()));
		}

		TEST(ClientNetworkManager, CanProcessMultipleMessagesInOneUpdate)
		{
			REGISTER_MESSAGE(MockMessage);

			unsigned numberOfExecutions = 0;
			MockMessage::setExecuteOnClientCommand([&](){numberOfExecutions++; });

			serverManager->sendMessage(MockMessage(), clientAddress1);
			serverManager->sendMessage(MockMessage(), clientAddress1);

			clientManager1->update();

			CHECK_EQUAL(2, numberOfExecutions);
		}
	}
}
