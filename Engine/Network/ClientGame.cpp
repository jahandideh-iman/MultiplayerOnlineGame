#include "ClientGame.h"
#include "Engine/Network/ClientNetworkManager.h"
#include "Engine/Network/Messages/RemoteMethodCallMessage.h"


mog::network::ClientGame::ClientGame()
{
	networkManager = new ClientNetworkManager(this);
}


mog::network::ClientGame::~ClientGame()
{
}

void mog::network::ClientGame::remoteMethodCall(std::string method, const NetworkGameObject *obj)
{
	getNetworkManager()->sendMessage(RemoteMethodCallMessage(obj, method), getServerAddress());
}

mog::network::InternetAddress mog::network::ClientGame::getServerAddress()
{
	return serverAddress;
}

void mog::network::ClientGame::setServerAddress(InternetAddress address)
{
	this->serverAddress = address;
}
