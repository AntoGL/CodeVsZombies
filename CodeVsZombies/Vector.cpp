#include "pch.h"
#include <cmath>
#include "Vector.h"

Vector::Vector(const double x,  const double y)
	: x(x), y(y)
{
}

Vector::Vector(const Point& start, const Point& end)
	: x(end.x - start.x)
	, y(end.y - start.y)
{
}

double Vector::GetLength() const
{
	return std::sqrt(x*x+y*y);
}

void Vector::SetLength(const double value)
{
	const double length = GetLength();
	if (length == 0)
		return;

	const double p = value / length;
	x *= p;
	y *= p;
}

double Vector::Angle(const Vector& vector) const
{
	return acos((x * vector.x + y * vector.y) / sqrt(GetLength() * vector.GetLength()));
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