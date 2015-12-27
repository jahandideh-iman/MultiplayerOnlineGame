#pragma once

#include "Engine/Level.h"
#include "Engine/Macros.h"

namespace mog
{
	class GameLevel :
		public Level
	{
	public:
		GameLevel();
		~GameLevel();

		AUTOID(GameLevel, getID)
	};
}