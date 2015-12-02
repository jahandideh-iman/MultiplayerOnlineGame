#pragma once

#include "cocos2d.h"
#include "Level.h"

namespace mog
{
	class GameObject;
	class Game :
		public cocos2d::Layer
	{
	public:
		Game();
		~Game();

		void loadLevel(Level *level);

		void addGameObject(GameObject *o);

		virtual void update(float dt) override;

	protected:
		Level *currentLevel = nullptr;
		std::vector<GameObject *> gameObjects;
	};
}
