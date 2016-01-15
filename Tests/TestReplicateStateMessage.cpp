#include "CppUTest/TestHarness.h"
#include "NetworkBase.h"
#include "MockNetworkGameObject.h"

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
		class MockNonEmptyNetworkGameObject : public NetworkGameObject
		{
		public:
			MockNonEmptyNetworkGameObject()
			{
				networkComponent->addVariable("var", &variable);
			}

			AUTOID(MockNonEmptyNetworkGameObject, getNetworkID);

			Integer variable;
		};

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
			REGISTER_CONSTRUCTOR(MockNonEmptyNetworkGameObject);

			auto gameObject = new MockNonEmptyNetworkGameObject();

			gameObject->variable = 5;

			serverGame->addGameObject(gameObject);


			serverManager->sendMessage(ReplicateInstanceMessage(gameObject), network::InternetAddress(clientPort));
			clientManager->update();

			serverManager->sendMessage(ReplicateStateMessage(gameObject), network::InternetAddress(clientPort));
			clientManager->update();

			auto replicatedObject = dynamic_cast<MockNonEmptyNetworkGameObject *> (clientManager->findNetworkGameObjectByInstanceId(gameObject->getInstanceId()));

			CHECK_EQUAL(gameObject->variable.getValue(), replicatedObject->variable.getValue());
		}
	}
}