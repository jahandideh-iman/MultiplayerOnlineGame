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

		TEST(ReplicateStateMessage, ReplicatesNetworkComponentStates)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			MockNetworkGameObjectWithState gameObject;
			gameObject.setInstanceId(1);
			
			gameObject.variable1 = 1;
			gameObject.variable2 = 2;

			serverManager->sendMessage(ReplicateInstanceMessage(&gameObject,Role_None), clientAddress1);
			clientManager1->update();

			serverManager->sendMessage(ReplicateStateMessage(&gameObject), clientAddress1);
			clientManager1->update();

			auto replicatedObject = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager1->findNetworkGameObject(gameObject.getInstanceId()));

			CHECK_EQUAL(gameObject.variable1.getValue(), replicatedObject->variable1.getValue());
			CHECK_EQUAL(gameObject.variable2.getValue(), replicatedObject->variable2.getValue());
		}

		TEST(ReplicateStateMessage, ReplicatesNetworkComponentDirtyStatesWhenDirtyReplicationIsTrue)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(ReplicateStateMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithState);

			MockNetworkGameObjectWithState gameObject;
			gameObject.setInstanceId(1);

			gameObject.variable1 = 1;
			gameObject.variable2 = 2;

			serverManager->sendMessage(ReplicateInstanceMessage(&gameObject, Role_None), clientAddress1);
			clientManager1->update();

			//First replicate all variables
			serverManager->sendMessage(ReplicateStateMessage(&gameObject), clientAddress1);
			clientManager1->update();

			gameObject.variable1 = 3;
			gameObject.variable2 = 4;

			gameObject.variable1.setDirty(false);
			gameObject.variable2.setDirty(true);

			serverManager->sendMessage(ReplicateStateMessage(&gameObject, true), clientAddress1);
			clientManager1->update();

			auto replicatedObject = dynamic_cast<MockNetworkGameObjectWithState *> (clientManager1->findNetworkGameObject(gameObject.getInstanceId()));

			CHECK_EQUAL(1, replicatedObject->variable1.getValue());
			CHECK_EQUAL(4, replicatedObject->variable2.getValue());
		}
	}
}