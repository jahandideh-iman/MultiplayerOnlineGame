#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockNetworkGameObject.h"
#include "MockNetworkGameObjectWithState.h"

#include "Engine/Network/Messages/ReplicateStateMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Network/ConstructorDatabase.h"
#include "Engine/Core/Types.h"
#include "Engine/Network/InternetAddress.h"


namespace mog
{
	namespace network
	{

		TEST_GROUP_BASE(ReplicateStateMessage, NetworkBase)
		{
			void teardown() override
			{
				NetworkBase::teardown();
				ConstructorDatabase::clear();
			}
		};

		TEST(ReplicateStateMessage, ReplicatesNetworkComponentStatesInServerUpdate)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			auto gameObject = new MockNetworkGameObjectWithState();

			gameObject->variable1 = 1;
			gameObject->variable2 = 2;

			serverGame->addGameObject(gameObject);

			serverManager->sendMessage(ReplicateInstanceMessage(gameObject), network::InternetAddress(clientPort1));
			clientManager1->update();

			serverManager->sendMessage(ReplicateStateMessage(gameObject), network::InternetAddress(clientPort1));
			clientManager1->update();

			auto replicatedObject = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager1->findNetworkGameObject(gameObject->getInstanceId()));

			CHECK_EQUAL(gameObject->variable1.getValue(), replicatedObject->variable1.getValue());
			CHECK_EQUAL(gameObject->variable2.getValue(), replicatedObject->variable2.getValue());
		}
	}
}