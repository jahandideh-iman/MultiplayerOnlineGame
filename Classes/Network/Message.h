#pragma once

#include "InternetAddress.h"

#include "Engine/Types.h"
#include "Engine/Macros.h"

#include "Network/Buffer.h"

namespace mog
{
	namespace network
	{
		class Message
		{

		public:
			Message();
			virtual ~Message();

			virtual void execute(const Buffer &buffer, const network::InternetAddress &address) const = 0;
			virtual Buffer *serialize() const = 0;
			virtual ID getID() const = 0;

		protected:
			static unsigned int code;
		};

	}
}