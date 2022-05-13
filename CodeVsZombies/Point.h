#pragma once
#include "export.h"

CVZ_EXPORT struct Point
{
    int x;
    int y;

    CVZ_EXPORT constexpr Point(const int x, const int y)
	    : x(x), y(y)
    {
	    
    }

    CVZ_EXPORT double DistanceTo(const Point& point) const;
};