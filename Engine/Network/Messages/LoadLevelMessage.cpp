#include "LoadLevelMessage.h"
#include "Engine/LevelDatabase.h"
#include "Network/ClientGame.h"

mog::network::LoadLevelMessage::LoadLevelMessage(ID name)
{
	this->levelName = name;
}

mog::network::LoadLevelMessage::LoadLevelMessage()
{

}

mog::network::LoadLevelMessage::~LoadLevelMessage()
{
}

void mog::network::LoadLevelMessage::fillData(ParameterContainer &parameters) const
{
	parameters.put("levelName", levelName);
}

void mog::network::LoadLevelMessage::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	ID name = parameters.get("levelName");
	auto level = LevelDatabase::get()->find(name);
	level->initialGameObjects();
	game->loadLevel(level);
	/*if (GlobalData::gameType == GameType::T_Client)
	GlobalData::game->loadLevel(new GameLevel());*/
}

void mog::network::LoadLevelMessage::executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{

}
