#pragma once
#include "Point.h"

class Unit
{
    int id;
    Point coordinate;

public:
    Unit();
    Unit(int x, int y);
    CVZ_EXPORT Unit(int id, int x, int y);
    virtual ~Unit() = default;

    CVZ_EXPORT operator const Point& () const;

    int GetId() const;
    void SetCoordinate(const Point& point);
    CVZ_EXPORT Point& GetCoordinate();
    CVZ_EXPORT const Point& GetCoordinate() const;

    CVZ_EXPORT double DistanceTo(const Point& point) const;
};
