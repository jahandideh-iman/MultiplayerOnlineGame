#include "CppUTest/TestHarness.h"
#include "Engine/Core/ReplicablePoint.h"
#include "Engine/Core/Buffer.h"

namespace mog
{
	TEST_GROUP(ReplicablePoint)
	{

	};

	TEST(ReplicablePoint, CorrectlyConstructs)
	{
		ReplicablePoint point(1, 2);

		CHECK_EQUAL(1, point.getX());
		CHECK_EQUAL(2, point.getY());
	}

	TEST(ReplicablePoint, CorrectlyReadsAndWirtes)
	{
		ReplicablePoint point1(1, 2);
		ReplicablePoint point2(2, 3);

		Buffer buffer;
		point1.write(&buffer);
		point2.read(&buffer);

		CHECK_EQUAL(point1.getX(), point2.getX());
		CHECK_EQUAL(point1.getY(), point2.getY());
	}

	TEST(ReplicablePoint, ChangingStateSetsDirtyFlag)
	{
		ReplicablePoint point(1, 2);

		point.setDirty(false);
		point.setX(3);

		CHECK_TRUE(point.isDirty());

		point.setDirty(false);
		point.setY(3);

		CHECK_TRUE(point.isDirty());
	}

	TEST(ReplicablePoint, NotChangingStateDoesNotSetsDirtyFlag)
	{
		ReplicablePoint point(1, 2);

		point.setDirty(false);
		point.setX(1);

		CHECK_FALSE(point.isDirty());

		point.setDirty(false);
		point.setY(2);

		CHECK_FALSE(point.isDirty());
	}
}