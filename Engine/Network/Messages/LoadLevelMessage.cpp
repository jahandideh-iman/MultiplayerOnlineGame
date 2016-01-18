#include "LoadLevelMessage.h"
#include "Engine/Core/LevelDatabase.h"
#include "Engine/Network/ClientGame.h"

mog::network::LoadLevelMessage::LoadLevelMessage(const Level *level)
{
	this->level = level;
}

mog::network::LoadLevelMessage::LoadLevelMessage()
{

}

mog::network::LoadLevelMessage::~LoadLevelMessage()
{
}

void mog::network::LoadLevelMessage::fillData(ParameterContainer &parameters) const
{
	parameters.put("levelName", level->getID());
}

void mog::network::LoadLevelMessage::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	ID name = parameters.get("levelName");
	auto level = LevelDatabase::get()->find(name);
	level->initialGameObjects();
	game->loadLevel(level);
}

void mog::network::LoadLevelMessage::executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{

}
