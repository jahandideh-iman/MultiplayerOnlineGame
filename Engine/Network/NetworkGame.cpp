#include "NetworkGame.h"
#include "Network/NetworkManager.h"


mog::network::NetworkGame::NetworkGame()
{
	networkManager = new NetworkManager(this);
}


mog::network::NetworkGame::~NetworkGame()
{
	delete networkManager;
}


mog::network::NetworkManager * mog::network::NetworkGame::getNetworkManager()
{
	return networkManager;
}
