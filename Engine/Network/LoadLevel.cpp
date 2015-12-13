#include "LoadLevel.h"
#include <iostream>


mog::network::LoadLevel::LoadLevel(char *name)
{
	this->levelName = name;
}

mog::network::LoadLevel::LoadLevel()
{

}

mog::network::LoadLevel::~LoadLevel()
{
}

void mog::network::LoadLevel::execute(const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	/*if (GlobalData::gameType == GameType::T_Client)
		GlobalData::game->loadLevel(new GameLevel());*/
}

void mog::network::LoadLevel::fillData(ParameterContainer &parameters) const
{
	parameters.put("levelName", levelName);
}
