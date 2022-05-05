#include "pch.h"
#include "GameState.h"

void GameState::Clear()
{
	Ash = Unit(0, 0);
	humans.clear();
	zombies.clear();
}

void GameState::SetAshCoordinate(const int x, const int y)
{
	Ash = Unit(x, y);
}

void GameState::AddHuman(const Unit& human)
{
	humans.insert_or_assign(human.GetId(), human);
}

void GameState::AddZombie(const Zombie& zombie)
{
	zombies.insert_or_assign(zombie.GetId(), zombie);
}