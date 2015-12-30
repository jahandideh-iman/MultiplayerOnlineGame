#pragma once

#include "Engine/Network/NetworkGameObject.h"

namespace mog
{
	namespace network
	{
		class NetworkComponent;
		class MockNetworkGameObject : public NetworkGameObject
		{
		public:
			MockNetworkGameObject();

			AUTOID(MockNetworkGameObject, getNetworkID);

			Integer getVariable() const;

			Integer variable;

		private:

		};

	}
}

