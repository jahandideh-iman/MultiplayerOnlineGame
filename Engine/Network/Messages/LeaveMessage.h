#pragma once

#include "Engine/Network/Messages/Message.h"

namespace mog
{
	namespace network
	{
		class LeaveMessage : public Message
		{
		public:
			LeaveMessage();
			LeaveMessage(std::string playerName);
			~LeaveMessage();

			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const override;

			AUTOID(LeaveMessage, getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;
		
		private:
			std::string playerName;
		};
	}
}

