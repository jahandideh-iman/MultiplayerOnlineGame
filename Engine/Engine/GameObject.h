#pragma once

#include "Component.h"
#include <vector>

namespace mog
{
	class Game;

	struct Point
	{
		Point(int x, int y)
		{
			this->x = x; this->y = y;
		}
		Point(){}
		int x = 0;
		int y = 0;
	};
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void addComponent(Component *c);
		std::vector<mog::Component *> getComponents();

		virtual void onAddedToGame(Game *game);

		virtual void update(float dt);

		void setPosition(Point pos);
		Point getPosition() const;

		Component *findComponent(ID id);

	protected:
		virtual void addComponentsToGame(Game *game);

	private:
		std::vector<mog::Component *> components;

		Point position;

	};
}
