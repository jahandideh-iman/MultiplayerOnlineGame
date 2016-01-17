#pragma once
#include "Engine/Network/Messages/Message.h"
namespace mog
{
	namespace network
	{
		class JoinMessage :
			public Message
		{
		public:
			JoinMessage(std::string playerName);
			JoinMessage();
			~JoinMessage();

			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const override;

			AUTOID(JoinMessage,getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;

		private:
			std::string playerName;
		};
	}
}
