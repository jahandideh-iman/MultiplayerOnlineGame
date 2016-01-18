#pragma once

#include "Engine/Network/Messages/Message.h"
#include "Engine/Core/Types.h"

namespace mog
{
	class Level;

	namespace network
	{
	
		class LoadLevelMessage : public Message
		{
		public:
			LoadLevelMessage(const Level *level);
			LoadLevelMessage();
			~LoadLevelMessage();

			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
			
			AUTOID(LoadLevelMessage, getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;

		private:
			const Level *level;
		};
	}
}