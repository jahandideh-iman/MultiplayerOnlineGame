#pragma once
#include "Engine/Network/NetworkPawn.h"
#include "Engine/Core/Macros.h"
#include "Engine/Core/Types.h"

namespace mog
{

	class Pawn :
		public network::NetworkPawn
	{
	public:
		Pawn();
		~Pawn();

		AUTOID(Pawn, getNetworkID);

		void moveUp();

		void initialRegisteredMethods() override;


	private:
		Integer health = 100;
	};

}


