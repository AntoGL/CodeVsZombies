#pragma once
#include <unordered_map>
#include "Zombie.h"

using Humans = std::unordered_map<int, Unit>;

class GameState
{
    Humans humans;
    std::unordered_map<int, Zombie> zombies;
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

    void Clear();

    void SetAshCoordinate(int x, int y);
    void AddHuman(const Unit& human);
    void AddZombie(const Zombie& zombie);
};
