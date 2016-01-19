#pragma once

#include "Engine/Core/GameObject.h"
#include "Engine/Network/NetworkObject.h"

#include <functional>
#include <map>

namespace mog
{
	namespace network
	{
		class NetworkComponent;
		class NetworkGameObject : public GameObject, public NetworkObject
		{
			typedef std::function<void()> Method;
		public:
			NetworkGameObject();

			virtual ~NetworkGameObject();

			void onAddedToGame(Game *game) override;
			void onRemovedFromGame(Game *game) override;

			virtual void initialRegisteredMethods();

			void updatePosition(float dt) override;

			void callMethod(std::string name);

			unsigned getInstanceId() const;
			void setInstanceId(unsigned i);

			void writeState(Buffer *buffer) const;
			void readState(const Buffer *buffer);

			NetworkComponent *getNetworkComponent();

			//TODO: Find a way to reject more that one call to this function
			void setIsReplica(bool isReplical);
			bool isReplica() const;

		protected:
			void registerMethod(std::string name,Method method);

		protected:
			NetworkComponent *networkComponent = nullptr;

		private:
			unsigned instanceId;

			bool bIsReplica = false;

			std::map<std::string, Method> registeredMethods;
		};
	}
}
