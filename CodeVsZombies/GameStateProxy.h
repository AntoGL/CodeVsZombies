#pragma once
#include "IGameState.h"

class GameStateProxy : public IGameState
{
	IGameState& gameState;

public:
    GameStateProxy(IGameState& gameState);

    CVZ_EXPORT bool IsEndGame() const override;
    CVZ_EXPORT void SetEndGame(bool value) override;
    CVZ_EXPORT const Unit& GetAsh() const override;
    const Unit& GetHuman(int id) const override;
    CVZ_EXPORT const Humans& GetHumans() const override;
    bool IsAliveHuman(int id) const override;
    const Zombie& GetZombie(int id) const override;
    const Zombies& GetZombies() const override;
    CVZ_EXPORT Zombies& GetZombies() override;

    void Clear() override;

    CVZ_EXPORT void SetAshCoordinate(int x, int y) override;
    CVZ_EXPORT void AddHuman(const Unit& human) override;
    void RemoveHuman(int id) override;
    CVZ_EXPORT void AddZombie(const Zombie& zombie) override;
    void RemoveZombie(int id) override;
    CVZ_EXPORT int GetScore() const override;
    CVZ_EXPORT void SetScore(int value) override;
};