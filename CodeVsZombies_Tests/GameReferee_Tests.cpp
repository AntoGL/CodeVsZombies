#include "pch.h"
#include "GameReferee.h"
#include "GameConst.h"

using namespace std;
using namespace testing;

constexpr int MOVE_RANGE = static_cast<int>(ASH_SPEED);
constexpr int SAFE_RANGE = static_cast<int>(ASH_ATTACK_RANGE + ZOMBIE_SPEED + 1);

class GameReferee_Tests
{
protected:
	static void FillAshCoordinate(const unique_ptr<GameState>& gameState, const Point& ashCoordinate)
	{
		gameState->SetAshCoordinate(ashCoordinate.x, ashCoordinate.y);
	}

	static void FillZombieCoordinates(const unique_ptr<GameState>& gameState, const vector<Point>& zombieCoordinates)
	{
		const auto& zombies = gameState->GetZombies();
		for (const auto& zombieCoordinate : zombieCoordinates)
		{
			const int id = static_cast<int>(zombies.size());
			gameState->AddZombie(Zombie(id, zombieCoordinate.x, zombieCoordinate.y, -1, -1));
		}
	}

	static unique_ptr<GameState> CreateGameState(const Point& ashCoordinate, const vector<Point>& zombieCoordinates, const vector<Point>&)
	{
		auto gameState = make_unique<GameState>();
		FillAshCoordinate(gameState, ashCoordinate);
		FillZombieCoordinates(gameState, zombieCoordinates);

		return move(gameState);
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		auto referee = GameReferee();
		referee.SetGameState(gameState);

		return referee;
	}
};

struct GameReferee_MoveAsh_Tests : GameReferee_Tests, TestWithParam<tuple<Point, Point, Point>>
{
	static unique_ptr<GameState> CreateGameState(const Point& ashCoordinate)
	{
		return GameReferee_Tests::CreateGameState(ashCoordinate, vector<Point>(), vector<Point>());
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		return GameReferee_Tests::CreateReferee(gameState);
	}
};

INSTANTIATE_TEST_CASE_P(
	PointInMoveRange_MoveToPoint,
	GameReferee_MoveAsh_Tests,
		Values(
			make_tuple(Point(0, 0), Point(0, 0), Point(0, 0)),
			make_tuple(Point(0, 0), Point(1, 0), Point(1, 0)),
			make_tuple(Point(0, 0), Point(0, 1), Point(0, 1)),
			make_tuple(Point(0, 0), Point(1, 1), Point(1, 1)),
			make_tuple(Point(0, 0), Point(-1, 0), Point(-1, 0)),
			make_tuple(Point(0, 0), Point(0, -1), Point(0, -1)),
			make_tuple(Point(0, 0), Point(-1, -1), Point(-1, -1)),
			make_tuple(Point(0, 0), Point(MOVE_RANGE, 0), Point(MOVE_RANGE, 0)),
			make_tuple(Point(0, 0), Point(0, MOVE_RANGE), Point(0, MOVE_RANGE)),
			make_tuple(Point(0, 0), Point(707, 707), Point(707, 707)),
			make_tuple(Point(0, 0), Point(-MOVE_RANGE, 0), Point(-MOVE_RANGE, 0)),
			make_tuple(Point(0, 0), Point(0, -MOVE_RANGE), Point(0, -MOVE_RANGE)),
			make_tuple(Point(0, 0), Point(-707, -707), Point(-707, -707))
		)
);

INSTANTIATE_TEST_CASE_P(
	PointOutMoveRange_MoveToNearestPoint,
	GameReferee_MoveAsh_Tests,
	Values(
		make_tuple(Point(0, 0), Point(MOVE_RANGE + 1, 0), Point(MOVE_RANGE, 0)),
		make_tuple(Point(0, 0), Point(0, MOVE_RANGE + 1), Point(0, MOVE_RANGE)),
		make_tuple(Point(0, 0), Point(MOVE_RANGE + 1, MOVE_RANGE + 1), Point(707, 707)),
		make_tuple(Point(0, 0), Point(-MOVE_RANGE - 1, 0), Point(-MOVE_RANGE, 0)),
		make_tuple(Point(0, 0), Point(0, -MOVE_RANGE - 1), Point(0, -MOVE_RANGE)),
		make_tuple(Point(0, 0), Point(-MOVE_RANGE - 1, -MOVE_RANGE - 1), Point(-707, -707))
	)
);

TEST_P(GameReferee_MoveAsh_Tests, Case)
{
	auto [ashCoordinate, targetPoint, expectedAshCoordinate] = GetParam();
	const auto gameState = CreateGameState(ashCoordinate);
	auto referee = CreateReferee(gameState.get());

	referee.Turn(targetPoint);

	const Point& ash = gameState->GetAsh();

	ASSERT_EQ(expectedAshCoordinate.x, ash.x);
	ASSERT_EQ(expectedAshCoordinate.y, ash.y);
}

class GameReferee_MoveZombie_Tests : public GameReferee_Tests, public TestWithParam<tuple<vector<Point>, vector<Point> > >
{
public:
	static unique_ptr<GameState> CreateGameState(const vector<Point>& zombiesCoordinate)
	{
		constexpr Point ashCoordinate(SAFE_RANGE, SAFE_RANGE);
		return GameReferee_Tests::CreateGameState(ashCoordinate, zombiesCoordinate, vector<Point>());
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		return GameReferee_Tests::CreateReferee(gameState);
	}
};

INSTANTIATE_TEST_CASE_P(
	ZombieShouldMoveToAsh,
	GameReferee_MoveZombie_Tests,
	Values(
		make_tuple(vector{ Point(SAFE_RANGE, 0) }, vector{ Point(SAFE_RANGE, static_cast<int>(ZOMBIE_SPEED)) }),	//top
		make_tuple(vector{ Point(0, SAFE_RANGE) }, vector{ Point(static_cast<int>(ZOMBIE_SPEED), SAFE_RANGE) }),	//left
		make_tuple(vector{ Point(SAFE_RANGE, 2 * SAFE_RANGE) }, vector{ Point(SAFE_RANGE, static_cast<int>(2 * SAFE_RANGE - ZOMBIE_SPEED)) }),	//bottom
		make_tuple(vector{ Point(2 * SAFE_RANGE, SAFE_RANGE) }, vector{ Point(static_cast<int>(2 * SAFE_RANGE - ZOMBIE_SPEED), SAFE_RANGE) })	//right
	)
);

TEST_P(GameReferee_MoveZombie_Tests, Case)
{
	auto [zombieCoordinates, expectedZombieCoordinates] = GetParam();
	const auto gameState = CreateGameState(zombieCoordinates);
	auto referee = CreateReferee(gameState.get());

	referee.Turn(gameState->GetAsh());

	auto& zombies = gameState->GetZombies();
	const auto cnt = zombies.size();
	ASSERT_EQ(expectedZombieCoordinates.size(), cnt);

	for(int i = 0; i < cnt; i++)
	{
		const Point& zombieCoordinate = zombies.at(i).GetCoordinate();
		const auto& expectedZombieCoordinate = expectedZombieCoordinates[i];

		ASSERT_EQ(expectedZombieCoordinate.x, zombieCoordinate.x);
		ASSERT_EQ(expectedZombieCoordinate.y, zombieCoordinate.y);
	}
}