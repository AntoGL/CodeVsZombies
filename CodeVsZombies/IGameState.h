#pragma once
#include <unordered_map>
#include "export.h"
#include "Zombie.h"

using Humans = std::unordered_map<int, Unit>;
using Zombies = std::unordered_map<int, Zombie>;

class IGameState
{
public:
    CVZ_EXPORT virtual bool IsEndGame() const = 0;
    CVZ_EXPORT virtual void SetEndGame(bool value) = 0;
    CVZ_EXPORT virtual const Unit& GetAsh() const = 0;
    virtual const Unit& GetHuman(int id) const = 0;
    CVZ_EXPORT virtual const Humans& GetHumans() const = 0;
    virtual bool IsAliveHuman(int id) const = 0;
    virtual const Zombie& GetZombie(int id) const = 0;
    virtual const Zombies& GetZombies() const = 0;
    virtual CVZ_EXPORT Zombies& GetZombies() = 0;

    virtual void Clear() = 0;

    virtual CVZ_EXPORT void SetAshCoordinate(int x, int y) = 0;
    virtual CVZ_EXPORT void AddHuman(const Unit& human) = 0;
    virtual void RemoveHuman(int id) = 0;
    virtual CVZ_EXPORT void AddZombie(const Zombie& zombie) = 0;
    virtual void RemoveZombie(int id) = 0;
    virtual CVZ_EXPORT int GetScore() const = 0;
    virtual CVZ_EXPORT void SetScore(int value) = 0;
};