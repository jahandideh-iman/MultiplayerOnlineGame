#pragma once

#include "Engine/Network/NetworkGameObject.h"
#include <string>

namespace mog
{
	namespace network
	{
		class MockNetworkGameObject : public NetworkGameObject
		{
		public:
			MockNetworkGameObject();

			AUTOID(MockNetworkGameObject, getNetworkID);

		};

	}
}

