#pragma once
#include "Engine/Core/Component.h"
#include "cocos2d.h"

#include <map>
#include <functional>

namespace mog
{
	class InputComponent : public Component, public cocos2d::Node
	{
		typedef std::function<void()> Action;
	public:
		~InputComponent();

		InputComponent(ID id, const GameObject *owner);

		virtual void addSelfToGame(Game *g);

		void addOnPressAction(cocos2d::EventKeyboard::KeyCode key, Action action);
		void addOnReleaseAction(cocos2d::EventKeyboard::KeyCode key, Action action);

	private:
		std::map<cocos2d::EventKeyboard::KeyCode, Action> onPressActions;
		std::map<cocos2d::EventKeyboard::KeyCode, Action> onReleaseActions;
	};
}

