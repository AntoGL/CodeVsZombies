#include "pch.h"
#include <iostream>
#include "Point.h"
#include "Unit.h"
#include "GameState.h"

using namespace std;

int main()
{
    GameState game;

    while (true)
    {
        game.ReadState(cin);
        const auto& p = game.GetTargetPoint();
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << p.x << " " << p.y << endl; // Your destination coordinates
    }
}