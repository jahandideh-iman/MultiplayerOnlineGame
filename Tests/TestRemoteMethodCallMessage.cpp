#include "CppUTest/TestHarness.h"

#include "Engine/Network/Messages/RemoteMethodCallMessage.h"
#include "Engine/Network/ConstructorDatabase.h"

#include "NetworkBase.h"
#include "MockNetworkGameObjectWithMethod.h"



namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(RemoteMethodCallMessage, NetworkBase)
		{
			void teardown() override
			{
				NetworkBase::teardown();
				ConstructorDatabase::clear();
			}
		};

		TEST(RemoteMethodCallMessage, CallsMethodOnServer)
		{
			REGISTER_MESSAGE(RemoteMethodCallMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithMethod);

			auto networkObject = new MockNetworkGameObjectWithMethod();

			serverGame->addGameObject(networkObject);

			clientManager->sendMessage(RemoteMethodCallMessage(networkObject, "method"), network::InternetAddress(serverPort));
			serverManager->update();

			CHECK_TRUE(networkObject->isMethodCalled);
		}

		TEST(RemoteMethodCallMessage, DoesNotCallMethodOnClient)
		{
			REGISTER_MESSAGE(RemoteMethodCallMessage);
			REGISTER_CONSTRUCTOR(MockNetworkGameObjectWithMethod);

			auto networkObject = new MockNetworkGameObjectWithMethod();

			clientGame->addGameObject(networkObject);

			serverManager->sendMessage(RemoteMethodCallMessage(networkObject, "method"), network::InternetAddress(clientPort));
			clientManager->update();

			CHECK_FALSE(networkObject->isMethodCalled);
		}
	}
}