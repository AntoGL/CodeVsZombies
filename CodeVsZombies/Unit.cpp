#include "pch.h"
#include "Unit.h"

Unit::Unit()
	: id(-1), x(0), y(0)
{
}

Unit::Unit(const int x, const int y)
	: id(-1), x(x), y(y)
{
}

Unit::Unit(const int id, const int x, const int y)
	: id(id), x(x), y(y)
{
}

int Unit::GetId() const
{
	return id;
}