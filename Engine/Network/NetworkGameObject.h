#pragma once

#include "Engine/Core/GameObject.h"
#include "Engine/Network/NetworkObject.h"

namespace mog
{
	namespace network
	{
		class NetworkComponent;
		class NetworkGameObject : public GameObject, public NetworkObject
		{
		public:
			NetworkGameObject();

			virtual ~NetworkGameObject();

			virtual void onAddedToGame(Game *game) override;

			unsigned getInstanceId() const;
			void setInstanceId(unsigned i);

			void writeState(Buffer *buffer) const;

			//TODO: Find a way to reject more that one call to this function
			void setIsReplica(bool isReplical);
			bool isReplica() const;

		protected:
			NetworkComponent *networkComponent = nullptr;

		private:
			unsigned instanceId;

			bool bIsReplica = false;

			
		};
	}
}
