#pragma once

#include "Component.h"
#include <vector>

namespace mog
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void addComponent(Component *c);
		std::vector<mog::Component *> getComponents();

	private:
		std::vector<mog::Component *> components;
	};
}
