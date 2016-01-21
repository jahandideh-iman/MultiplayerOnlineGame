#pragma once

#include "Engine/Network/Messages/Message.h"

namespace mog
{
	class Buffer;
	namespace network
	{
		class NetworkGameObject;
		class ReplicateStateMessage : public Message
		{
		public:
			ReplicateStateMessage();
			ReplicateStateMessage(const NetworkGameObject *object, bool dirtyOnly = false);
			virtual ~ReplicateStateMessage();

			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;

			AUTOID(ReplicateStateMessage,getID)
		protected:
			virtual void fillData(ParameterContainer &parameters) const;

		private:
			const NetworkGameObject *networkGameObject;
			bool dirtyOnly = false;
		};
	}
}