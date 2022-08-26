#pragma once
#include "GameState.h"

class GameReferee
{
	GameStatePtr game;

public:
	CVZ_EXPORT GameReferee() = default;

	CVZ_EXPORT void SetGameState(GameStatePtr gameState);
	CVZ_EXPORT void Turn(const Point& action);

private:
	void MoveZombies();
	void MoveZombie(Zombie& zombie);
	void UpdateZombieTarget(Zombie& zombie) const;
	const Unit& GetZombieTarget(const Zombie& zombie) const;

	void MoveAsh(const Point& action) const;
	void DestroyZombies() const;
	void DestroyHuman() const;
	void AddScore(int countZombiesDestoied) const;
	void CheckEndGame() const;
};