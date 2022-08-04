#pragma once
#include "export.h"
#include "Unit.h"

CVZ_EXPORT class Zombie final
	: public Unit
{
    Point nextCoordinate;
    int targetId;

public:
    CVZ_EXPORT Zombie(int id, int targetId, int x, int y, int nextX, int nextY);
    CVZ_EXPORT Zombie(int id, int x, int y, int nextX, int nextY);

    void SetNextCoordinate(const Point& point);
    Point& GetNextCoordinate();
    const Point& GetNextCoordinate() const;

    void SetTargetId(int id);
    int GetTargetId() const;
};