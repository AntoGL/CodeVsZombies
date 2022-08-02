#pragma once
#include <unordered_map>
#include <memory>
#include "Zombie.h"

using Humans = std::unordered_map<int, Unit>;
using Zombies = std::unordered_map<int, Zombie>;

class GameState
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

    CVZ_EXPORT bool IsEndGame() const;
    CVZ_EXPORT void SetEndGame(bool value);
    CVZ_EXPORT const Unit& GetAsh() const;
    const Unit& GetHuman(int id) const;
    CVZ_EXPORT const Humans& GetHumans() const;
    const Zombie& GetZombie(int id) const;
    const Zombies& GetZombies() const;
    CVZ_EXPORT Zombies& GetZombies();

    void Clear();

    CVZ_EXPORT void SetAshCoordinate(int x, int y);
    CVZ_EXPORT void AddHuman(const Unit& human);
    void RemoveHuman(int id);
    CVZ_EXPORT void AddZombie(const Zombie& zombie);
    void RemoveZombie(int id);
    CVZ_EXPORT int GetScore() const;
    CVZ_EXPORT void SetScore(int value);
};

using GameStatePtr = GameState*;