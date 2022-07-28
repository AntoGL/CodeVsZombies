#include "pch.h"
#include "../CodeVsZombies/GameReferee.h"
#include "../CodeVsZombies/GameConst.h"

using namespace std;
using namespace testing;

constexpr int MOVE_RANGE = static_cast<int>(ASH_SPEED);

struct GameReferee_MoveAsh_Tests : TestWithParam<tuple<Point, Point, Point>>
{
	static unique_ptr<GameState> CreateGameState(const Point& ashCoordinate)
	{
		auto gameState = make_unique<GameState>();
		gameState->SetAshCoordinate(ashCoordinate.x, ashCoordinate.y);

		return move(gameState);
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		auto referee = GameReferee();
		referee.SetGameState(gameState);

		return referee;
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