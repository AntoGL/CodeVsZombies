#include "pch.h"
#include "GameState.h"

const Unit& GameState::GetAsh() const
{
	return Ash;
}

const Unit& GameState::GetHuman(const int id) const
{
	return humans.at(id);
}

const Humans& GameState::GetHumans() const
{
	return humans;
}

const Zombie& GameState::GetZombie(const int id) const
{
	return zombies.at(id);
}

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