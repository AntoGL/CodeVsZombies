#include "pch.h"
#include "ZombieKiller.h"

Point ZombieKiller::GetMovePoint(const GameState& gameState)
{
	const auto& humans = gameState.GetHumans();
	const Unit& player = gameState.GetAsh();

	double minD = 1000000;
	Point p(0, 0);
	for (const auto& human : humans)
	{
		const double d = player.DistanceTo(human.second);
		if (d < minD)
		{
			minD = d;
			p = human.second;
		}
	}

	return p;
}