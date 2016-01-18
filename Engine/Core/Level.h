#pragma once

#include "Object.h"
#include "GameObject.h"
#include "Types.h"

namespace mog
{
	class Level : public Object
	{
	public:
		Level();
		virtual ~Level();

		std::vector<GameObject *> getGameObjects();

		virtual ID getID() const { return "EmptyLevel"; }

		virtual void initialGameObjects() {}
		void setIsloaded(bool isLoaded);

	protected:
		void addGameObject(GameObject *object);

	private:

		bool isLoaded = false;

		std::vector<GameObject *> objects;
	};
}

