#pragma once

#include "Engine/Core/GameObject.h"
#include "Engine/Network/NetworkObject.h"

namespace mog
{
	namespace network
	{
		class NetworkGameObject : public GameObject, public NetworkObject
		{
		public:
			NetworkGameObject();
			virtual ~NetworkGameObject();

			virtual void onAddedToGame(Game *game) override;

			unsigned getIndex();
			void setIndex(unsigned i);

		private:
			unsigned index;
		};
	}
}
