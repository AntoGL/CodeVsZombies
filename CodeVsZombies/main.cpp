#include "pch.h"
#include <iostream>
#include "GameStateReader.h"
#include "ZombieKiller.h"

using namespace std;

int main()
{
    GameState game;
    ZombieKiller killer;

    while (true)
    {
        GameStateReader::Read(game, std::cin);
        const Point res = killer.GetMovePoint(game);

    	cout << res.x << " " << res.y << endl;
    }
}