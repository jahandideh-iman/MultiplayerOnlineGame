#pragma once

#include "Engine/GameObject.h"
namespace mog
{
	class Level
	{
	public:
		Level();
		~Level();

		void addGameObject(GameObject *object);
		std::vector<GameObject *> getGameObjects();

	private:
		std::vector<GameObject *> objects;
	};
}

