#pragma once
#include "Unit.h"

class Zombie final
	: public Unit
{
    Point nextCoordinate;

public:
    Zombie(int id, int x, int y, int nextX, int nextY);

    void SetNextCoordinate(const Point& point);
    Point& GetNextCoordinate();
    const Point& GetNextCoordinate() const;
};