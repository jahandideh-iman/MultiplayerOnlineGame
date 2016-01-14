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
			//REGISTER_MESSAGE(ReplicateInstanceMessage);
			//REGISTER_MESSAGE(ReplicateStateMessage);
			//REGISTER_CONSTRUCTOR(MockNetworkGameObject);

			//auto gameObject = new MockNetworkGameObject();

			//gameObject->variable = 5;

			//serverGame->addGameObject(gameObject);


			//serverManager->sendMessage(ReplicateInstanceMessage(gameObject), network::InternetAddress(clientPort));
			//clientManager->update();

			//serverManager->sendMessage(ReplicateStateMessage(gameObject), network::InternetAddress(clientPort));
			//clientManager->update();

			//auto replicatedObject = dynamic_cast<const MockNetworkGameObject *> (clientManager->getGameObjects()[0]);

			//CHECK_EQUAL(gameObject->getVariable().getValue(), replicatedObject->getVariable().getValue());

		}
	}
}