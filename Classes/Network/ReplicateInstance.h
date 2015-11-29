#pragma once

#include "Message.h"

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

			virtual void execute(const ParameterContainer &parameters, const network::InternetAddress &address) const override;

			AUTOID(ReplicateInstance,getID)

		protected:
			virtual void fillData(ParameterContainer *parameters) const override;

		private:
			NetworkGameObject *object = nullptr;

		};
	}
}
