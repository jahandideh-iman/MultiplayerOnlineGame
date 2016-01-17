#include "ClientGame.h"
#include "Engine/Network/ClientNetworkManager.h"


mog::network::ClientGame::ClientGame()
{
	networkManager = new ClientNetworkManager(this);
}


mog::network::ClientGame::~ClientGame()
{
}