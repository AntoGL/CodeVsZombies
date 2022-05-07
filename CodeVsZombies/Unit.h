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
    void SetCoordinate(const Point& point);
    Point& GetCoordinate();
    const Point& GetCoordinate() const;

    double DistanceTo(const Point& point) const;
};
