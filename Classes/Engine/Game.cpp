#include "Game.h"
#include "GlobalData.h"


mog::Game::Game()
{
	GlobalData::game = this;
}


mog::Game::~Game()
{
	GlobalData::game = nullptr;
}
