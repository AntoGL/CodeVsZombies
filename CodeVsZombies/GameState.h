#pragma once
#include <unordered_map>
#include <memory>
#include "Zombie.h"

using Humans = std::unordered_map<int, Unit>;
using Zombies = std::unordered_map<int, Zombie>;

class GameState
{
    Humans humans;
    Zombies zombies;
    Unit Ash;

public:
    CVZ_EXPORT GameState() = default;
    ~GameState() = default;

    CVZ_EXPORT GameState(const GameState&) = delete;
    CVZ_EXPORT GameState(GameState&&) = delete;

    CVZ_EXPORT GameState& operator=(const GameState&) = delete;
    CVZ_EXPORT GameState& operator=(GameState&&) = delete;

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
};

using GameStatePtr = GameState*;