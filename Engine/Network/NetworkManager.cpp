#include "NetworkManager.h"
#include "InternetAddress.h"
#include <iostream>
#include "Engine/Network/Messages/Message.h"
#include "Engine/Network/Messages/MessageDatabase.h"

#include "Engine/Network/GameSocket.h"

#include "Engine/Core/Buffer.h"


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


void mog::network::NetworkManager::setUpdateRate(float rate)
{
	updateRate = rate;
}

void mog::network::NetworkManager::update(float dt)
{
	elapsedTime += dt;
	if (elapsedTime >= getFrameLenght())
	{
		processUpdate();
		elapsedTime = 0;
	}
}

void mog::network::NetworkManager::processUpdate()
{
	processMessages();
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
			executeMessage(*(MessageDatabase::get()->find(messageId)), parameters, senderAddress);
		}
		else
			break;
	}

}

void mog::network::NetworkManager::sendMessage(const Message &m, const InternetAddress &dest)
{
	Buffer buffer;
	buffer.write(m.getID());
	buffer.write(":");
	m.write(&buffer);
	//buffer->write(*m.serialize());
	char *data = buffer.getData();
	socket->send(dest, data, buffer.getSize());

	delete []data;
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

std::vector<const mog::network::NetworkGameObject *> mog::network::NetworkManager::getNetworkGameObjects() const
{
	std::vector<const NetworkGameObject *> objects;

	for (auto obj : networkGameObjects)
		objects.push_back(obj.second);

	return objects;
}

void mog::network::NetworkManager::removeNetworkGameObject(NetworkGameObject *object)
{
	for (auto obj : networkGameObjects)
	{
		if (obj.second == object)
		{
			networkGameObjects.erase(obj.first);
			break;
		}
	}
}

void mog::network::NetworkManager::addNetworkGameObject(NetworkGameObject *object)
{
	networkGameObjects[object->getInstanceId()] = object;
}

float mog::network::NetworkManager::getFrameLenght()
{
	if (updateRate <= EPSILON)
		return 0;
	else
		return 1 / updateRate;
}

