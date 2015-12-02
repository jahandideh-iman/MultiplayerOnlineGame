
#include "Game.h"

namespace mog
{
	enum GameType {T_None, T_Server, T_Client};
	struct GlobalData
	{
		static Game *game;
		static GameType gameType;
	private:
		GlobalData(){};
	};
}
