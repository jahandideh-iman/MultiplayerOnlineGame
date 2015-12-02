#pragma once
#include "Message.h"

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