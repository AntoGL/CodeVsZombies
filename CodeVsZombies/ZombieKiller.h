#pragma once
#include "Point.h"
#include "GameState.h"

struct Turn
{
	Point fistMove;
	std::unique_ptr<GameState> gameState;

	Turn(const Point& point, const GameState& gameState);

	Turn(const Turn& source);
	Turn& operator=(const Turn& source);
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