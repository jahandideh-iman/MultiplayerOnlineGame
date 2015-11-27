#pragma once
#include "Engine/GameObject.h"
#include "Network/GameObjectRepresenter.h"
#include "cocos2d.h"

namespace mog
{
	class Pawn :
		public GameObject
	{
	public:
		Pawn();
		~Pawn();

	private:
		int health = 0;
	};

}

