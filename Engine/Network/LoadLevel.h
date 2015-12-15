#pragma once

#include "Network/Messages/Message.h"

namespace mog
{
	namespace network
	{
		class LoadLevel : public Message
		{
		public:
			LoadLevel(char *name);
			LoadLevel();
			~LoadLevel();

			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
			
			AUTOID(LoadLevel, getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;

		private:
			char *levelName = nullptr;
		};
	}
}