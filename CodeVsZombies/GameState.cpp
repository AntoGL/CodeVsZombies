#include "pch.h"
#include "GameState.h"

GameState::GameState()
	: isEndGame(false)
	, score(0)
{

}

GameState::GameState(const GameState& source)
	: isEndGame(source.isEndGame)
	, Ash(source.Ash)
	, score(source.score)
{
	for (const auto& [_, human] : source.humans)
		AddHuman(human);

	for (const auto& [_, zombie] : source.zombies)
		AddZombie(zombie);
}

bool GameState::IsEndGame() const
{
	return isEndGame;
}

void GameState::SetEndGame(const bool value)
{
	isEndGame = value;
}

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

const Zombies& GameState::GetZombies() const
{
	return zombies;
}

Zombies& GameState::GetZombies()
{
	return zombies;
}

void GameState::Clear()
{
	isEndGame = false;
	Ash = Unit(0, 0);
	humans.clear();
	zombies.clear();
	score = 0;
}

void GameState::SetAshCoordinate(const int x, const int y)
{
	Ash = Unit(x, y);
}

void GameState::AddHuman(const Unit& human)
{
	humans.insert_or_assign(human.GetId(), human);
}

void GameState::RemoveHuman(const int id)
{
	humans.erase(id);
}

void GameState::AddZombie(const Zombie& zombie)
{
	zombies.insert_or_assign(zombie.GetId(), zombie);
}

void GameState::RemoveZombie(const int id)
{
	zombies.erase(id);
}

int GameState::GetScore() const
{
	return score;
}

void GameState::SetScore(const int value)
{
	score = value;
}