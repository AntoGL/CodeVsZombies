#pragma once
#include "GameState.h"

class GameReferee
{
	GameStatePtr game;

public:
	GameReferee() = default;

	void SetGameState(const GameStatePtr& gameState);
	void Turn(const Point& action);

private:
	void MoveZombies();
	void MoveZombie(Zombie& zombie);

	void MoveAsh(const Point& action) const;
	void DestroyZombies() const;
	void DestroyHuman() const;
};