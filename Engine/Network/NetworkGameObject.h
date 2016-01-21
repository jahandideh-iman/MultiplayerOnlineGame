#pragma once

#include "Engine/Core/GameObject.h"
#include "Engine/Network/NetworkObject.h"

#include <functional>
#include <map>
#include "Engine/Network/Client.h"

namespace mog
{

	namespace network
	{
		class Client;
		class NetworkComponent;
		class NetworkGame;

		enum  Role
		{
			Role_None,
			Role_Authority,
			Role_Proxy,
			Role_Simulated,
		};

		class NetworkGameObject : public GameObject, public NetworkObject
		{
			typedef std::function<void()> Method;
		public:
			NetworkGameObject();

			virtual ~NetworkGameObject();

			void onRemovedFromGame(Game *game) override;

			virtual void initialRegisteredMethods();

			void updatePosition(float dt) override;

			void callMethod(std::string name);

			unsigned getInstanceId() const;
			void setInstanceId(unsigned i);

			void writeState(Buffer *buffer) const;
			void readState(const Buffer *buffer);

			NetworkComponent *getNetworkComponent();

			void setClient(const Client *client);
			const Client *getClient() const;

			Role getRole() const;
			//WARNING: It must not be public
			//TODO: Find a way to make it private
			void setRole(Role role);


			NetworkGame *getNetworkGame();

		protected:
			void onAddedToGame(Game *game) override;
			void registerMethod(std::string name,Method method);

		protected:
			NetworkComponent *networkComponent = nullptr;

		private:
			unsigned instanceId;

			const Client *client = nullptr;

			std::map<std::string, Method> registeredMethods;

			Role role;
		};
	}
}
