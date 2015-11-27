#include "NetworkManager.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "GameSocket.h"
#include "InternetAddress.h"
#include <iostream>
#include "MessageDatabase.h"

#include "cocos2d.h" //For CCLOG 
#include "Message.h"
#include "Buffer.h"


using namespace mog::network;

NetworkManager *NetworkManager::manager = nullptr;

NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
	delete socket;
}

NetworkManager * NetworkManager::get()
{
	if (manager == nullptr)
		manager = new NetworkManager();
	return manager;
}

bool NetworkManager::setup()
{
	WSADATA wsaData;

	// Initialize Winsock
	auto iResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	return true;
}

bool NetworkManager::teardown()
{
	delete manager;
	::WSACleanup();
	return true;
}

void NetworkManager::setPort(unsigned port)
{
	socket = new network::GameSocket();
	socket->open(port);
}

void NetworkManager::update(float dt)
{
	InternetAddress senderAddress;
	char data[256];
	auto size = socket->receive(senderAddress, data, 256);

	if (size != 0)
	{
		ID messageId = extractMessageId(data, size);
		Buffer messageData = extractMessageData(data, size);
		CCLOG("Message ID is : %s", messageId.c_str());
		CCLOG("data is : %s", messageData.getData());
		MessageDatabase::get()->find(messageId)->execute(messageData, senderAddress);
	}
		
}

void NetworkManager::sendMessage(const Message &m, const InternetAddress &dest)
{
	auto buffer = new Buffer();
	buffer->write(m.getID());
	buffer->write(":");
	buffer->write(*m.serialize());
	socket->send(dest, buffer->getData(), buffer->getSize());

	delete buffer;
}

mog::ID NetworkManager::extractMessageId(char* message, unsigned size)
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

mog::network::Buffer mog::network::NetworkManager::extractMessageData(char* message, unsigned size)
{
	int i;
	for (i = 0; i < 20; i++)
	{
		if (message[i] == ':')
			break;
	}

	return Buffer(message+i+1);
}
