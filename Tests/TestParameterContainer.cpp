#include "CppUTest/TestHarness.h"
#include "Engine/Core/ParameterContainer.h"
#include "Engine/Core/Buffer.h"

SimpleString StringFrom(const mog::ParameterContainer& o)
{
	return "ParameterContainer";
}
namespace mog
{
	TEST_GROUP(ParameterContainer)
	{
	};

	TEST(ParameterContainer, HasTheEnteredPair)
	{
		ParameterContainer container;

		container.put("key", "value");

		CHECK_EQUAL("value", container.get("key"));
	}

	TEST(ParameterContainer, CanHaveMultiplePairs)
	{
		ParameterContainer container;

		container.put("key1", "value1");
		container.put("key2", "value2");

		CHECK_EQUAL("value1", container.get("key1"));
		CHECK_EQUAL("value2", container.get("key2"));
	}

	TEST(ParameterContainer, ContainersAreNotEqualIfHaveDifferentNumberOfPairs)
	{
		ParameterContainer container1;
		ParameterContainer container2;

		container1.put("key1", "value1");
		container1.put("key2", "value2");

		container2.put("key1", "value1");

		CHECK_TRUE(container1 != container2);
	}

	TEST(ParameterContainer, ContainersAreNotEqualIfHaveDifferentPairs)
	{
		ParameterContainer container1;
		ParameterContainer container2;

		container1.put("key1", "value1");

		container2.put("key1", "differentValue1");

		CHECK_TRUE(container1 != container2);
	}

	TEST(ParameterContainer, ContainersAreEqualIfHaveSamePairs)
	{
		ParameterContainer container1;
		ParameterContainer container2;

		container1.put("key1", "value1");
		container1.put("key2", "value2");

		container2.put("key1", "value1");
		container2.put("key2", "value2");

		CHECK_EQUAL(container1 ,container2);
	}

	TEST(ParameterContainer, IsCorrectlyInitializedByBuffer)
	{
		ParameterContainer container1;
		ParameterContainer container2;
		Buffer buffer;

		container1.put("key1", "value1");
		container1.put("key2", "value2");
		container1.write(&buffer);

		container2.initialWithBuffer(buffer);

		CHECK_EQUAL(container1, container2);
	}

	//TEST(ParameterContainer, IsCorrectlyInitializedByWithNestedBuffer)
	//{
	//	ParameterContainer container1;
	//	ParameterContainer container2;
	//	ParameterContainer container3;
	//	Buffer buffer;

	//	container1.put("key1", "value1");
	//	container1.put("key2", "value2");

	//	container1.write(&buffer);
	//	container2.put("containerKey", buffer.getData());
	//	container2.put("key4", "value3");

	//	buffer.clear();
	//	container2.write(&buffer);

	//	container3.initialWithBuffer(buffer);


	//	CHECK_EQUAL("value3", container3.get("key4"));
	//	CHECK_EQUAL("value2", container3.get("key2"));
	//	CHECK_EQUAL(container1, container3.get("key2"));
	//}
}