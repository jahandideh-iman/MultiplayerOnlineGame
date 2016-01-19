#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockNetworkGameObject.h"

#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/Messages/RemoveInstanceMessage.h"

#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/ConstructorDatabase.h"


namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(RemoveInstanceMessage, NetworkBase)
		{
			void teardown() override
			{
				NetworkBase::teardown();
				ConstructorDatabase::clear();
			}
		};

		TEST(RemoveInstanceMessage, RemovesNetworkGameObjectFromClient)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(RemoveInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			int arbitraryID = 3;
			MockNetworkGameObject networkObject;
			networkObject.setInstanceId(arbitraryID);

			serverManager->sendMessage(ReplicateInstanceMessage(&networkObject), clientAddress1);
			clientManager1->update();

			serverManager->sendMessage(RemoveInstanceMessage(networkObject.getInstanceId()), clientAddress1);
			clientManager1->update();

			CHECK_FALSE(clientManager1->hasNetworkGameObject(arbitraryID));
		}

		TEST(RemoveInstanceMessage, DoesNotRemoveNetworkGameObjectFromServer)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_MESSAGE(RemoveInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			auto networkObject = new MockNetworkGameObject();

			serverGame->addGameObject(networkObject);

			clientManager1->sendMessage(RemoveInstanceMessage(networkObject->getInstanceId()), serverAddress);
			serverManager->update();

			CHECK_TRUE(serverManager->hasNetworkGameObject(networkObject));
		}
	}
}
