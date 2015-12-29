#include "CppUTest/TestHarness.h"
#include "Engine/Core/Buffer.h"
#include "NetworkBase.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Core/LevelDatabase.h"
#include "MockGameObject.h"

namespace mog
{
	namespace network
	{

		class MockLevel : public Level
		{
		public:
			virtual void initialGameObjects() override
			{
				addGameObject(new MockGameObject("Obj1"));
				addGameObject(new MockGameObject("Obj2"));
			}

			AUTOID(MockLevel,getID)

		};

		TEST_GROUP_BASE(LoadLevelMessage, NetworkBase)
		{
			bool gameHasLevelObjects(Game *game, Level *level)
			{
				for (auto gameO : clientGame->getGameObjects())
				{
					bool has = false;
					for (auto levelO : level->getGameObjects())
					{
						if (((MockGameObject*)levelO)->key == ((MockGameObject*)gameO)->key)
							has = true;
					}
					if (has == false)
						return false;
				}
				return true;
			}
		};

		TEST(LoadLevelMessage, LevelIsLoadedOnClient)
		{
			REGISTER_LEVEL(MockLevel);

			REGISTER_MESSAGE(LoadLevelMessage);

			MockLevel level;
			level.initialGameObjects();

			serverManager->sendMessage(LoadLevelMessage(level.getID()), network::InternetAddress(clientPort));
			clientManager->update();

			CHECK_TRUE(gameHasLevelObjects(clientGame, &level));

			LevelDatabase::clear();
		}
	}

}