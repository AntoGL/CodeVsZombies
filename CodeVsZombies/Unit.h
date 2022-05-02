#pragma once
#include <istream>
#include "Point.h"

class Unit
{
    int x;
    int y;

public:
    Unit();
    Unit(int x, int y);
    virtual ~Unit() = default;

    Point GetCoord() const;

    void Update(std::istream& in);

protected:
    virtual void UpdateImpl(std::istream& in);
};
