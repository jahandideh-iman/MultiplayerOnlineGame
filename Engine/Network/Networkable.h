#pragma once

#include "Engine/Core/Types.h"
#include "Engine/Core/Macros.h"

namespace mog
{
	namespace network
	{
		class Networkable
		{
		public:
			Networkable();
			virtual ~Networkable();

			virtual ID getNetworkID() const = 0;

			unsigned getInstanceId() const;
			void setInstanceId(unsigned i);

		private:
			unsigned instanceId;
		};
	}
}
