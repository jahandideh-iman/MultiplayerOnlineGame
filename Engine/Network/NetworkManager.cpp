#include "NetworkManager.h"
#include "InternetAddress.h"
#include <iostream>
#include "Engine/Network/Messages/Message.h"
#include "Engine/Network/Messages/MessageDatabase.h"
#include "Engine/Network/Messages/ReplicateStateMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"

#include "Engine/Network/GameSocket.h"
#include "Engine/Network/NetworkGame.h"

#include "Engine/Core/Buffer.h"
#include "Engine/Network/ClientGame.h"
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

mog::network::NetworkManager::NetworkManager(NetworkGame *game)
{
	this->game = game;
}


mog::network::NetworkManager::~NetworkManager()
{
	delete socket;
	for (auto client : clientReplicationInfos)
		delete client;
}


void mog::network::NetworkManager::setSocket(GameSocket *socket)
{
	this->socket = socket;
}


void mog::network::NetworkManager::setPort(unsigned port)
{
	socket->open(port);
}

void mog::network::NetworkManager::update(float dt)
{
	if (game->getType() == T_Server)
		processReplications();

	processMessages();
}

void mog::network::NetworkManager::sendMessage(const Message &m, const InternetAddress &dest)
{
	auto buffer = new mog::Buffer();
	buffer->write(m.getID());
	buffer->write(":");
	m.write(buffer);
	//buffer->write(*m.serialize());
	char *data = buffer->getData();
	socket->send(dest, data, buffer->getSize());

	delete []data;
	delete buffer;
}

mog::ID mog::network::NetworkManager::extractMessageId(char* message, unsigned size)
{
	char *buffer = new char[size];
	unsigned i;
	for (i = 0; i < size; i++)
	{
		if (message[i] == ':')
			break;
		buffer[i] = message[i];
	}
	buffer[i] = '\0';

	ID id(buffer);
	delete []buffer;
	return id;
	//return atoi(buffer);
}

mog::Buffer mog::network::NetworkManager::extractMessageData(char* message, unsigned size)
{
	unsigned i;
	for (i = 0; i < size; i++)
	{
		if (message[i] == ':')
			break;
	}

	return Buffer(message+i+1);
}

void mog::network::NetworkManager::addNetworkGameObject(NetworkGameObject *o)
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

void mog::network::NetworkManager::processMessages()
{
	InternetAddress senderAddress;
	
	while (true)
	{
		char data[256];
		auto size = socket->receive(senderAddress, data, 256);

		if (size != 0)
		{
			ID messageId = extractMessageId(data, size);
			Buffer messageData = extractMessageData(data, size);
			ParameterContainer parameters(&messageData);
			//CCLOG("Message ID is : %s", messageId.c_str());
			//CCLOG("data is : %s", messageData.getData());
			if (game->getType() == T_Client)
				MessageDatabase::get()->find(messageId)->executeOnClient(dynamic_cast<ClientGame*>(game), parameters, senderAddress);
			else if (game->getType() == T_Server)
				MessageDatabase::get()->find(messageId)->executeOnServer(dynamic_cast<ServerGame*>(game), parameters, senderAddress);
		}
		else
			break;
	}

}

void mog::network::NetworkManager::processReplications()
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

void mog::network::NetworkManager::addClient(const InternetAddress *address)
{
	auto clientRep = new ClientReplicationInfo(address);
	for (auto networkObj : networkGameObjects)
		clientRep->addToBeReplicatedInstance(networkObj.first);

	clientReplicationInfos.push_back(clientRep);
}

std::vector<const mog::network::InternetAddress *>  mog::network::NetworkManager::getClients() const
{
	std::vector<const InternetAddress *> addresses;

	for (auto client : clientReplicationInfos)
		addresses.push_back(client->getAddress());

	return addresses;
}

bool mog::network::NetworkManager::hasNetworkGameObject(const NetworkGameObject *gameObj) const
{
	for (auto obj : networkGameObjects)
	{
		if (obj.second == gameObj)
			return true;
	}

	return false;
}

bool mog::network::NetworkManager::hasNetworkGameObject(unsigned instanceId) const
{
	return findNetworkGameObject(instanceId) != nullptr;
}

mog::network::NetworkGameObject * mog::network::NetworkManager::findNetworkGameObject(unsigned instaceId) const
{
	auto p = networkGameObjects.find(instaceId);

	if (p == networkGameObjects.end())
		return nullptr;
	return p->second;
}
