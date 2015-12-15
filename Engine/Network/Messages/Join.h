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

			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const override;

			AUTOID(Join,getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;
		};
	}
}
