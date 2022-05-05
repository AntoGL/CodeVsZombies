#pragma once
#include "Unit.h"

class Zombie final
	: public Unit
{
    int nextX;
    int nextY;

public:
    Zombie(int id, int x, int y, int nextX, int nextY);
};