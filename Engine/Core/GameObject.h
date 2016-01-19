#pragma once

#include "Engine/Core/Component.h"
#include "Engine/Core/SerializablePoint.h"
#include <vector>

namespace mog
{
	class Game;

	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void addComponent(Component *c);
		std::vector<mog::Component *> getComponents();

		virtual void onAddedToGame(Game *game);
		virtual void onRemovedFromGame(Game *game);

		virtual void update(float dt);

		void setPosition(Point pos);
		Point getPosition() const;

		void setRoation(Float r);
		Float getRoation() const;

		Component *findComponent(ID id);

		Game *getOwner();

	protected:
		//TODO: Find out why this method is virtual
		virtual void addComponentsToGame(Game *game);

		SerializablePoint position;
		Float rotation = 0;

	private:
		std::vector<mog::Component *> components;
		Game *owner = nullptr;

	};
}
