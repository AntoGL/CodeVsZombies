#include "pch.h"
#include <iostream>
#include "ZombieKiller.h"
#include "GameReferee.h"
#include "Vector.h"

std::vector<Point> ZombieKiller::GetMoves(const GameState& gameState)
{
	//TODO: Сделать код читабельнее
	static const Vector base(1, 0);
	constexpr double angle180 = 3.14159265; // std::acos(-1);
	constexpr double angle90 = 1.57079633; // std::acos(0);

	if (gameState.IsEndGame())
		return { gameState.GetAsh() };

	std::vector moves(4, Point(0, 0));

	const auto& ash = gameState.GetAsh();
	const auto& humans = gameState.GetHumans();
	for (const auto& [_, human] : humans)
	{
		Vector ashToHuman(ash, human);
		if (ashToHuman.x == 0 && ashToHuman.y == 0)
		{
			moves[0] = human;
			continue;
		}

		ashToHuman.SetLength(1);
		double angle = base.Angle(ashToHuman);
		if (ashToHuman.y < 0)
			angle += angle180;

		const int sectorIndex = static_cast<int>(angle / angle90);
		moves[sectorIndex] = human;
	}

	for (int i = moves.size() -1; i >= 0; i--)
		if (moves[i].x == 0 && moves[i].y == 0)
			moves.erase(moves.begin() + i);

	return moves;
}

std::vector<Turn> ZombieKiller::Calculate(const GameState& gameState)
{
	const auto moves = GetMoves(gameState);

	std::vector<Turn> turns;
	turns.reserve(moves.size());

	static GameReferee referee;
	for (const auto& p : moves)
	{
		auto copy = std::make_shared<GameState>(gameState);
		turns.push_back(Turn{ p, copy });
		referee.SetGameState(copy.get());
		referee.Turn(p);
	}

	return turns;
}

std::vector<Turn> ZombieKiller::Calculate(const std::vector<Turn>& turns)
{
	std::vector<Turn> res;
	for (const auto& turn : turns)
	{
		for (const auto& t : Calculate(turn))
			res.push_back(t);
	}

	return res;
}

std::vector<Turn> ZombieKiller::Calculate(const Turn& turn)
{
	const auto& gameState = *turn.gameState;
	const auto moves = GetMoves(gameState);

	std::vector<Turn> turns;
	turns.reserve(moves.size());

	static GameReferee referee;
	for (const auto& p : moves)
	{
		auto copy = std::make_shared<GameState>(gameState);
		turns.emplace_back(Turn{ turn.fistMove, copy });
		referee.SetGameState(copy.get());
		referee.Turn(p);
	}

	return turns;
}

Point ZombieKiller::GetMovePoint(const GameState& gameState)
{
	auto turns = Calculate(gameState);
	for (int i = 0; i < 5; i++)
	{
		turns = Calculate(turns);
	}

	Point res { 0, 0 };
	int maxScore = -1;
	for (const auto & turn : turns)
	{
		if (maxScore < turn.gameState->GetScore())
		{
			res = turn.fistMove;
			maxScore = turn.gameState->GetScore();
		}
	}

	return res;
}