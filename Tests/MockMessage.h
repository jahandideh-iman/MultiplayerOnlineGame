#pragma once

#include "Network/Message.h"
#include <functional>

namespace mog
{
	namespace network
	{
		class MockMessage : public network::Message
		{
		public:

			void execute(const ParameterContainer &parameters, const network::InternetAddress &address) const override;

			AUTOID(MockMessage, getID);

			static void setExecuteCommand(std::function<void()> f);

		private:
			static std::function<void()> executeFunction;

		};
	}
}

