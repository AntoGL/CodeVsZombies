#pragma once
#include "Point.h"
#include "GameState.h"

struct Turn
{
	Point fistMove;
	std::shared_ptr<GameState> gameState;
};

class ZombieKiller
{
	std::vector<Point> GetMoves(const GameState& gameState);
	std::vector<Turn> Calculate(const GameState& gameState);
	std::vector<Turn> Calculate(const std::vector<Turn>& turns);
	std::vector<Turn> Calculate(const Turn& turn);

public:
	Point GetMovePoint(const GameState& gameState);
};