#pragma once

#include "Engine/Types.h"

namespace mog
{
	class Game;
	class GameObject;

	class Component
	{
	public:
		Component(ID id, const GameObject *owner);
		~Component();

		virtual void addSelfToGame(Game *g) = 0;

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
