#include "pch.h"
#include <unordered_set>
#include <algorithm>
#include "GameReferee.h"
#include "GameConst.h"
#include "Vector.h"

void GameReferee::SetGameState(const GameStatePtr& gameState)
{
	game = gameState;
}

void GameReferee::Turn(const Point& action)
{
	MoveZombies();
	MoveAsh(action);
	DestroyZombies();
	DestroyHuman();
}

void GameReferee::MoveZombies()
{
	for (auto& zomby : game->GetZombies())
		MoveZombie(zomby.second);
}

void GameReferee::MoveZombie(Zombie& zombie)
{
	Point targetPoint = game->GetAsh();
	double minD = zombie.DistanceTo(targetPoint);
	for (auto& human : game->GetHumans())
	{
		const double d = zombie.DistanceTo(human.second) < minD;
		if (d < minD)
		{
			minD = d;
			targetPoint = human.second;
		}
	}

	Vector v = targetPoint - zombie;
	v.SetLength(ZOMBIE_SPEED);

	zombie.SetCoordinate(zombie + v);
	zombie.SetNextCoordinate(zombie + v);
}

void GameReferee::MoveAsh(const Point& action) const
{
	const Point ashCoord = game->GetAsh();
	Vector move = action - ashCoord;
	if (move.GetLength() > ASH_SPEED)
		move.SetLength(ASH_SPEED);

	const Point nextState = ashCoord + move;
	game->SetAshCoordinate(nextState.x, nextState.y);
}

void GameReferee::DestroyZombies() const
{
	const Point& ashCoordinate = game->GetAsh();
	std::unordered_set<int> destroyedZombieIds;
	for (auto& zombie : game->GetZombies())
	{
		if (ashCoordinate.DistanceTo(zombie.second) < ASH_ATTACK_RANGE)
			destroyedZombieIds.emplace(zombie.first);
	}

	for (const int id : destroyedZombieIds)
		game->RemoveZombie(id);
}

void GameReferee::DestroyHuman() const
{
	const Humans& humans = game->GetHumans();
	const Zombies& zombies = game->GetZombies();
	std::unordered_set<int> destroyedHumanIds;
	for (const std::pair<const int, Unit>& human : humans)
	{
		//TODO: Âûהוכטעü ףסכמגטו ג מעהוכüםûי לועמה
		if (std::any_of(zombies.cbegin(), zombies.cend(),
			[&human](const std::pair<const int, Zombie>& pair)
			{
				return human.second.DistanceTo(pair.second) < ZOMBIE_ATTACK_RANGE;
			}))
			destroyedHumanIds.emplace(human.first);
	}

	for (const int id : destroyedHumanIds)
		game->RemoveHuman(id);
}
