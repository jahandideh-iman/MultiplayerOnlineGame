#pragma once

#include "Engine/Core/Types.h"
#include "Engine/Core/Macros.h"

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
