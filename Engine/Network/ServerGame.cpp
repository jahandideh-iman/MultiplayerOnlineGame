#include "ServerGame.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Engine/Network/ServerNetworkManager.h"

#include "Engine/Network/NetworkPawn.h"
#include "Engine/Network/NetworkPawnFactory.h"
#include "Engine/Core/LevelFactory.h"

mog::network::ServerGame::ServerGame()
{
	networkManager = new ServerNetworkManager(this);
}


mog::network::ServerGame::~ServerGame()
{
	for (auto p : playersInfo)
		delete p;
}

void mog::network::ServerGame::joinNewPlayer(Client *client)
{
	playersInfo.push_back(client);
	dynamic_cast<ServerNetworkManager* > (getNetworkManager())->addClient(client->address);

	NetworkPawn *pawn;
	if (NetworkPawnFactory::get()->isSet())
		pawn = NetworkPawnFactory::get()->create();
	else
		pawn = new NetworkPawn();

	pawn->setClinet(client);
	addGameObject(pawn);
	onPawnCreated(pawn);

	if (LevelFactory::get()->isSet())
	{
		auto level = LevelFactory::get()->create();
		getNetworkManager()->sendMessage(LoadLevelMessage(level), *client->address);
		delete level;
	}
}


void mog::network::ServerGame::removePlayer(const Client *info)
{
	for (auto it = playersInfo.begin(); it != playersInfo.end(); it++)
	{
		auto pInfo = *it;
		if (*pInfo == *info)
		{
			playersInfo.erase(it);
			dynamic_cast<ServerNetworkManager* > (getNetworkManager())->removeClient(info->address);
			delete pInfo;
			break;
		}
	}
}

const mog::network::Client * mog::network::ServerGame::getPlayerInfoByName(std::string name) const
{
	for (auto p : playersInfo)
	{
		if (p->name == name)
			return p;
	}

	return nullptr;
}

bool mog::network::ServerGame::hasClient(const Client* info) const
{
	for (auto p : playersInfo)
	{
		if (*p == *info)
			return true;
	}

	return false;
}
