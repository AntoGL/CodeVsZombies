#include "pch.h"
#include <unordered_set>
#include <algorithm>
#include "GameReferee.h"
#include "Fibonachi.h"
#include "GameConst.h"
#include "Vector.h"

void GameReferee::SetGameState(GameState* gameState)
{
	game = gameState;
}

void GameReferee::Turn(const Point& action)
{
	MoveZombies();
	MoveAsh(action);
	DestroyZombies();
	DestroyHuman();
	CheckEndGame();
}

void GameReferee::MoveZombies()
{
	for (auto& [_, zombie] : game->GetZombies())
		MoveZombie(zombie);
}

void GameReferee::MoveZombie(Zombie& zombie)
{
	UpdateZombieTarget(zombie);
	const Unit& targetUnit = GetZombieTarget(zombie);

	Vector v = targetUnit - zombie;
	if (v.GetLength() > ZOMBIE_SPEED)
		v.SetLength(ZOMBIE_SPEED);

	zombie.SetCoordinate(zombie + v);
	zombie.SetNextCoordinate(zombie + v);
}

void GameReferee::UpdateZombieTarget(Zombie& zombie) const
{
	int id = zombie.GetTargetId();
	if (id != ASH_ID)
	{
		const Point& targetHumanCoordinate = GetZombieTarget(zombie);
		const Point& ashCoordinate = game->GetAsh();
		if (ashCoordinate.DistanceTo(zombie) < targetHumanCoordinate.DistanceTo(zombie))
			id = ASH_ID;
	}
	else
	{
		double minD = zombie.DistanceTo(game->GetAsh());
		for (const auto& [_, human] : game->GetHumans())
		{
			if (const double d = zombie.DistanceTo(human); d < minD)
			{
				minD = d;
				id = human.GetId();
			}
		}
	}

	zombie.SetTargetId(id);
}

const Unit& GameReferee::GetZombieTarget(const Zombie& zombie) const
{
	const int targetId = zombie.GetTargetId();
	return targetId == ASH_ID ? game->GetAsh() : game->GetHuman(targetId);
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
		if (ashCoordinate.DistanceTo(zombie.second) <= ASH_ATTACK_RANGE)
			destroyedZombieIds.emplace(zombie.first);
	}

	for (const int id : destroyedZombieIds)
		game->RemoveZombie(id);

	AddScore(static_cast<int>(destroyedZombieIds.size()));
}

void GameReferee::AddScore(const int countZombiesDestoied) const
{
	auto score = game->GetScore();
	const auto countHumans = static_cast<int>(game->GetHumans().size());
	const auto humansScore = countHumans * countHumans;
	const auto zombieScore = Fibonachi::at(countZombiesDestoied + 2);

	score += zombieScore * humansScore * 10;

	game->SetScore(score);
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

void GameReferee::CheckEndGame() const
{
	const bool allHumanDead = game->GetHumans().empty();
	const bool allZombieDead = game->GetZombies().empty();
	game->SetEndGame(allHumanDead || allZombieDead);
	if (allHumanDead)
		game->SetScore(0);
}