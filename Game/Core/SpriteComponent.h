#pragma once

#include "Engine/Core/Component.h"
#include "cocos2d.h"

namespace mog
{
	class SpriteComponent : public Component
	{
	public:
		~SpriteComponent();

		SpriteComponent(ID id, const GameObject *owner, const std::string &fileName);

		virtual void addSelfToGame(Game *g);

		virtual void update(float dt) override;

	private:
		cocos2d::Sprite *sprite = nullptr;
	};
}
