#include "pch.h"
#include <iostream>
#include "GameStateReader.h"

using namespace std;

int main()
{
    GameState game;

    while (true)
    {
        GameStateReader::Read(game, std::cin);

    	cout << "0 0" << endl;
    }
}