#include "ClientNetworkManager.h"
#include "Engine/Network/ClientGame.h"
#include "Engine/Network/Messages/Message.h"

#include <assert.h>

mog::network::ClientNetworkManager::ClientNetworkManager(ClientGame *game) : NetworkManager(game)
{

}


mog::network::ClientNetworkManager::~ClientNetworkManager()
{
}

void mog::network::ClientNetworkManager::addNetworkGameObject(NetworkGameObject *object)
{
	assert(object->isReplica());

	NetworkManager::addNetworkGameObject(object);
}

void mog::network::ClientNetworkManager::removeNetworkGameObject(NetworkGameObject *object)
{
	NetworkManager::removeNetworkGameObject(object);
}

void mog::network::ClientNetworkManager::executeMessage(const Message &mesaage, const ParameterContainer &parameters, const InternetAddress &senderAddress)
{
	mesaage.executeOnClient(dynamic_cast<ClientGame*>(game), parameters, senderAddress);
}