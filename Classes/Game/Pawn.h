#pragma once
#include "network/NetworkGameObject.h"
#include "Engine/Macros.h"
#include "Engine/Types.h"

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
		Integer health = 100;
	};

}


