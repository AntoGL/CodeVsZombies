#pragma once
#include "Unit.h"

class Zombie final
	: public Unit
{
    int _nextX;
    int _nextY;

protected:
    void UpdateImpl(std::istream& in) override;

public:
    Zombie();
};