#include "CppUTest/TestHarness.h"
#include "Engine/Game.h"
#include "Engine/GameObject.h"
#include "Engine/GlobalData.h"

namespace mog
{
	class MockGameObject : public GameObject
	{
	public:
		virtual void update(float dt) override {
			isUpdateCalled = true;
		}

		bool isUpdateCalled = false;
	};

	TEST_GROUP(Game)
	{

		void teardown()
		{
			GlobalData::get()->clear();
		}
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

	TEST(Game, IsSetInGlobalDataAfterCreation)
	{
		Game game;

		CHECK_EQUAL(&game, GLOBAL_DATA()->getGame());
	}
}