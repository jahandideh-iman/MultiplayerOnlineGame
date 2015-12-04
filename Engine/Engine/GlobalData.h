#pragma once

#include "Game.h"

#define GLOBAL_DATA() GlobalData::get()

namespace mog
{
	enum GameType {T_None, T_Server, T_Client};
	class GlobalData
	{
	public:
		static GlobalData *get();
		static void clear();

		void setGame(Game *g);
		void setGameType(GameType t);

		Game *getGame();
		GameType getGameType();

		

	private:
		GlobalData(){};

	private:
		static GlobalData *gd;
		Game *game = nullptr;
		GameType gameType = T_None;
	};
}
