#include "pch.h"
#include "Zombie.h"

Zombie::Zombie(const int id, const int x, const int y, const int nextX, const int nextY)
	: Unit(id, x, y)
	, nextCoordinate(nextX, nextY)
{
}