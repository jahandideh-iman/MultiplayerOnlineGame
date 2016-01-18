#include "ServerGame.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/ServerNetworkManager.h"

#include "Engine/Network/NetworkPawn.h"
#include "Engine/Network/NetworkPawnFactory.h"

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

	NetworkPawn *pawn;
	if (NetworkPawnFactory::get()->isSet())
		pawn = NetworkPawnFactory::get()->create();
	else
		pawn = new NetworkPawn();

	addGameObject(pawn);
	onPawnCreated(pawn);
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
