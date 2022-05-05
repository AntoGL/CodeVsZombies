#pragma once
#include "Point.h"

class Unit
{
    int id;
    Point coordinate;

public:
    Unit();
    Unit(int x, int y);
    Unit(int id, int x, int y);
    virtual ~Unit() = default;

    operator const Point& () const;

    int GetId() const;

    double DistanceTo(const Point& point) const;
};
