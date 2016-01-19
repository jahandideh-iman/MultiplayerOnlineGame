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

		void update(float dt) override;

		void moveUpPressed();
		void moveUpReleased();

		void moveDownPressed();
		void moveDownReleased();

		void moveLeftPressed();
		void moveLeftReleased();

		void moveRightPressed();
		void moveRightReleased();

		void shoot();

		void initialRegisteredMethods() override;

	private:
		Integer health = 100;

		Integer speed = 50;
	};

}


