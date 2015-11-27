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

		virtual char *getName() const = 0;

	private:
		std::vector<GameObject *> objects;
	};
}

