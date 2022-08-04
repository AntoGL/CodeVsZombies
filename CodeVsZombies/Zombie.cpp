#include "pch.h"
#include "Zombie.h"

Zombie::Zombie(const int id, const int targetId, const int x, const int y, const int nextX, const int nextY)
	: Unit(id, x, y)
	, nextCoordinate(nextX, nextY)
	, targetId(targetId)
{
	
}

Zombie::Zombie(const int id, const int x, const int y, const int nextX, const int nextY)
	: Unit(id, x, y)
	, nextCoordinate(nextX, nextY)
	, targetId(-1)
{
}

void Zombie::SetNextCoordinate(const Point& point)
{
	nextCoordinate = point;
}

Point& Zombie::GetNextCoordinate()
{
	return nextCoordinate;
}

const Point& Zombie::GetNextCoordinate() const
{
	return nextCoordinate;
}

void Zombie::SetTargetId(const int id)
{
	targetId = id;
}

int Zombie::GetTargetId() const
{
	return targetId;
}