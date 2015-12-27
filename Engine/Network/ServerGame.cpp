#include "ServerGame.h"
#include "Network/NetworkManager.h"
#include "Network/Messages/LoadLevelMessage.h"
#include "network/ReplicateInstance.h"

mog::network::ServerGame::ServerGame()
{
}


mog::network::ServerGame::~ServerGame()
{
	for (auto p : playersInfo)
		delete p;
}

void mog::network::ServerGame::joinNewPlayer(PlayerInfo *info)
{
	playersInfo.push_back(info);
	getNetworkManager()->addClient(info->address);

	/*network::NetworkGameObject *p = new Pawn();
	p->setPosition(Point(200, 200));
	addGameObject(p);


	getNetworkManager()->sendMessage(mog::network::LoadLevel(currentLevel->getName()), *info->address);
	getNetworkManager()->sendMessage(mog::network::ReplicateInstance(p), *info->address);*/

	//NetworkManager::sendMessage();
}

const mog::network::PlayerInfo * mog::network::ServerGame::getPlayerInfoByName(std::string name) const
{
	for (auto p : playersInfo)
	{
		if (p->name == name)
			return p;
	}

	return nullptr;
}
