#pragma once

#include "Engine/Types.h"
#include "Engine/Macros.h"




namespace mog
{
	namespace network
	{
		class NetworkObject
		{
		public:
			NetworkObject();
			virtual ~NetworkObject();

			virtual ID getNetworkID() const = 0;
		};
	}
}
