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
		void removeGameObjectAtEndOfUpdate(GameObject *object);

		void update(float dt = 0);

		//NOTE: For testing 
		bool has(const GameObject *object) const;
		//NOTE: For testing 
		const std::vector<GameObject *> &getGameObjects();

	protected:
		virtual void internalUpdate(float dt);

		Level *currentLevel = nullptr;
		std::vector<GameObject *> gameObjects;

		std::vector<GameObject *> toBeRemovedAtEndOfUpdate;

	};
}
