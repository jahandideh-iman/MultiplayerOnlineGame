#pragma once

#include "Engine/Network/Messages/Message.h"

#include <string>

namespace mog
{
	namespace network
	{
		class NetworkGameObject;

		class RemoteMethodCallMessage : public Message
		{
		public:
			RemoteMethodCallMessage();

			RemoteMethodCallMessage(const NetworkGameObject *object, std::string methodName);
			virtual ~RemoteMethodCallMessage();

			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const InternetAddress &address) const override;

			AUTOID(RemoteMethodCallMessage, getID);

		protected:
			virtual void fillData(ParameterContainer &parameters) const override;

		private:
			const NetworkGameObject *object = nullptr;
			std::string methodName;
		};
	}
}


