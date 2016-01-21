#pragma once

#include "Engine/Network/Messages/Message.h"

namespace mog
{
	namespace network
	{
		class NetworkGameObject;
		enum Role;
		class ReplicateInstanceMessage : public Message
		{
		public:
			ReplicateInstanceMessage(const NetworkGameObject *object,Role role);
			ReplicateInstanceMessage();
			~ReplicateInstanceMessage();

			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;

			AUTOID(ReplicateInstanceMessage,getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;

		private:
			const NetworkGameObject *object = nullptr;
			Role role;

		};
	}
}
