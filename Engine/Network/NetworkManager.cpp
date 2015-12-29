#include "NetworkManager.h"
#include "InternetAddress.h"
#include <iostream>
#include "Engine/Network/Messages/MessageDatabase.h"
#include "Engine/Network/ReplicateState.h"
#include "Engine/Network/GameSocket.h"
#include "Engine/Network/NetworkGame.h"
#include "Engine/Network/Messages/Message.h"
#include "Engine/Core/Buffer.h"
#include "Engine/Network/ClientGame.h"
#include "Engine/Network/ServerGame.h"


mog::network::NetworkManager::NetworkManager(NetworkGame *game)
{
	this->game = game;
}


mog::network::NetworkManager::~NetworkManager()
{
	delete socket;
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
	char buffer[21];
	int i;
	for (i = 0; i < 20; i++)
	{
		if (message[i] == ':')
			break;
		buffer[i] = message[i];
	}
	buffer[i] = '\0';

	return ID(buffer);
	//return atoi(buffer);
}

mog::Buffer mog::network::NetworkManager::extractMessageData(char* message, unsigned size)
{
	int i;
	for (i = 0; i < 20; i++)
	{
		if (message[i] == ':')
			break;
	}

	return Buffer(message+i+1);
}

void mog::network::NetworkManager::addNetworkGameObject(NetworkGameObject *o)
{
	networkGameObjects.emplace(lastNetworkGameObjectId, o);
	o->setIndex(lastNetworkGameObjectId);
	lastNetworkGameObjectId++;
}

void mog::network::NetworkManager::addNetworkComponent(NetworkComponent *c)
{
	networkComponents.emplace(lastNetworkComponentId, c);
	//c->setIndex(lastNetworkComponentId);
	lastNetworkComponentId++;
}

void mog::network::NetworkManager::processMessages()
{
	InternetAddress senderAddress;
	char data[256];
	auto size = socket->receive(senderAddress, data, 256);

	if (size != 0)
	{
		ID messageId = extractMessageId(data, size);
		Buffer messageData = extractMessageData(data, size);
		ParameterContainer parameters(messageData);
		//CCLOG("Message ID is : %s", messageId.c_str());
		//CCLOG("data is : %s", messageData.getData());
		if (game->getType() == T_Client)
			MessageDatabase::get()->find(messageId)->executeOnClient(dynamic_cast<ClientGame*>(game), parameters, senderAddress);
		else if (game->getType() == T_Server)
			MessageDatabase::get()->find(messageId)->executeOnServer(dynamic_cast<ServerGame*>(game), parameters, senderAddress);
	}
}

void mog::network::NetworkManager::processReplications()
{
	
	for (auto elem : networkComponents)
	{
		unsigned index = elem.first;
		auto component = elem.second;
		Buffer buffer;
		component->writeReplications(&buffer);
		if (!buffer.isEmpty())
		{
			for (auto client : clientAddresses)
			{
				sendMessage(ReplicateState(index,&buffer), *client);
			}
		}
	}

	//sendMessage(
}

void mog::network::NetworkManager::addClient(const InternetAddress *address)
{
	clientAddresses.emplace_back(address);
}

const std::vector<const mog::network::InternetAddress *> & mog::network::NetworkManager::getClients() const
{
	return clientAddresses;
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

bool mog::network::NetworkManager::hasNetworkComponent(const NetworkComponent *comp) const
{
	for (auto c : networkComponents)
	{
		if (c.second == comp)
			return true;
	}

	return false;
}
