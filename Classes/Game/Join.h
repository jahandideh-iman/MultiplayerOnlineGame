#pragma once
#include "Network/Command.h"
namespace mog
{
	namespace network
	{
		class Join :
			public Command
		{
		public:
			Join();
			~Join();

			virtual void execute(const Buffer &buffer, const InternetAddress& address) const override;

			virtual Buffer *serialize() const override;

			AUTOID(Join,getID)
		};
	}
}
