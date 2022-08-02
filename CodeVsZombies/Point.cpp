#include "pch.h"
#include <cmath>
#include "Point.h"

double Point::DistanceTo(const Point& point) const
{
    const int dx = x - point.x;
    const int dy = y - point.y;
    return std::sqrt(dx * dx + dy * dy);
}