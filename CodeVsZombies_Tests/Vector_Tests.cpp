#include "pch.h"
#include "Vector.h"

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
	OperatorSum_Integer,
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

INSTANTIATE_TEST_CASE_P(
	OperatorSum_Real,
	Vector_OperatorSumPointVector_Fixture,
	Values(
		make_tuple(Point(0, 0), Vector(0.1, 0), Point(0, 0)),
		make_tuple(Point(0, 0), Vector(0, 0.1), Point(0, 0)),
		make_tuple(Point(0, 0), Vector(0.1, 0.1), Point(0, 0)),
		make_tuple(Point(0, 0), Vector(0, 0.9), Point(0, 0)),
		make_tuple(Point(0, 0), Vector(0.9, 0), Point(0, 0)),
		make_tuple(Point(0, 0), Vector(0.9, 0.9), Point(0, 0))
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

struct Vector_SetLength_Fixture : TestWithParam<tuple<Vector, double, Vector>>
{
	
};

INSTANTIATE_TEST_CASE_P(
	SetLength,
	Vector_SetLength_Fixture,
	Values(
		make_tuple(Vector(1, 0), 2, Vector(2, 0))
		, make_tuple(Vector(0, 1), 2, Vector(0, 2))
		, make_tuple(Vector(2, 0), 1, Vector(1, 0))
		, make_tuple(Vector(0, 2), 1, Vector(0, 1))
		, make_tuple(Vector(0, 2), 0, Vector(0, 0))
	)
);

INSTANTIATE_TEST_CASE_P(
	ReturnZeroVector,
	Vector_SetLength_Fixture,
	Combine(
		Values(
			Vector(0, 0)
			, Vector(0, 1)
			, Vector(1, 0)
			, Vector(1, 1)
			, Vector(3, 2)
			, Vector(8, -3)
			, Vector(-7, 4)
			, Vector(-97, -44)
		)
		, Values(0)
		, Values(Vector(0, 0)))
);

TEST_P(Vector_SetLength_Fixture, Case)
{
	auto [vector, length, expectedVector] = GetParam();

	vector.SetLength(length);

	ASSERT_EQ(expectedVector.GetLength(), vector.GetLength());
	ASSERT_EQ(expectedVector.x, vector.x);
	ASSERT_EQ(expectedVector.y, vector.y);
}

struct Vector_Angle_Tests : TestWithParam<tuple<Vector, Vector, double>>
{
	
};

#define Angle45 std::sqrt(2) / 2

INSTANTIATE_TEST_CASE_P(
	SimpleTests,
	Vector_Angle_Tests,
	Values(
		make_tuple(Vector(1, 0), Vector(1, 0), std::acos(1)),	// 0
		make_tuple(Vector(1, 0), Vector(Angle45, Angle45), std::acos(std::sqrt(2) / 2)),	// 45
		make_tuple(Vector(1, 0), Vector(0, 1), std::acos(0)),	// 90
		make_tuple(Vector(1, 0), Vector(-1, 0), std::acos(-1)),	// 180
		make_tuple(Vector(1, 0), Vector(0, -1), std::acos(0)),	// -90
		make_tuple(Vector(1, 0), Vector(Angle45, -Angle45), std::acos(std::sqrt(2) / 2))	//-45
	)
);

TEST_P(Vector_Angle_Tests, Case)
{
	auto [vector1, vector2, expectedAngle] = GetParam();

	const double angle = vector1.Angle(vector2);

	ASSERT_EQ(expectedAngle, angle);
}