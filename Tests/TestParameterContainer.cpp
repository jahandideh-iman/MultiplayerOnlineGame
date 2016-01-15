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

		container2.initialWithBuffer(&buffer);

		CHECK_EQUAL(container1, container2);
	}

	TEST(ParameterContainer, IsCorrectlyInitializedByWithNestedBuffer)
	{
		//TODO: clean this up
		ParameterContainer childContainer;
		ParameterContainer parentContainer;
		ParameterContainer resultContainer;
		Buffer buffer;

		childContainer.put("key1", "value1");
		childContainer.put("key2", "value2");

		childContainer.write(&buffer);
		char * data = buffer.getData();

		parentContainer.put("child", data);
		parentContainer.put("key3", "value3");

		buffer.clear();
		parentContainer.write(&buffer);

		resultContainer.initialWithBuffer(&buffer);

		CHECK_EQUAL("value3", resultContainer.get("key3"));
		CHECK_EQUAL(childContainer, ParameterContainer{ &Buffer{ resultContainer.get("child") } });

		delete []data;
	}
}