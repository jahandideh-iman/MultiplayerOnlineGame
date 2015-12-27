#include "CppUTest/TestHarness.h"
#include "Engine/GameObject.h"
#include "Engine/Component.h"



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
}