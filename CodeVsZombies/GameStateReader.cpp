#include "pch.h"
#include "GameStateReader.h"

void GameStateReader::Read(GameState& gameState, std::istream& input)
{
	gameState.Clear();

	ReadAsh(gameState, input);
	ReadHumans(gameState, input);
	ReadZombies(gameState, input);
}

void GameStateReader::ReadAsh(GameState& gameState, std::istream& input)
{
	int x, y;
	input >> x >> y;
	input.ignore();

	gameState.SetAshCoordinate(x, y);
}

void GameStateReader::ReadHumans(GameState& gameState, std::istream& input)
{
	int count;
	input >> count; input.ignore();
	for (int i = 0; i < count; i++) {
		int id, x, y;
		input >> id >> x >> y;
		input.ignore();

		gameState.AddHuman(Unit(id, x, y));
	}
}

void GameStateReader::ReadZombies(GameState& gameState, std::istream& input)
{
	int count;
	input >> count; input.ignore();
	for (int i = 0; i < count; i++) {
		int id, x, y, nextX, nextY;
		input >> id >> x >> y >> nextX >> nextY;
		input.ignore();

		gameState.AddZombie(Zombie(id, x, y, nextX, nextY));
	}
}