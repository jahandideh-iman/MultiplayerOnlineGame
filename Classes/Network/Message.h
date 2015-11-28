#pragma once

#include "InternetAddress.h"

#include "Engine/Types.h"
#include "Engine/Macros.h"

#include "Network/ParameterContainer.h"

namespace mog
{
	namespace network
	{
		class Message
		{

		public:
			Message();
			virtual ~Message();

			virtual void execute(const ParameterContainer &parameters, const network::InternetAddress &address) const = 0;
			Buffer *serialize() const ;
			virtual ID getID() const = 0;

		protected:
			virtual void fillData(ParameterContainer *parameters) const = 0;

		protected:
			static unsigned int code;
		};

	}
}