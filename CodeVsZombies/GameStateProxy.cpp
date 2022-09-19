#include "pch.h"
#include "GameStateProxy.h"


GameStateProxy::GameStateProxy(IGameState& gameState)
	: gameState(gameState)
{
}

bool GameStateProxy::IsEndGame() const
{
	return gameState.IsEndGame();
}

void GameStateProxy::SetEndGame(const bool value)
{
	gameState.SetEndGame(value);
}

const Unit& GameStateProxy::GetAsh() const
{
	return gameState.GetAsh();
}

const Unit& GameStateProxy::GetHuman(const int id) const
{
	return gameState.GetHuman(id);
}

const Humans& GameStateProxy::GetHumans() const
{
	return gameState.GetHumans();
}

bool GameStateProxy::IsAliveHuman(const int id) const
{
	return gameState.IsAliveHuman(id);
}

const Zombie& GameStateProxy::GetZombie(const int id) const
{
	return gameState.GetZombie(id);
}

const Zombies& GameStateProxy::GetZombies() const
{
	return gameState.GetZombies();
}

Zombies& GameStateProxy::GetZombies()
{
	return gameState.GetZombies();
}

void GameStateProxy::Clear()
{
	gameState.Clear();
}

void GameStateProxy::SetAshCoordinate(const int x, const int y)
{
	gameState.SetAshCoordinate(x, y);
}

void GameStateProxy::AddHuman(const Unit& human)
{
	gameState.AddHuman(human);
}

void GameStateProxy::RemoveHuman(const int id)
{
	gameState.RemoveHuman(id);
}

void GameStateProxy::AddZombie(const Zombie& zombie)
{
	gameState.AddZombie(zombie);
}

void GameStateProxy::RemoveZombie(const int id)
{
	gameState.RemoveZombie(id);
}

int GameStateProxy::GetScore() const
{
	return gameState.GetScore();
}

void GameStateProxy::SetScore(const int value)
{
	gameState.SetScore(value);
}