#include "CppUTest/TestHarness.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Component.h"



namespace mog
{

	TEST_GROUP(GameObject)
	{

	};

	TEST(GameObject, hasTheAddedComponents)
	{
		GameObject gameObject;

		auto component1 = new Component("comp1", &gameObject);
		auto component2 = new Component("comp2", &gameObject);

		gameObject.addComponent(component1);
		gameObject.addComponent(component2);

		CHECK_EQUAL(component1, gameObject.findComponent("comp1"));
		CHECK_EQUAL(component2, gameObject.findComponent("comp2"));
	}

	TEST(GameObject, PositionIsCorrectInRegardToVelocity)
	{
		GameObject gameObject;
		gameObject.setPosition(Point(0, 0));
		gameObject.setVelocity(Vector(1, 2));

		gameObject.update(2);

		CHECK_EQUAL(2, gameObject.getPosition().getX());
		CHECK_EQUAL(4, gameObject.getPosition().getY());
	}
}