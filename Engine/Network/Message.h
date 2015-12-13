#pragma once

#include "InternetAddress.h"

#include "Engine/Types.h"
#include "Engine/Macros.h"

#include "Engine/ParameterContainer.h"

namespace mog
{
	namespace network
	{
		class ClientGame;
		class ServerGame;

		class Message
		{

		public:
			Message();
			virtual ~Message();

			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const {}
			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const {}
		
			void write(Buffer *buffer) const;

			virtual ID getID() const = 0;

		protected:
			virtual void fillData(ParameterContainer &parameters) const {}

		protected:
			static unsigned int code;
		};

	}
}