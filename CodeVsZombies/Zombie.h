#pragma once
#include "Unit.h"

class Zombie final
	: public Unit
{
    Point nextCoordinate;

public:
    Zombie(int id, int x, int y, int nextX, int nextY);
};