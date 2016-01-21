#pragma once

#include "Engine/Core/Component.h"
#include "Engine/Core/SerializablePoint.h"
#include <vector>

namespace mog
{
	class Game;

	class GameObject
	{
		friend class Game;
	public:
		GameObject();
		virtual ~GameObject();

		void addComponent(Component *c);
		std::vector<mog::Component *> getComponents();

		virtual void onRemovedFromGame(Game *game);

		virtual void update(float dt);

		virtual void updatePosition(float dt);
		virtual void updateRotation(float dt);

		void setPosition(Point pos);
		Point getPosition() const;

		void setRoation(Float r);
		Float getRoation() const;

		Component *findComponent(ID id);

		void setVelocity(Vector velocity);
		void setVelocityX(float x);
		void setVelocityY(float y);
		Vector getVelocity() const;

		Game *getOwner();

	protected:
		virtual void onAddedToGame(Game *game){};

	protected:
		SerializablePoint position;
		Float rotation = 0;
		Vector velocity;

	private:
		void addComponentsToGame(Game *game);
		
		//TODO: Find a better name
		void privateOnAddedToGame(Game *game);

	private:
		std::vector<mog::Component *> components;
		Game *owner = nullptr;



	};
}
