#pragma once
struct Point
{
    int x;
    int y;

    constexpr Point(const int x, const int y)
	    : x(x), y(y)
    {
	    
    }

    double DistanceTo(const Point& point) const;
};