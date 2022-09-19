//#include "../pch.h"
#include "Point.h"
#include "gtest/gtest.h"

using namespace testing;
using namespace std;

void DistanceTo_TestCase(const Point& p1, const Point& p2, const double expectedDistance)
{
	const double distance = p1.DistanceTo(p2);

	ASSERT_DOUBLE_EQ(expectedDistance, distance);
}

TEST(Point_Tests, DistanceTo_IdenticalPoints_Return0)
{
	const Point point(0, 0);

	DistanceTo_TestCase(point, point, 0);
}

TEST(Point_Tests, DistanceTo_DifferentPoints_Return17_029)
{
	const Point point1(-2, -3);
	const Point point2(9, 10);

	DistanceTo_TestCase(point1, point2, 17.029386365926403);
}