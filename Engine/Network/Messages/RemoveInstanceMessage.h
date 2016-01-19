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
			RemoveInstanceMessage(const NetworkGameObject *gameObject);
			RemoveInstanceMessage();
			~RemoveInstanceMessage();

			void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const InternetAddress &address) const override;

			AUTOID(RemoveInstanceMessage, getID);

		protected:
			void fillData(ParameterContainer &parameters) const override;

		private:
			const NetworkGameObject *gameObject;
		};
	}
}
