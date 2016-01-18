#pragma once

#include "Engine/Core/Level.h"
#include "Engine/Core/Macros.h"

namespace mog
{
	class GameLevel :
		public Level
	{
	public:
		GameLevel();
		~GameLevel();

		virtual void initialGameObjects() override;

		AUTOID(GameLevel, getID)
	};
}