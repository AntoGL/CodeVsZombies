#pragma once
#include <iostream>
#include "GameState.h"

class GameStateReader
{
public:
	static void Read(GameState& gameState, std::istream& input);

private:
	static void ReadAsh(GameState& gameState, std::istream& input);
	static void ReadHumans(GameState& gameState, std::istream& input);
	static void ReadZombies(GameState& gameState, std::istream& input);
};