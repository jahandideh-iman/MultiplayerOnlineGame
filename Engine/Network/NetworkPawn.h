#pragma once

#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Core/Types.h"

namespace mog
{
	namespace network
	{
		class NetworkPawn : public NetworkGameObject
		{
		public:
			NetworkPawn();
			~NetworkPawn();

			void update(float dt) override;

			AUTOID(NetworkPawn, getNetworkID);

			void setVelocity(Vector velocity);
			void setVelocityX(float x);
			void setVelocityY(float y);
			Vector getVelocity() const;

		private:
			Vector velocity;
		};
	}
}
