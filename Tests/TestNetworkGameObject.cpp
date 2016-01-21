#include "CppUTest/TestHarness.h"
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Core/Game.h"

#include "MockNetworkGameObject.h"
#include "MockNetworkGameObjectWithMethod.h"
#include "MockNetworkGameObjectWithState.h"
#include "NetworkBase.h"

namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(NetworkGameObject,NetworkBase)
		{

		};

		TEST(NetworkGameObject, AddsItselfToNetworkManagerWhenAddedToGame)
		{
			auto networkObject1 = new MockNetworkGameObject();
			auto networkObject2 = new MockNetworkGameObject();
			initialClientNetworkGameObject(networkObject2);
			
			serverGame->addGameObject(networkObject1);
			clientGame1->addGameObject(networkObject2);


			CHECK_TRUE(serverManager->hasNetworkGameObject(networkObject1));
			CHECK_TRUE(clientManager1->hasNetworkGameObject(networkObject2));
		}

		TEST(NetworkGameObject, RemovesItselfFromNetworkManagerWhenRemovedFromGame)
		{
			auto networkObject1 = new MockNetworkGameObject();
			auto networkObject2 = new MockNetworkGameObject();
			initialClientNetworkGameObject(networkObject2);

			serverGame->addGameObject(networkObject1);
			clientGame1->addGameObject(networkObject2);

			serverGame->removeGameObject(networkObject1);
			clientGame1->removeGameObject(networkObject2);


			CHECK_FALSE(serverManager->hasNetworkGameObject(networkObject1));
			CHECK_FALSE(clientManager1->hasNetworkGameObject(networkObject2));
		}

		TEST(NetworkGameObject, WrittenStateIsCorrectForEmptyNetworkGameObject)
		{
			MockNetworkGameObject networkObject;
			Buffer buffer;

			networkObject.writeState(&buffer);

			char *data = buffer.getData();

			STRCMP_EQUAL("{}", data);

			delete[]data;
		}

		TEST(NetworkGameObject, WrittenStateIsCorrectForNonEmptyNetowrkGameObject)
		{
			MockNetworkGameObject networkObject;
			Integer var1 = 1;
			Integer var2 = 2;
			networkObject.getNetworkComponent()->addVariable("var1", &var1);
			networkObject.getNetworkComponent()->addVariable("var2", &var2);

			Buffer buffer;

			networkObject.writeState(&buffer);
			ParameterContainer params(&buffer);

			CHECK_EQUAL("1", params.get("var1"));
			CHECK_EQUAL("2", params.get("var2"));
		}

		TEST(NetworkGameObject, WrittenStateForDirtyIsCorrectForNonEmptyNetowrkGameObject)
		{
			MockNetworkGameObject networkObject;
			Integer var1 = 1;
			Integer var2 = 2;
			networkObject.getNetworkComponent()->addVariable("var1", &var1);
			networkObject.getNetworkComponent()->addVariable("var2", &var2);

			var1.setDirty(false);
			var2.setDirty(true);

			Buffer buffer;

			networkObject.writeState(&buffer,true);
			ParameterContainer params(&buffer);

			CHECK_FALSE(params.has("var1"));
			CHECK_TRUE(params.has("var2"));
		}

		TEST(NetworkGameObject, ReadStateIsCorrect)
		{
			MockNetworkGameObject networkObject;
			Integer var1 = 0;
			Integer var2 = 0;
			networkObject.getNetworkComponent()->addVariable("var1", &var1);
			networkObject.getNetworkComponent()->addVariable("var2", &var2);

			ParameterContainer params;
			params.put("var1", "1");
			params.put("var2", "2");

			Buffer buffer;

			params.write(&buffer);

			networkObject.readState(&buffer);

			CHECK_EQUAL(1, var1.getValue());
			CHECK_EQUAL(2, var2.getValue());
		}

		TEST(NetworkGameObject, CallsRegisteredMethodsByName)
		{
			MockNetworkGameObjectWithMethod networkObject;

			networkObject.initialRegisteredMethods();

			networkObject.callMethod("method");

			CHECK_TRUE(networkObject.isMethodCalled)
		}

		TEST(NetworkGameObject, InitialRegisteredMethodsIsCalledWhenAddedToGame)
		{
			auto networkObject = new MockNetworkGameObjectWithMethod();
			Game game;

			game.addGameObject(networkObject);

			CHECK_TRUE(networkObject->isInitialRegisteredMethodsCalled);
		}
	}
}