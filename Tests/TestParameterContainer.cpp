#include "CppUTest/TestHarness.h"
#include "Engine/Core/ParameterContainer.h"
#include "Engine/Core/Buffer.h"

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

	TEST(ParameterContainer, IsCorrectlyInitializedByBuffer)
	{
		ParameterContainer container1;
		ParameterContainer container2;
		Buffer buffer;

		container1.put("key1", "value1");
		container1.put("key2", "value2");
		container1.write(&buffer);
		
		container2.initialWithBuffer(buffer);

		CHECK_EQUAL("value1", container2.get("key1"));
		CHECK_EQUAL("value2", container2.get("key2"));
	}
}