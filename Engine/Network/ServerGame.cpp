#include "ServerGame.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/ServerNetworkManager.h"

#include "Engine/Network/NetworkPawn.h"

mog::network::ServerGame::ServerGame()
{
	networkManager = new ServerNetworkManager(this);
}


mog::network::ServerGame::~ServerGame()
{
	for (auto p : playersInfo)
		delete p;
}

void mog::network::ServerGame::joinNewPlayer(PlayerInfo *info)
{
	playersInfo.push_back(info);
	dynamic_cast<ServerNetworkManager* > (getNetworkManager())->addClient(info->address);

	auto pawn = new NetworkPawn();

	addGameObject(pawn);
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
