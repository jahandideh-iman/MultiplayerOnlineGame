#pragma once

#include "Network/Message.h"
#include "Engine/Buffer.h"

namespace mog
{
	namespace network
	{
		class ReplicateState : public Message
		{
		public:
			ReplicateState();
			ReplicateState(unsigned componentIndex, Buffer *variables);
			virtual ~ReplicateState();

			virtual void execute(const ParameterContainer &parameters, const network::InternetAddress &address) const;

			AUTOID(ReplicateState,getID)
		protected:
			virtual void fillData(ParameterContainer &parameters) const;

			Buffer *variables = nullptr;
			unsigned componentIndex;
		
		};
	}
}