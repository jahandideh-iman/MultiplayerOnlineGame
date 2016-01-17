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

			serverManager->sendMessage(ReplicateInstanceMessage(&networkObject), network::InternetAddress(clientPort1));
			clientManager1->update();

			auto replicatedObject = dynamic_cast<const MockNetworkGameObject *> (clientManager1->findNetworkGameObjectByInstanceId(networkObject.getInstanceId()));

			CHECK_EQUAL(networkObject.getInstanceId(), replicatedObject->getInstanceId());
		}
	}
}
