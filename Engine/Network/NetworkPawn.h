#pragma once

#include "Engine/Network/NetworkGameObject.h"

namespace mog
{
	namespace network
	{
		class NetworkPawn : public NetworkGameObject
		{
		public:
			NetworkPawn();
			~NetworkPawn();

			AUTOID(NetworkPawn, getNetworkID);
		};
	}
}
