#include "pch.h"
#include "GameState.h"

GameState::GameState()
	: Ash(new Unit())
{
}

GameState::~GameState()
{
	delete Ash;
	for (const auto& unit : _humans)
		delete unit.second;
}

void GameState::ReadState(std::istream& in)
{
	SetAllUnitsNotUpdated();

	Ash->Update(in);
	ReadHuman(in);
	ReadZombies(in);

	ClearNotUpdatedUnits();
}

void GameState::SetAllUnitsNotUpdated()
{
	for (const auto& unit : _humans)
		_notUpdatedUnitIds.insert(unit.first);
}

void GameState::ReadHuman(std::istream& in)
{
	ReadUnit(_humans, in, []() { return new Unit(); });
}

void GameState::ReadZombies(std::istream& in)
{
	ReadUnit(_zombies, in, []() { return static_cast<Unit*>(new Zombie()); });
}

void GameState::ReadUnit(std::map<int, Unit*>& units, std::istream& in, Unit* (*CreateNewUnit)())
{
	int count;
	in >> count; in.ignore();
	for (int i = 0; i < count; i++) {
		int id = ReadId(in);
		if (units.find(id) == units.end())
		{
			units[id] = CreateNewUnit();
		}

		_notUpdatedUnitIds.erase(id);
		units[id]->Update(in);
	}
}

int GameState::ReadId(std::istream& in)
{
	int id;
	in >> id;
	return id;
}

void GameState::ClearNotUpdatedUnits()
{
	for (auto id : _notUpdatedUnitIds)
	{
		delete _humans[id];
		_humans.erase(id);
	}
}

double GameState::MinDistanceToZombie(const Point& p)
{
	double minD = 10000000;
	for (const auto& z : _zombies)
	{
		double d = distanceD(p, z.second->GetCoord());
		if (d < minD)
		{
			minD = d;
		}
	}

	return minD;
}

Point GameState::GetTargetPoint()
{
	Point target(0, 0);
	double minD = 10000000;
	for (const auto& h : _humans)
	{
		double zd = MinDistanceToZombie(h.second->GetCoord());
		double d = distanceD(Ash->GetCoord(), h.second->GetCoord());
		if (minD == 10000000 || (d < minD && ((d / 1000) - 1) < (zd / 400)))
		{
			minD = d;
			target = h.second->GetCoord();
		}
	}

	return target;
}