#pragma once

#include "Component.h"
#include "cocos2d.h"

namespace mog
{
	class SpriteComponent : public Component
	{
	public:
		~SpriteComponent();

		SpriteComponent(const std::string &fileName);

		virtual void addSelfToGame(Game *g);

	private:
		cocos2d::Sprite *sprite = nullptr;
	};
}
