#include "CppUTest/TestHarness.h"

#include "NetworkBase.h"
#include "MockNetworkGameObjectWithMethod.h"

#include "Engine/Network/ClientGame.h"
#include "Engine/Network/Messages/RemoteMethodCallMessage.h"

namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(ClientGame, NetworkBase)
		{
		public:

			void teardown() override
			{
				NetworkBase::teardown();
				MessageDatabase::clear();
			}
		};

		TEST(ClientGame, CallsRemoteMethod)
		{
			REGISTER_MESSAGE(RemoteMethodCallMessage);
	
			auto gameObject = new MockNetworkGameObjectWithMethod();

			serverGame->addGameObject(gameObject);
			clientGame1->callRemoteMethod("method", gameObject);

			serverGame->update();

			CHECK_TRUE(gameObject->isMethodCalled);
		}
	}
}