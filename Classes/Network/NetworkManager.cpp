#include "NetworkManager.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "GameSocket.h"
#include "InternetAddress.h"
#include <iostream>
#include "MessageDatabase.h"

#include "cocos2d.h" //For CCLOG 
#include "Message.h"


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
		CCLOG("data is : %s", data);
		auto id = extractMessageId(data, size);
		MessageDatabase::get()->find(id)->execute(NetworkData(data,size), senderAddress);
	}
		
}

void NetworkManager::sendMessage(const Message &m, const InternetAddress &dest)
{
	NetworkData *nd = m.write();
	socket->send(dest, nd->data, nd->size);

	delete nd;
}

unsigned NetworkManager::extractMessageId(char* message, unsigned size)
{
	char buffer[10];
	strcpy(buffer, message);
	CCLOG("Message ID is : %s", buffer);
	return atoi(buffer);
}
