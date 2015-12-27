#pragma once

#include "Types.h"

namespace mog
{
	class Game;
	class GameObject;

	class Component
	{
	public:
		Component(ID id, const GameObject *owner);
		virtual ~Component();

		virtual void addSelfToGame(Game *g) {};

		virtual void update(float dt) {};

		ID getId() const;
		void setId(ID id);

		const GameObject *getOwner();

	protected:
		const GameObject *owner;

	private:
		ID id;
	};
}
