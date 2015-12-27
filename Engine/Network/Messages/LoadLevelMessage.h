#pragma once

#include "Network/Messages/Message.h"
#include "Engine/Types.h"

namespace mog
{
	namespace network
	{
		class LoadLevelMessage : public Message
		{
		public:
			LoadLevelMessage(ID name);
			LoadLevelMessage();
			~LoadLevelMessage();

			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
			
			AUTOID(LoadLevelMessage, getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;

		private:
			ID levelName;
		};
	}
}