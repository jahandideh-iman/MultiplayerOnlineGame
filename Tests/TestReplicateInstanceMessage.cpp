#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockNetworkGameObject.h"

#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/ConstructorDatabase.h"



namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(ReplicateInstanceMessage, NetworkBase)
		{
			void teardown() override
			{
				NetworkBase::teardown();
				ConstructorDatabase::clear();
			}
		};

		TEST(ReplicateInstanceMessage, ReplicatesNetworkGameObject)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			int arbitraryID = 3;
			MockNetworkGameObject networkObject;
			networkObject.setInstanceId(arbitraryID);

			serverManager->sendMessage(ReplicateInstanceMessage(&networkObject,Role_None), clientAddress1);
			clientManager1->update();

			auto replicatedObject = dynamic_cast<const MockNetworkGameObject *> (clientManager1->findNetworkGameObject(networkObject.getInstanceId()));

			CHECK_EQUAL(networkObject.getInstanceId(), replicatedObject->getInstanceId());
		}

		TEST(ReplicateInstanceMessage, CorrectlySetRoleInReplicatedObject)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			int arbitraryID = 3;
			MockNetworkGameObject networkObject;
			networkObject.setInstanceId(arbitraryID);

			serverManager->sendMessage(ReplicateInstanceMessage(&networkObject, Role_Proxy), clientAddress1);
			serverManager->sendMessage(ReplicateInstanceMessage(&networkObject, Role_Simulated), clientAddress2);

			clientManager1->update();
			clientManager2->update();

			auto replicatedObject1 = dynamic_cast<const MockNetworkGameObject *> (clientManager1->findNetworkGameObject(networkObject.getInstanceId()));
			auto replicatedObject2 = dynamic_cast<const MockNetworkGameObject *> (clientManager2->findNetworkGameObject(networkObject.getInstanceId()));

			CHECK_EQUAL(Role_Proxy, replicatedObject1->getRole());
			CHECK_EQUAL(Role_Simulated, replicatedObject2->getRole());
		}
	}
}
