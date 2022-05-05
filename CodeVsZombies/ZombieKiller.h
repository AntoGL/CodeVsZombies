#pragma once
#include "Point.h"
#include "GameState.h"

class ZombieKiller
{
public:
	Point GetMovePoint(const GameState& gameState);
};