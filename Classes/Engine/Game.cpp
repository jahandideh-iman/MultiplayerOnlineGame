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

void mog::Game::LoadLevel(Level *level)
{
	currentLevel = level;
	for (GameObject *o : level->getGameObjects())
	{
		o->addSelfToGame(this);
	}
}



