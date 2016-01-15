#include "CppUTest/TestHarness.h"
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"
#include "MockNetworkGameObject.h"

namespace mog
{
	namespace network
	{

		class MockNetworkGameObjectWithMethod : public NetworkGameObject
		{
		public:
			MockNetworkGameObjectWithMethod()
			{
			}

			void initialRegisteredMethods() override
			{
				registerMethod("method", std::bind(&mog::network::MockNetworkGameObjectWithMethod::method, this));
			}

			AUTOID(MockNetworkGameObjectWithMethod, getNetworkID);

			void method()
			{
				isMethodCalled = true;
			}

			bool isMethodCalled = false;
		};

		TEST_GROUP(NetworkGameObject)
		{

		};

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

		TEST(NetworkGameObject, callsRegisteredMethodsByName)
		{
			MockNetworkGameObjectWithMethod networkObject;

			networkObject.initialRegisteredMethods();

			networkObject.callMethod("method");

			CHECK_TRUE(networkObject.isMethodCalled)
		}
	}
}