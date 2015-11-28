#pragma once

#include "Engine/GameObject.h"
#include "Network/NetworkObject.h"

namespace mog
{
	namespace network
	{
		class NetworkGameObject : public GameObject, public NetworkObject
		{
		public:
			NetworkGameObject();
			virtual ~NetworkGameObject();

			virtual void addSelfToGame(Game *game);

			unsigned getIndex();
			void setIndex(unsigned i);

		private:
			unsigned index;
		};
	}
}
