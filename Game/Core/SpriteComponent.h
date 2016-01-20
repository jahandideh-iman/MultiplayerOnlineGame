#pragma once

#include "Engine/Core/Component.h"
#include "cocos2d.h"
#include <functional>
#include <vector>

namespace mog
{
	class CCGame;
	class SpriteComponent : public Component
	{
		typedef std::function<void()> Callback;
	public:
		~SpriteComponent();

		SpriteComponent(ID id, const GameObject *owner, const std::string &fileName);

		virtual void addSelfToGame(Game *g);

		virtual void update(float dt) override;

		void addOutOfViewCallback(Callback callback);

	private:
		cocos2d::Sprite *sprite = nullptr;

		CCGame *ccGame = nullptr;

		std::vector < Callback > outOfViewCallbacks;
	};
}
