#pragma once
#include <unordered_map>
#include "Zombie.h"

class GameState
{
    std::unordered_map<int, Unit> humans;
    std::unordered_map<int, Zombie> zombies;
    Unit Ash;

public:
    GameState() = default;
    ~GameState() = default;

    GameState(const GameState&) = delete;
    GameState(GameState&&) = delete;

    GameState& operator=(const GameState&) = delete;
    GameState& operator=(GameState&&) = delete;

    void Clear();

    void SetAshCoordinate(int x, int y);
    void AddHuman(const Unit& human);
    void AddZombie(const Zombie& zombie);
};
