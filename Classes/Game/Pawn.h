#pragma once
#include "Engine/GameObject.h"
#include "network/NetworkObject.h"
#include "Engine/Macros.h"

namespace mog
{
	class Pawn :
		public GameObject, public network::NetworkObject
	{
	public:
		Pawn();
		~Pawn();

		AUTOID(Pawn, getNetworkID);

	private:
		int health = 0;
	};

}


