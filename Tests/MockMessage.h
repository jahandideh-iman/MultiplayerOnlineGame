#pragma once

#include "Network/Message.h"
#include <functional>

namespace mog
{
	namespace network
	{
		class MockMessage : public Message
		{
		public:
			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override;
		

			AUTOID(MockMessage, getID);

			static void setExecuteOnClientCommand(std::function<void()> f);
			static void setExecuteOnServerCommand(std::function<void()> f);

		private:
			static std::function<void()> executeOnClientFunction;
			static std::function<void()> executeOnServerFunction;

		};
	}
}

