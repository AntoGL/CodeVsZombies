#pragma once
class Unit
{
    int id;
    int x;
    int y;

public:
    Unit();
    Unit(int x, int y);
    Unit(int id, int x, int y);
    virtual ~Unit() = default;

    int GetId() const;
};