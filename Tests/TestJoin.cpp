#include "CppUTest/TestHarness.h"
#include "Engine/Buffer.h"
#include "NetworkBase.h"
#include "Network/Messages/Join.h"

namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(Join,NetworkBase)
		{
		};

		TEST(Join, PlayerInfoIsAddedToServer)
		{
			REGISTER_MESSAGE(Join);
		}
	}
	
}