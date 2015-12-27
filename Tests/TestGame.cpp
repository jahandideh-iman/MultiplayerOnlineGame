#include "CppUTest/TestHarness.h"
#include "Engine/Game.h"
#include "Engine/GameObject.h"
#include "Engine/Level.h"
#include "MockGameObject.h"


namespace mog
{

	class MockLevel : public Level
	{
	public:
		void addGameObject(GameObject *object)
		{
			Level::addGameObject(object);
		}
	};

	TEST_GROUP(Game)
	{

	};

	TEST(Game, hasTheAddedGameObject)
	{
		Game game;
		auto o1 = new GameObject();
		auto o2 = new GameObject();

		game.addGameObject(o1);
		game.addGameObject(o2);

		CHECK_TRUE(game.has(o1))
		CHECK_TRUE(game.has(o2))
	}

	TEST(Game, callsGameObjectUpdateInUpdate)
	{
		Game game;
		auto o1 = new MockGameObject();
		auto o2 = new MockGameObject();

		game.addGameObject(o1);
		game.addGameObject(o2);

		game.update(0.5);

		CHECK_TRUE(o1->isUpdateCalled);
		CHECK_TRUE(o2->isUpdateCalled);
	}

	TEST(Game, loadsLevelsComponents)
	{
		MockLevel level;
		Game game;
		auto o1 = new MockGameObject();
		auto o2 = new MockGameObject();

		level.addGameObject(o1);
		level.addGameObject(o2);

		game.loadLevel(&level);

		CHECK_TRUE(game.has(o1));
		CHECK_TRUE(game.has(o2));
	}
}