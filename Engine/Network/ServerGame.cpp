#include "ServerGame.h"
#include "Network/NetworkManager.h"
#include "Network/LoadLevel.h"
#include "network/ReplicateInstance.h"

mog::network::ServerGame::ServerGame()
{
}


mog::network::ServerGame::~ServerGame()
{
}

void mog::network::ServerGame::joinNewPlayer(PlayerInfo *info)
{
	playersInfo.push_back(info);
	/*network::NetworkGameObject *p = new Pawn();
	p->setPosition(Point(200, 200));
	addGameObject(p);

	getNetworkManager()->addClient(info->address);

	getNetworkManager()->sendMessage(mog::network::LoadLevel(currentLevel->getName()), *info->address);
	getNetworkManager()->sendMessage(mog::network::ReplicateInstance(p), *info->address);*/

	//NetworkManager::sendMessage();
}