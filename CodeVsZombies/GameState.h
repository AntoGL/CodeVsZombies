#pragma once
#include <map>
#include <set>
#include "Zombie.h"

class GameState
{
    std::map<int, Unit*> _humans;
    std::map<int, Unit*> _zombies;
    std::set<int> _notUpdatedUnitIds;
    Unit* Ash;

public:
    GameState();
    ~GameState();

    void ReadState(std::istream& in);

    double MinDistanceToZombie(const Point& p);

    Point GetTargetPoint();

private:
    void SetAllUnitsNotUpdated();
    void ReadHuman(std::istream& in);
    void ReadZombies(std::istream& in);
    void ReadUnit(std::map<int, Unit*>& units, std::istream& in, Unit* (*CreateNewUnit)());
    static int ReadId(std::istream& in);
    void ClearNotUpdatedUnits();
};
