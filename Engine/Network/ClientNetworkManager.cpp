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

void mog::network::ClientNetworkManager::addNetworkGameObject(NetworkGameObject *o)
{
	assert(o->isReplica());

	networkGameObjects[o->getInstanceId()] = o;
}

void mog::network::ClientNetworkManager::executeMessage(const Message &mesaage, const ParameterContainer &parameters, const InternetAddress &senderAddress)
{
	mesaage.executeOnClient(dynamic_cast<ClientGame*>(game), parameters, senderAddress);
}
