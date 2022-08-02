#pragma once
#include "export.h"
#include "Unit.h"

CVZ_EXPORT class Zombie final
	: public Unit
{
    Point nextCoordinate;

public:
    CVZ_EXPORT Zombie(int id, int x, int y, int nextX, int nextY);

    void SetNextCoordinate(const Point& point);
    Point& GetNextCoordinate();
    const Point& GetNextCoordinate() const;
};