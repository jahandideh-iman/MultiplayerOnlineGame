#include "CppUTest/TestHarness.h"
#include "Engine/Core/Buffer.h"
#include "NetworkBase.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Core/LevelDatabase.h"

#include "MockLevel.h"

namespace mog
{
	namespace network
	{

		TEST_GROUP_BASE(LoadLevelMessage, NetworkBase)
		{
		};

		TEST(LoadLevelMessage, LevelIsLoadedOnClient)
		{
			REGISTER_LEVEL(MockLevel);
			REGISTER_MESSAGE(LoadLevelMessage);

			MockLevel level;
			level.initialGameObjects();

			serverManager->sendMessage(LoadLevelMessage(&level), clientAddress1);
			clientManager1->update();

			CHECK_TRUE(gameHasLevelObjects(clientGame1, &level));

			LevelDatabase::clear();
		}
	}

}