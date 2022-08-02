#include "pch.h"
#include "Unit.h"

Unit::Unit()
	: id(-1), coordinate(0, 0)
{
}

Unit::Unit(const int x, const int y)
	: id(-1), coordinate(x, y)
{
}

Unit::Unit(const int id, const int x, const int y)
	: id(id), coordinate(x, y)
{
}

Unit::operator const Point&() const
{
	return GetCoordinate();
}

int Unit::GetId() const
{
	return id;
}
void Unit::SetCoordinate(const Point& point)
{
	coordinate = point;
}

Point& Unit::GetCoordinate()
{
	return coordinate;
}

const Point& Unit::GetCoordinate() const
{
	return coordinate;
}

double Unit::DistanceTo(const Point& point) const
{
	return coordinate.DistanceTo(point);
}