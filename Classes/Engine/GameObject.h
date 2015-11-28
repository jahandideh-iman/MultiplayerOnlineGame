#pragma once

#include "Component.h"
#include <vector>
#include "cocos2d.h"

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

		virtual void addSelfToGame(Game *game);

		void setPosition(Point pos);
		Point getPosition();

	private:
		std::vector<mog::Component *> components;

	};
}
