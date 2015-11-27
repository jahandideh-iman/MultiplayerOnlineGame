#pragma once

#include "cocos2d.h"
#include "Level.h"

namespace mog
{
	class Game :
		public cocos2d::Layer
	{
	public:
		Game();
		~Game();

		void LoadLevel(Level *level) ;

	private:
		void addGameObject(GameObject *object);

	protected:
		Level *currentLevel = nullptr;
	};
}
