#pragma once

#include "Network/Messages/Message.h"

namespace mog
{
	namespace network
	{
		class NetworkGameObject;
		class ReplicateInstance : public Message
		{
		public:
			ReplicateInstance(NetworkGameObject *object);
			ReplicateInstance();
			~ReplicateInstance();

			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;

			AUTOID(ReplicateInstance,getID)

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;

		private:
			NetworkGameObject *object = nullptr;

		};
	}
}
