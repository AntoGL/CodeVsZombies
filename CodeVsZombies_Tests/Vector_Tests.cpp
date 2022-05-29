#include "pch.h"
#include "../CodeVsZombies/Vector.h"

//https://www.sandordargo.com/blog/2019/04/24/parameterized-testing-with-gtest#parameterized-tests-what-are-they-parameterizedtests

using namespace std;
using namespace testing;

struct Vector_ConstructorDoubleDouble_Fixture : TestWithParam<tuple<double, double>>
{
	
};

const auto VectorCoordinates = Values(0, 1, -1, 100, 1000, INT32_MAX, INT32_MIN, 0.1, 0.5, 11.3);
INSTANTIATE_TEST_CASE_P(
	Different_Coordinates,
	Vector_ConstructorDoubleDouble_Fixture,
	Combine(VectorCoordinates, VectorCoordinates));

TEST_P(Vector_ConstructorDoubleDouble_Fixture, CaseName)
{
	auto [x, y] = GetParam();
	const Vector vector(x, y);

	ASSERT_EQ(x, vector.x);
	ASSERT_EQ(y, vector.y);
}

struct Vector_OperatorSumPointVector_Fixture : TestWithParam<tuple<Point, Vector, Point>>
{
	
};

INSTANTIATE_TEST_CASE_P(
	OperatorSum,
	Vector_OperatorSumPointVector_Fixture,
	Values(
		make_tuple(Point(0, 0), Vector(0, 0), Point(0, 0)),
		make_tuple(Point(0, 0), Vector(1, 0), Point(1, 0)),
		make_tuple(Point(0, 0), Vector(0, 1), Point(0, 1)),
		make_tuple(Point(0, 0), Vector(1, 1), Point(1, 1)),
		make_tuple(Point(2, 3), Vector(1, 1), Point(3, 4)),
		make_tuple(Point(2, 3), Vector(1, 4), Point(3, 7)),
		make_tuple(Point(2, 3), Vector(4, 1), Point(6, 4)),
		make_tuple(Point(2, 3), Vector(4, 4), Point(6, 7))
	)
);

TEST_P(Vector_OperatorSumPointVector_Fixture, PointVector)
{
	auto [point, vector, expectedResult] = GetParam();

	const Point result = point + vector;

	ASSERT_EQ(0, expectedResult.DistanceTo(result));
}

TEST_P(Vector_OperatorSumPointVector_Fixture, VectorPoint)
{
	auto [point, vector, expectedResult] = GetParam();

	const Point result = vector + point;

	ASSERT_EQ(0, expectedResult.DistanceTo(result));
}

struct Vector_OperatorDifPointPoint_Fixture : TestWithParam<tuple<Point, Point, Vector>>
{

};

INSTANTIATE_TEST_CASE_P(
	OperatorDiff,
	Vector_OperatorDifPointPoint_Fixture,
	Values(
		make_tuple(Point(0, 0), Point(0, 0), Vector(0, 0)),
		make_tuple(Point(0, 0), Point(1, 0), Vector(1, 0)),
		make_tuple(Point(0, 0), Point(0, 1), Vector(0, 1)),
		make_tuple(Point(0, 0), Point(1, 1), Vector(1, 1)),
		make_tuple(Point(2, 3), Point(1, 1), Vector(-1, -2)),
		make_tuple(Point(2, 3), Point(1, 4), Vector(-1, 1)),
		make_tuple(Point(2, 3), Point(4, 1), Vector(2, -2)),
		make_tuple(Point(2, 3), Point(4, 4), Vector(2, 1))
	)
);

TEST_P(Vector_OperatorDifPointPoint_Fixture, PointPoint)
{
	auto [start, end, expectedResult] = GetParam();

	const Vector result = end - start;

	ASSERT_EQ(expectedResult.x, result.x);
	ASSERT_EQ(expectedResult.y, result.y);
}