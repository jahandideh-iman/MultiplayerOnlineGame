#pragma once

#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Network/NetworkComponent.h"

namespace mog
{
	namespace network
	{
		class MockNetworkGameObjectWithState : public NetworkGameObject
		{
		public:
			MockNetworkGameObjectWithState()
			{
				networkComponent->addVariable("var1", &variable1);
				networkComponent->addVariable("var2", &variable2);
			}

			void setDirty(bool dirty) override { bMockDirty = dirty; }

			bool isDirty() const override { return bMockDirty; }

			AUTOID(MockNetworkGameObjectWithState, getNetworkID);

			Integer variable1;
			Integer variable2;

		private:
			bool bMockDirty = true;
		};

	}
}
