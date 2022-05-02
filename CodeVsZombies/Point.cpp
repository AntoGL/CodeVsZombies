#include "pch.h"
#include "Point.h"

constexpr Point::Point(const int x, const int y) : x(x), y(y)
{
}

constexpr double Point::DistanceTo(const Point& point) const
{
    const int dx = x - point.x;
    const int dy = y - point.y;
    return std::sqrt(dx * dx + dy * dy);
}