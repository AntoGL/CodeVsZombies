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
    GameState() = default;
    ~GameState() = default;

    GameState(const GameState&) = delete;
    GameState(GameState&&) = delete;

    GameState& operator=(const GameState&) = delete;
    GameState& operator=(GameState&&) = delete;

    const Unit& GetAsh() const;
    const Unit& GetHuman(int id) const;
    const Humans& GetHumans() const;
    const Zombie& GetZombie(int id) const;
    const Zombies& GetZombies() const;
    Zombies& GetZombies();

    void Clear();

    void SetAshCoordinate(int x, int y);
    void AddHuman(const Unit& human);
    void RemoveHuman(int id);
    void AddZombie(const Zombie& zombie);
    void RemoveZombie(int id);
};

using GameStatePtr = GameState*;