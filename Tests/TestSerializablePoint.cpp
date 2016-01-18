#include "CppUTest/TestHarness.h"


#include "Engine/Core/SerializablePoint.h"

namespace mog
{
	TEST_GROUP(SerializablePoint)
	{

	};

	TEST(SerializablePoint, CorrectlyConstructs)
	{
		SerializablePoint point(1, 2);

		CHECK_EQUAL(1, point.x);
		CHECK_EQUAL(2, point.y);
	}

	TEST(SerializablePoint, CorrectlyReadsAndWirtes)
	{
		SerializablePoint point1(1, 2);
		SerializablePoint point2(2, 3);

		Buffer buffer;
		point1.write(&buffer);
		point2.read(&buffer);

		CHECK_EQUAL(point1.x, point2.x);
		CHECK_EQUAL(point1.y, point2.y);

	}
}