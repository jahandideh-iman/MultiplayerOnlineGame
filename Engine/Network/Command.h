#pragma once
#include "Network/Messages/Message.h"

namespace mog
{
	namespace network
	{
		class Command :
			public Message
		{
		public:
			Command();
			~Command();
		};
	}
}