#pragma once
#include "Engine/Network/NetworkGameObject.h"
#include "Engine/Core/Macros.h"
#include "Engine/Core/Types.h"

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


