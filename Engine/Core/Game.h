#pragma once

#include "Level.h"


namespace mog
{
	class GameObject;
	class Game
	{
	public:
		Game();
		virtual ~Game();

		void loadLevel(Level *level);

		void addGameObject(GameObject *object);
		void removeGameObject(GameObject *object);

		virtual void update(float dt);

		//NOTE: For testing 
		bool has(const GameObject *object) const;
		//NOTE: For testing 
		const std::vector<GameObject *> &getGameObjects();

	protected:
		Level *currentLevel = nullptr;
		std::vector<GameObject *> gameObjects;
	};
}
