#include "pch.h"
#include <iostream>
#include <map>
#include <set>
#include "Point.h"
#include "Unit.h"

using namespace std;

class Zombie
    : public Unit
{
    int _nextX;
    int _nextY;

protected:
    void UpdateImpl(istream& in) override
    {
        Unit::UpdateImpl(in);

        in >> _nextX >> _nextY;
    }

public:
    Zombie() : Unit()
    {

    }
};

class Game
{
    map<int, Unit*> _humans;
    map<int, Unit*> _zombies;
    set<int> _notUpdatedUnitIds;
    Unit* Ash;

public:
    Game()
        : Ash(new Unit())
    {
    }

    ~Game()
    {
        delete Ash;
        for (const auto& unit : _humans)
            delete unit.second;
    }

    void ReadState(istream& in)
    {
        SetAllUnitsNotUpdated();

        Ash->Update(in);
        ReadHuman(in);
        ReadZombies(in);

        ClearNotUpdatedUnits();
    }

    double MinDistanceToZombie(const Point& p)
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

    Point GetTargetPoint()
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

private:
    static int ReadId(istream& in)
    {
        int id;
        in >> id;
        return id;
    }

    void ReadUnit(map<int, Unit*>& units, istream& in, Unit* (*CreateNewUnit)())
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

    void ReadHuman(istream& in)
    {
        ReadUnit(_humans, in, []() { return new Unit(); });
    }

    void ReadZombies(istream& in)
    {
        ReadUnit(_zombies, in, []() { return static_cast<Unit*>(new Zombie()); });
    }

    void SetAllUnitsNotUpdated()
    {
        for (const auto& unit : _humans)
            _notUpdatedUnitIds.insert(unit.first);
    }

    void ClearNotUpdatedUnits()
    {
        for (auto id : _notUpdatedUnitIds)
        {
            delete _humans[id];
            _humans.erase(id);
        }
    }
};

/**
 * Save humans, destroy zombies!
 **/

int main()
{
    Game game;

    while (true)
    {
        game.ReadState(cin);
        const auto& p = game.GetTargetPoint();
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << p.x << " " << p.y << endl; // Your destination coordinates
    }
}