#pragma once

#include "Engine/Core/GameObject.h"

namespace mog
{
	class MockGameObject : public GameObject
	{
	public:
		MockGameObject() {};
		MockGameObject(std::string key){ this->key = key; };

		virtual void update(float dt) override {
			isUpdateCalled = true;
		}

		bool isUpdateCalled = false;
		std::string key = "";
	};
}

