#include "ServerNetworkManager.h"

#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/Messages/RemoveInstanceMessage.h"
#include "Engine/Network/Messages/ReplicateStateMessage.h"
#include "Engine/Network/ServerGame.h"

#include <set>
#include <assert.h>

namespace mog
{
	namespace network
	{
		class ClientReplicationInfo
		{
		public:
			ClientReplicationInfo(const Client * client)
			{
				this->client = client;
			}

			const InternetAddress *getAddress()
			{
				return client->address;
			}

			const Client *getClient()
			{
				return client;
			}

			void addToBeReplicatedInstance(unsigned  instanceId)
			{
				toBeReplicatedInstances.insert(instanceId);
			}


			void eraseToBeReplicatedInstance(unsigned  instanceId)
			{
				toBeReplicatedInstances.erase(instanceId);
			}

			void addToBeRemovedInstance(unsigned  instanceId)
			{
				toBeRemovedInstaces.insert(instanceId);
			}


			void eraseToBeRemovedInstance(unsigned  instanceId)
			{
				toBeRemovedInstaces.erase(instanceId);
			}

			unsigned getToBeReplicatedInstance()
			{
				return *(toBeReplicatedInstances.begin());
			}

			unsigned getToBeRemovedInstance()
			{
				return *(toBeRemovedInstaces.begin());
			}

			bool isToBeReplicatedEmpty()
			{
				return toBeReplicatedInstances.empty();
			}

			bool isToBeRemovedEmpty()
			{
				return toBeRemovedInstaces.empty();
			}

		private:
			const Client *client = nullptr;
			std::set<unsigned > toBeReplicatedInstances;
			std::set<unsigned > toBeRemovedInstaces;
		};
	}
}

mog::network::ServerNetworkManager::ServerNetworkManager(ServerGame *game) : NetworkManager(game)
{

}

mog::network::ServerNetworkManager::~ServerNetworkManager()
{
	for (auto client : clientReplicationInfos)
		delete client;
}

void mog::network::ServerNetworkManager::addClient(const Client *client)
{
	auto clientRep = new ClientReplicationInfo(client);
	for (auto networkObj : networkGameObjects)
		clientRep->addToBeReplicatedInstance(networkObj.first);

	clientReplicationInfos.push_back(clientRep);
}

void mog::network::ServerNetworkManager::removeClient(const InternetAddress *address)
{
	for (auto it = clientReplicationInfos.begin(); it != clientReplicationInfos.end(); it++)
	{
		if (*(*it)->getAddress() == *address)
		{
			delete *it;
			clientReplicationInfos.erase(it);
			break;
		}
	}
}

void mog::network::ServerNetworkManager::addNetworkGameObject(NetworkGameObject *object)
{
	assert(object->getRole() == Role_Authority);

	object->setInstanceId(lastNetworkGameObjectId);
	lastNetworkGameObjectId++;

	for (auto client : clientReplicationInfos)
		client->addToBeReplicatedInstance(object->getInstanceId());

	NetworkManager::addNetworkGameObject(object);
}

void mog::network::ServerNetworkManager::removeNetworkGameObject(NetworkGameObject *object)
{
	assert(object->getRole() == Role_Authority);

	for (auto client : clientReplicationInfos)
		client->addToBeRemovedInstance(object->getInstanceId());

	NetworkManager::removeNetworkGameObject(object);
}


void mog::network::ServerNetworkManager::update(float dt /* = 0 */)
{
	NetworkManager::update(dt);

	//NOTE: The order may be important
	processInstanceReplications();
	processInstanceRemoval();
	processStateReplications();
}

void mog::network::ServerNetworkManager::processInstanceReplications()
{
	for (auto clientRep : clientReplicationInfos)
	{
		while (!clientRep->isToBeReplicatedEmpty())
		{
			auto instanceId = clientRep->getToBeReplicatedInstance();
			auto obj = findNetworkGameObject(instanceId);
			Role role = Role_None;
			if (*clientRep->getClient() == *obj->getClient())
				role = Role_Proxy;
			else
				role = Role_Simulated;

			sendMessage(ReplicateInstanceMessage(obj, role), *(clientRep->getAddress()));
			clientRep->eraseToBeReplicatedInstance(instanceId);
		}
	}
}

void mog::network::ServerNetworkManager::processInstanceRemoval()
{
	for (auto clientRep : clientReplicationInfos)
	{
		while (!clientRep->isToBeRemovedEmpty())
		{
			auto instanceId = clientRep->getToBeRemovedInstance();
			sendMessage(RemoveInstanceMessage(instanceId), *(clientRep->getAddress()));
			clientRep->eraseToBeRemovedInstance(instanceId);
		}
	}
}

void mog::network::ServerNetworkManager::processStateReplications()
{
	for (auto clientRep : clientReplicationInfos)
	{
		for (auto netObjetPair : networkGameObjects)
			sendMessage(ReplicateStateMessage(netObjetPair.second), *(clientRep->getAddress()));
	}
}

void mog::network::ServerNetworkManager::executeMessage(const Message &message, const ParameterContainer &parameters, const InternetAddress &senderAddress)
{
	message.executeOnServer(dynamic_cast<ServerGame*>(game), parameters, senderAddress);
}

std::vector<const mog::network::InternetAddress *>  mog::network::ServerNetworkManager::getClients() const
{
	std::vector<const InternetAddress *> addresses;

	for (auto client : clientReplicationInfos)
		addresses.push_back(client->getAddress());

	return addresses;
}

bool mog::network::ServerNetworkManager::hasClient(const InternetAddress *address) const
{
	for (auto client : clientReplicationInfos)
	{
		if (*client->getAddress() == *address)
			return true;
	}
	return false;
}
