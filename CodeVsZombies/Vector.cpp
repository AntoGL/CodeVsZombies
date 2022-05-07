#include "pch.h"
#include "Vector.h"

Vector::Vector(const Point& start, const Point& end)
{
	x = end.x - start.x;
	y = end.y - start.y;
	length = start.DistanceTo(end);
}

void Vector::SetLength(const double value)
{
	const double p = value / length;
	length = value;
	x *= p;
	y *= p;
}

Point operator+(const Point& point, const Vector& vector)
{
	const int x = static_cast<int>(point.x + vector.x);
	const int y = static_cast<int>(point.y + vector.y);

	return { x, y };
}

Point operator+(const Vector& vector, const Point& point)
{
	return point + vector;
}

Vector operator-(const Point& end, const Point& start)
{
	return { start, end };
}