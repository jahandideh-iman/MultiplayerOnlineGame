#pragma once

#include "Engine/Core/GameObject.h"
#include <functional>

namespace mog
{
	class MockGameObject : public GameObject
	{
	public:
		MockGameObject() {};
		MockGameObject(std::string key){ this->key = key; };

		void onAddedToGame(Game *game) override {
			GameObject::onAddedToGame(game);
			isOnAddedToGameCalled = true;
		}

		virtual void update(float dt) override {
			GameObject::update(dt);
			isUpdateCalled = true;
		}

		virtual void onRemovedFromGame(Game *game) override {
			GameObject::onRemovedFromGame(game);
			removeFromGameCallBack();
		}

		bool isUpdateCalled = false;
		bool isOnAddedToGameCalled = false;

		std::function<void()> removeFromGameCallBack;
		std::string key = "";
	};
}

