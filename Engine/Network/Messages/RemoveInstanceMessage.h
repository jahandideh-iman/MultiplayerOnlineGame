#pragma once

#include "Engine/Network/Messages/Message.h"

#include "Engine/Network/NetworkGameObject.h"

namespace mog
{
	namespace network
	{
		class NetworkGameObject;

		class RemoveInstanceMessage : public Message
		{
		public:
			RemoveInstanceMessage(unsigned instanceId);
			RemoveInstanceMessage();
			~RemoveInstanceMessage();

			void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const InternetAddress &address) const override;

			AUTOID(RemoveInstanceMessage, getID);

		protected:
			void fillData(ParameterContainer &parameters) const override;

		private:
			//NOTE: Instance ID is store because object may be deleted with fillData is called
			unsigned instanceId;
		};
	}
}
