#pragma once
#include <memory>
#include "IGameState.h"

//TODO: Посмотреть происходят ли тормоза при частом копировании колекции зомби (тормоза на выделение памяти под колекцию)
class GameState : IGameState
{
    bool isEndGame;
    Humans humans;
    Zombies zombies;
    Unit Ash;
    int score;

public:
    CVZ_EXPORT GameState();
    ~GameState() = default;

    CVZ_EXPORT GameState(const GameState& source);
    CVZ_EXPORT GameState(GameState&&) = delete;

    CVZ_EXPORT GameState& operator=(const GameState&) = delete;
    CVZ_EXPORT GameState& operator=(GameState&&) = delete;

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

using GameStatePtr = GameState*;