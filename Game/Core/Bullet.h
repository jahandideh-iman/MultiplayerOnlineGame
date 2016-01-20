#pragma once

#include "Engine/Network/NetworkGameObject.h"

#include "Engine/Core/Types.h"

namespace mog
{
	class Pawn;
	class Bullet : public network::NetworkGameObject
	{
	public:
		Bullet();
		Bullet(Pawn *shooter,Float r, Point p);
		~Bullet();

		AUTOID(Bullet, getNetworkID);
	private:
		Pawn *shooter = nullptr;
		int speed = 50;
	};
}

