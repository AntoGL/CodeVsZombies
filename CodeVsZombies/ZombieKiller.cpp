#include "pch.h"
#include <queue>
#include "ZombieKiller.h"
#include "GameReferee.h"

std::vector<Point> ZombieKiller::GetMoves(const GameState& gameState)
{
	std::vector<Point> moves;
	const auto& humans = gameState.GetHumans();
	for (const auto& [_, human] : humans)
		moves.push_back(human);

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
	for (int i = 0; i < 10; i++)
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