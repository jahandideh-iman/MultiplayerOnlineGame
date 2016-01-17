#pragma once

#include "Engine/Network/NetworkGameObject.h"

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
				isInitialRegisteredMethodsCalled = true;
				registerMethod("method", std::bind(&mog::network::MockNetworkGameObjectWithMethod::method, this));
			}

			AUTOID(MockNetworkGameObjectWithMethod, getNetworkID);

			void method()
			{
				isMethodCalled = true;
			}

			bool isInitialRegisteredMethodsCalled = false;
			bool isMethodCalled = false;
		};
	}
}