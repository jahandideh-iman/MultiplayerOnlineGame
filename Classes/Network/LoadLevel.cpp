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


mog::network::Buffer *mog::network::LoadLevel::serialize() const
{
	auto buffer = new Buffer();
	buffer->write(levelName);
	
	return buffer;
}

void mog::network::LoadLevel::execute(const Buffer &data, const network::InternetAddress &address) const
{
	if (GlobalData::gameType == GameType::T_Client)
		GlobalData::game->LoadLevel(new GameLevel());
}
