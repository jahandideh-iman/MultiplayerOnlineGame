#include "LoadLevel.h"
#include <iostream>
#include "Engine/GlobalData.h"
#include "Game/GameLevel.h"


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

unsigned mog::network::LoadLevel::getCode() const
{
	return 2000;
}

mog::network::NetworkData * mog::network::LoadLevel::write() const
{
	auto data = new char[20];
	auto s = sprintf(data, "%u", this->getCode());
	strcpy(&data[s + 1], levelName);

	NetworkData *nd = new NetworkData(data, s + 1 + 6);
	return nd;
}

void mog::network::LoadLevel::execute(const NetworkData &data, const network::InternetAddress &address) const
{
	if (GlobalData::gameType == GameType::T_Client)
		GlobalData::game->LoadLevel(new GameLevel());
}
