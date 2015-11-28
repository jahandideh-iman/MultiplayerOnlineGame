#pragma once
#include "network/NetworkGameObject.h"
#include "Engine/Macros.h"

namespace mog
{
	class Pawn :
		public network::NetworkGameObject
	{
	public:
		Pawn();
		~Pawn();

		AUTOID(Pawn, getNetworkID);

	private:
		int health = 0;
	};

}


