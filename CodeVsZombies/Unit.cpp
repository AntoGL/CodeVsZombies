#include "pch.h"
#include "Unit.h"

Unit::Unit(const int x, const int y) : x(x), y(y)
{}

Unit::Unit() : x(0), y(0)
{
}

Point Unit::GetCoord() const
{
	return {x, y};
}

void Unit::Update(std::istream& in)
{
	UpdateImpl(in);
	in.ignore();
}

void Unit::UpdateImpl(std::istream& in)
{
	in >> x >> y;
}