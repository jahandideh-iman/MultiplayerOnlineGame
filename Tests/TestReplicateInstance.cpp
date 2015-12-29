#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/ConstructorDatabase.h"


namespace mog
{
	namespace network
	{

		class MockNetworkGameObject : public NetworkGameObject
		{
			AUTOID(MockNetworkGameObject, getNetworkID);
		};

		TEST_GROUP_BASE(ReplicateInstanceMessage, NetworkBase)
		{

		};

		TEST(ReplicateInstanceMessage, ReplicatesNetworkGameObject)
		{
			REGISTER_MESSAGE(ReplicateInstanceMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			int arbitraryID = 3;
			MockNetworkGameObject networkObject;
			networkObject.setInstanceId(arbitraryID);

			serverManager->sendMessage(ReplicateInstanceMessage(&networkObject), network::InternetAddress(clientPort));
			clientManager->update();

			auto replicatedObject = dynamic_cast<const MockNetworkGameObject *> (clientGame->getGameObjects()[0]);

			CHECK_EQUAL(networkObject.getInstanceId(), replicatedObject->getInstanceId());

			ConstructorDatabase::clear();
		}
	}
}
