#include "NetworkGame.h"
#include "Engine/Network/NetworkManager.h"


mog::network::NetworkGame::NetworkGame()
{
}


mog::network::NetworkGame::~NetworkGame()
{
	delete networkManager;
}


mog::network::NetworkManager * mog::network::NetworkGame::getNetworkManager()
{
	return networkManager;
}

void mog::network::NetworkGame::internalUpdate(float dt /*= 0*/)
{
	Game::internalUpdate(dt);
	getNetworkManager()->update(dt);
}
