#include "GlobalData.h"


mog::GlobalData *mog::GlobalData::gd = nullptr;



void mog::GlobalData::clear()
{
	delete gd;
	gd = nullptr;
}

void mog::GlobalData::setGame(Game *g)
{
	game = g;
}

void mog::GlobalData::setGameType(GameType t)
{
	gameType = t;
}

mog::Game * mog::GlobalData::getGame()
{
	return game;
}

mog::GameType mog::GlobalData::getGameType()
{
	return gameType;
}
