#pragma once
#include "Point.h"

struct Vector
{
	double x;
	double y;
	double length;

public:
	Vector(const Point& start, const Point& end);

	void SetLength(double value);
};

Point operator+(const Point& point, const Vector& vector);
Point operator+(const Vector& vector, const Point& point);

Vector operator-(const Point& end, const Point& start);