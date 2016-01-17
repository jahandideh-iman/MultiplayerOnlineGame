#include "ServerNetworkManager.h"

#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/ServerGame.h"

#include <set>

namespace mog
{
	namespace network
	{
		class ClientReplicationInfo
		{
		public:
			ClientReplicationInfo(const InternetAddress * address)
			{
				this->address = address;
			}

			const InternetAddress *getAddress()
			{
				return address;
			}

			void addToBeReplicatedInstance(unsigned  instanceId)
			{
				toBeReplicatedInstances.insert(instanceId);
			}

			void removeToBeReplicatedInstance(unsigned  instanceId)
			{
				toBeReplicatedInstances.erase(instanceId);
			}

			unsigned getToBeReplicatedInstance()
			{
				return *(toBeReplicatedInstances.begin());
			}

			bool isEmpty()
			{
				return toBeReplicatedInstances.empty();
			}

		private:
			const InternetAddress *address = nullptr;
			std::set<unsigned > toBeReplicatedInstances;
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

void mog::network::ServerNetworkManager::addClient(const InternetAddress *address)
{
	auto clientRep = new ClientReplicationInfo(address);
	for (auto networkObj : networkGameObjects)
		clientRep->addToBeReplicatedInstance(networkObj.first);

	clientReplicationInfos.push_back(clientRep);
}

std::vector<const mog::network::InternetAddress *>  mog::network::ServerNetworkManager::getClients() const
{
	std::vector<const InternetAddress *> addresses;

	for (auto client : clientReplicationInfos)
		addresses.push_back(client->getAddress());

	return addresses;
}

void mog::network::ServerNetworkManager::addNetworkGameObject(NetworkGameObject *o)
{
	if (o->isReplica() == false)
	{
		o->setInstanceId(lastNetworkGameObjectId);
		lastNetworkGameObjectId++;

		for (auto client : clientReplicationInfos)
		{
			client->addToBeReplicatedInstance(o->getInstanceId());
		}
	}

	networkGameObjects[o->getInstanceId()] = o;
}

void mog::network::ServerNetworkManager::update(float dt /* = 0 */)
{
	processReplications();
	NetworkManager::update(dt);
}

void mog::network::ServerNetworkManager::processReplications()
{
	for (auto clientRep : clientReplicationInfos)
	{
		while (!clientRep->isEmpty())
		{
			auto instanceId = clientRep->getToBeReplicatedInstance();
			sendMessage(ReplicateInstanceMessage(findNetworkGameObject(instanceId)), *(clientRep->getAddress()));
			clientRep->removeToBeReplicatedInstance(instanceId);
		}
	}
}

void mog::network::ServerNetworkManager::executeMessage(const Message &message, const ParameterContainer &parameters, const InternetAddress &senderAddress)
{
	message.executeOnServer(dynamic_cast<ServerGame*>(game), parameters, senderAddress);
}
