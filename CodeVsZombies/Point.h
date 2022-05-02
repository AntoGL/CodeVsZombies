#pragma once
#include <cmath>

struct Point
{
    int x;
    int y;

    constexpr Point(int x, int y);
};

inline double distanceD(const Point& a, const Point& b)
{
    const int dx = a.x - b.x;
    const int dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}