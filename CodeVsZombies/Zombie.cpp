#include "pch.h"
#include "Zombie.h"

Zombie::Zombie()
	: Unit()
	, _nextX(0)
	, _nextY(0)
{
}

void Zombie::UpdateImpl(std::istream& in)
{
	Unit::UpdateImpl(in);

	in >> _nextX >> _nextY;
}