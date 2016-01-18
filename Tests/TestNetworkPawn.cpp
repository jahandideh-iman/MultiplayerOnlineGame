#include "CppUTest/TestHarness.h"

#include "Engine/Network/NetworkPawn.h"


namespace mog
{
	namespace network
	{
		TEST_GROUP(NetworkPawn)
		{

		};

		TEST(NetworkPawn, PositionIsCorrectInRegardToVelocity)
		{
			NetworkPawn pawn;
			pawn.setPosition(Point(0, 0));
			pawn.setVelocity(Vector(1, 2));

			pawn.update(2);

			CHECK_EQUAL(2, pawn.getPosition().x);
			CHECK_EQUAL(4, pawn.getPosition().y);
		}
	}
}