#pragma once
#include "IGameState.h"

class GameStateProxy : public IGameState
{
	IGameState& gameState;

public:
    CVZ_EXPORT GameStateProxy(IGameState& gameState);

    CVZ_EXPORT bool IsEndGame() const override;
    CVZ_EXPORT void SetEndGame(bool value) override;
    CVZ_EXPORT const Unit& GetAsh() const override;
    CVZ_EXPORT const Unit& GetHuman(int id) const override;
    CVZ_EXPORT const Humans& GetHumans() const override;
    CVZ_EXPORT bool IsAliveHuman(int id) const override;
    CVZ_EXPORT const Zombie& GetZombie(int id) const override;
    CVZ_EXPORT const Zombies& GetZombies() const override;
    CVZ_EXPORT Zombies& GetZombies() override;

    CVZ_EXPORT void Clear() override;

    CVZ_EXPORT void SetAshCoordinate(int x, int y) override;
    CVZ_EXPORT void AddHuman(const Unit& human) override;
    CVZ_EXPORT void RemoveHuman(int id) override;
    CVZ_EXPORT void AddZombie(const Zombie& zombie) override;
    CVZ_EXPORT void RemoveZombie(int id) override;
    CVZ_EXPORT int GetScore() const override;
    CVZ_EXPORT void SetScore(int value) override;
};