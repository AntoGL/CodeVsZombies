#pragma once
#include "Point.h"

struct Vector
{
	double x;
	double y;

public:
	CVZ_EXPORT Vector(double x, double y);
	CVZ_EXPORT Vector(const Point& start, const Point& end);

	CVZ_EXPORT inline double GetLength() const;
	CVZ_EXPORT void SetLength(double value);
};

CVZ_EXPORT Point operator+(const Point& point, const Vector& vector);
CVZ_EXPORT Point operator+(const Vector& vector, const Point& point);

CVZ_EXPORT Vector operator-(const Point& end, const Point& start);