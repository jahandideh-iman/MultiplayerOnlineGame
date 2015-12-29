#pragma once
#include "Engine/Network/Messages/Message.h"

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