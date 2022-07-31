#include "pch.h"
#include "GameReferee.h"
#include "GameConst.h"

using namespace std;
using namespace testing;

constexpr int MOVE_RANGE = static_cast<int>(ASH_SPEED);
constexpr int ASH_SAFE_RANGE = static_cast<int>(ASH_ATTACK_RANGE + ZOMBIE_SPEED + 1);
constexpr int ZOMBIE_SAFE_RANGE = static_cast<int>(ZOMBIE_ATTACK_RANGE + ZOMBIE_SPEED + 1);
constexpr int ZOMBIE_NOT_SAFE_RANGE = static_cast<int>(ZOMBIE_ATTACK_RANGE + ZOMBIE_SPEED - 1);

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
			//TODO: Добавить вычисление следующих координат для зомби
			gameState->AddZombie(Zombie(id, zombieCoordinate.x, zombieCoordinate.y, -1, -1));
		}
	}

	static void FillHumans(const unique_ptr<GameState>& gameState, const vector<Point>& humansCoordinates)
	{
		const auto& humans = gameState->GetHumans();
		for (const auto& humanCoordinate : humansCoordinates)
		{
			const int id = static_cast<int>(humans.size());
			gameState->AddHuman(Unit(id, humanCoordinate.x, humanCoordinate.y));
		}
	}

	static unique_ptr<GameState> CreateGameState(const Point& ashCoordinate, const vector<Point>& zombieCoordinates, const vector<Point>& humansCoordinates)
	{
		auto gameState = make_unique<GameState>();
		FillAshCoordinate(gameState, ashCoordinate);
		FillHumans(gameState, humansCoordinates);
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

class GameReferee_MoveZombie_Tests : public GameReferee_Tests, public TestWithParam<tuple<vector<Point>, vector<Point>, vector<Point>>>
{
public:
	static unique_ptr<GameState> CreateGameState(const vector<Point>& zombiesCoordinate, const vector<Point>& humansCoordinate)
	{
		constexpr Point ashCoordinate(ASH_SAFE_RANGE, ASH_SAFE_RANGE);
		return GameReferee_Tests::CreateGameState(ashCoordinate, zombiesCoordinate, humansCoordinate);
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
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 0) }, vector<Point>(), vector{ Point(ASH_SAFE_RANGE, static_cast<int>(ZOMBIE_SPEED)) }),	//Зомби сверху
		make_tuple(vector{ Point(0, ASH_SAFE_RANGE) }, vector<Point>(), vector{ Point(static_cast<int>(ZOMBIE_SPEED), ASH_SAFE_RANGE) }),	//Зомби слева
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 2 * ASH_SAFE_RANGE) }, vector<Point>(), vector{ Point(ASH_SAFE_RANGE, static_cast<int>(2 * ASH_SAFE_RANGE - ZOMBIE_SPEED)) }),	//Зомби снизу
		make_tuple(vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) }, vector<Point>(), vector{ Point(static_cast<int>(2 * ASH_SAFE_RANGE - ZOMBIE_SPEED), ASH_SAFE_RANGE) }),	//Зомби справа
		make_tuple(	//Зомби со всех сторон
			vector
			{
				Point(ASH_SAFE_RANGE, 0),
				Point(0, ASH_SAFE_RANGE),
				Point(ASH_SAFE_RANGE, 2 * ASH_SAFE_RANGE),
				Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE)
			},
			vector<Point>(),
			vector
			{
				Point(ASH_SAFE_RANGE, static_cast<int>(ZOMBIE_SPEED)),
				Point(static_cast<int>(ZOMBIE_SPEED), ASH_SAFE_RANGE),
				Point(ASH_SAFE_RANGE, static_cast<int>(2 * ASH_SAFE_RANGE - ZOMBIE_SPEED)),
				Point(static_cast<int>(2 * ASH_SAFE_RANGE - ZOMBIE_SPEED), ASH_SAFE_RANGE)
			})
	)
);

INSTANTIATE_TEST_CASE_P(
	ZombieShouldMoveToNearesHuman,
	GameReferee_MoveZombie_Tests,
	Values(
		make_tuple(	//Ближайший человек сверху от зомби
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE - ZOMBIE_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, static_cast<int>(ASH_SAFE_RANGE - ZOMBIE_SPEED)) }),
		make_tuple(	//Ближайший человек снизу от зомби
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE + ZOMBIE_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, static_cast<int>(ASH_SAFE_RANGE + ZOMBIE_SPEED)) }),
		make_tuple(	//Ближайший человек слева от зомби
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE - ZOMBIE_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(static_cast<int>(2 * ASH_SAFE_RANGE - ZOMBIE_SPEED), ASH_SAFE_RANGE) }),
		make_tuple(	//Ближайший человек справа от зомби
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE + ZOMBIE_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(static_cast<int>(2 * ASH_SAFE_RANGE + ZOMBIE_SPEED), ASH_SAFE_RANGE) }),
		make_tuple(	//Эш слева от зомби и он ближе чем другой человек
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(3 * ASH_SAFE_RANGE + 1, ASH_SAFE_RANGE) },
			vector{ Point(static_cast<int>(2 * ASH_SAFE_RANGE - ZOMBIE_SPEED), ASH_SAFE_RANGE) })
	)
);

TEST_P(GameReferee_MoveZombie_Tests, Case)
{
	auto [zombieCoordinates, humansCoordinates, expectedZombieCoordinates] = GetParam();
	const auto gameState = CreateGameState(zombieCoordinates, humansCoordinates);
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

class GameReferee_DestoyZombie_Tests : public GameReferee_Tests, public TestWithParam<tuple<vector<Point>, vector<int>>>
{
public:
	static unique_ptr<GameState> CreateGameState(const vector<Point>& zombiesCoordinate)
	{
		constexpr Point ashCoordinate(ASH_SAFE_RANGE, ASH_SAFE_RANGE);
		return GameReferee_Tests::CreateGameState(ashCoordinate, zombiesCoordinate, vector<Point>());
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		return GameReferee_Tests::CreateReferee(gameState);
	}
};

INSTANTIATE_TEST_CASE_P(
	ZombieInAshAtackRange_ShouldBeDestroyed,
	GameReferee_DestoyZombie_Tests,
	Values(
		make_tuple(vector{ Point(1, ASH_SAFE_RANGE) }, vector<int>()),
		make_tuple(vector{ Point(2 * ASH_SAFE_RANGE - 1, ASH_SAFE_RANGE) }, vector<int>()),
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 1) }, vector<int>()),
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 2 * ASH_SAFE_RANGE - 1) }, vector<int>()),
		make_tuple(vector{ Point(100, ASH_SAFE_RANGE) }, vector<int>()),
		make_tuple(vector{ Point(2 * ASH_SAFE_RANGE - 100, ASH_SAFE_RANGE) }, vector<int>()),
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 100) }, vector<int>()),
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 2 * ASH_SAFE_RANGE - 100) }, vector<int>())
	)
);

INSTANTIATE_TEST_CASE_P(
	ZombieOutAshAtackRange_ShouldBeAlive,
	GameReferee_DestoyZombie_Tests,
	Values(
		make_tuple(vector{ Point(0, ASH_SAFE_RANGE) }, vector{ 0 }),
		make_tuple(vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) }, vector{ 0 }),
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 0) }, vector{ 0 }),
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 2 * ASH_SAFE_RANGE) }, vector{ 0 }),
		make_tuple(vector{ Point(2 * ASH_SAFE_RANGE + 400, ASH_SAFE_RANGE) }, vector{ 0 }),
		make_tuple(vector{ Point(ASH_SAFE_RANGE, 2 * ASH_SAFE_RANGE + 400) }, vector{ 0 }),
		make_tuple(
			vector{
				Point(2 * ASH_SAFE_RANGE + 400, ASH_SAFE_RANGE),
				Point(ASH_SAFE_RANGE, 2 * ASH_SAFE_RANGE + 400),
				Point(1, ASH_SAFE_RANGE),
				Point(0, 0)
			},
			vector{ 0, 1, 3 })
	)
);

TEST_P(GameReferee_DestoyZombie_Tests, Case)
{
	auto [zombiesCoodinates, expectedAliveZombiesIds] = GetParam();
	const auto gameState = CreateGameState(zombiesCoodinates);
	auto referee = CreateReferee(gameState.get());

	referee.Turn(gameState->GetAsh());

	auto& zombies = gameState->GetZombies();
	ASSERT_EQ(expectedAliveZombiesIds.size(), zombies.size());
	for (const auto& it : expectedAliveZombiesIds)
		ASSERT_TRUE(zombies.find(it) != zombies.end());
}

class GameReferee_DestroyHuman_Tests : public GameReferee_Tests, public TestWithParam<tuple<vector<Point>, vector<Point>, vector<int>>>
{
public:
	static unique_ptr<GameState> CreateGameState(const vector<Point>& zombiesCoordinate, const vector<Point>& humansCoordinate)
	{
		constexpr Point ashCoordinate(ASH_SAFE_RANGE, ASH_SAFE_RANGE);
		return GameReferee_Tests::CreateGameState(ashCoordinate, zombiesCoordinate, humansCoordinate);
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		return GameReferee_Tests::CreateReferee(gameState);
	}
};

INSTANTIATE_TEST_CASE_P(
	HumanInZombieAtackRange_ShouldBeDestroyed,
	GameReferee_DestroyHuman_Tests,
	Values(
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector<int>()),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE + ZOMBIE_NOT_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector<int>()),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE - ZOMBIE_NOT_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector<int>()),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE + ZOMBIE_NOT_SAFE_RANGE) },
			vector<int>()),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE - ZOMBIE_NOT_SAFE_RANGE) },
			vector<int>())
	)
);

INSTANTIATE_TEST_CASE_P(
	HumanOutZombieAtackRange_ShouldBeAlive,
	GameReferee_DestroyHuman_Tests,
	Values(
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE + ZOMBIE_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ 0 }),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE - ZOMBIE_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ 0 }),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE + ZOMBIE_SAFE_RANGE) },
			vector{ 0 }),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE - ZOMBIE_SAFE_RANGE) },
			vector{ 0 })
	)
);

TEST_P(GameReferee_DestroyHuman_Tests, Case)
{
	auto [zombiesCoordinates, humansCoordinates, expectedAliveHumanIds] = GetParam();
	const auto gameState = CreateGameState(zombiesCoordinates, humansCoordinates);
	auto referee = CreateReferee(gameState.get());

	referee.Turn(gameState->GetAsh());

	auto& humans = gameState->GetHumans();
	ASSERT_EQ(expectedAliveHumanIds.size(), humans.size());
	for (const auto& it : expectedAliveHumanIds)
		ASSERT_TRUE(humans.find(it) != humans.end());
}

class GameReferee_EndGame_Tests : public GameReferee_Tests, public TestWithParam<tuple<vector<Point>, vector<Point>, bool>>
{
public:
	static unique_ptr<GameState> CreateGameState(const vector<Point>& zombiesCoordinate, const vector<Point>& humansCoordinate)
	{
		constexpr Point ashCoordinate(ASH_SAFE_RANGE, ASH_SAFE_RANGE);
		return GameReferee_Tests::CreateGameState(ashCoordinate, zombiesCoordinate, humansCoordinate);
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		return GameReferee_Tests::CreateReferee(gameState);
	}
};

INSTANTIATE_TEST_CASE_P(
	AllHumanDestroyed_EndGame,
	GameReferee_EndGame_Tests,
	Values(
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			true),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE + ZOMBIE_NOT_SAFE_RANGE, ASH_SAFE_RANGE) },
			true),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE - ZOMBIE_NOT_SAFE_RANGE, ASH_SAFE_RANGE) },
			true),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE + ZOMBIE_NOT_SAFE_RANGE) },
			true),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE - ZOMBIE_NOT_SAFE_RANGE) },
			true)
	)
);

INSTANTIATE_TEST_CASE_P(
	AnyHumanAlive_GameContinuing,
	GameReferee_EndGame_Tests,
	Values(
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE + ZOMBIE_SAFE_RANGE, ASH_SAFE_RANGE) },
			false),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE - ZOMBIE_SAFE_RANGE, ASH_SAFE_RANGE) },
			false),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE + ZOMBIE_SAFE_RANGE) },
			false),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE - ZOMBIE_SAFE_RANGE) },
			false),
		make_tuple(
			vector{ Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector{
				Point(2 * ASH_SAFE_RANGE + ZOMBIE_NOT_SAFE_RANGE, ASH_SAFE_RANGE),
				Point(2 * ASH_SAFE_RANGE, ASH_SAFE_RANGE - ZOMBIE_SAFE_RANGE) },
			false)
	)
);

TEST_P(GameReferee_EndGame_Tests, Case)
{
	auto [zombiesCoordinates, humansCoordinates, expectedEndGame] = GetParam();
	const auto gameState = CreateGameState(zombiesCoordinates, humansCoordinates);
	auto referee = CreateReferee(gameState.get());

	referee.Turn(gameState->GetAsh());

	ASSERT_EQ(expectedEndGame, gameState->IsEndGame());
}

class GameReferee_Score_Tests : public GameReferee_Tests, public TestWithParam<tuple<vector<Point>, vector<Point>, int>>
{
public:
	static unique_ptr<GameState> CreateGameState(const vector<Point>& zombiesCoordinate, const vector<Point>& humansCoordinate)
	{
		constexpr Point ashCoordinate(ASH_SAFE_RANGE, ASH_SAFE_RANGE);
		return GameReferee_Tests::CreateGameState(ashCoordinate, zombiesCoordinate, humansCoordinate);
	}

	static GameReferee CreateReferee(const GameStatePtr& gameState)
	{
		return GameReferee_Tests::CreateReferee(gameState);
	}
};

INSTANTIATE_TEST_CASE_P(
	SeveralHumans_ScoreEqualNumberOfHumansSquaredx10,	// NumberOfHumans * NumberOfHumans * 10
	GameReferee_Score_Tests,
	Values(
		make_tuple(
			vector{ Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector(1, Point(0, 0)),
			10),
		make_tuple(
			vector{ Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector(2, Point(0, 0)),
			40),
		make_tuple(
			vector{ Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector(3, Point(0, 0)),
			90),
		make_tuple(
			vector{ Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector(5, Point(0, 0)),
			250),
		make_tuple(
			vector{ Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector(10, Point(0, 0)),
			1000),
		make_tuple(
			vector{ Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE) },
			vector(20, Point(0, 0)),
			4000)
	)
);

INSTANTIATE_TEST_CASE_P(
	SeveralZombie_ScoreEqualFibNumberOfDestroyedZobiesSub2,	// Fib(NumberOfDestroyedZobies + 2) * 10
	GameReferee_Score_Tests,
	Values(
		make_tuple(
			vector(1, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(1, Point(0, 0)),
			10),
		make_tuple(
			vector(2, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(1, Point(0, 0)),
			20),
		make_tuple(
			vector(3, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(1, Point(0, 0)),
			30),
		make_tuple(
			vector(4, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(1, Point(0, 0)),
			50),
		make_tuple(
			vector(5, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(1, Point(0, 0)),
			80),
		make_tuple(
			vector(10, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(1, Point(0, 0)),
			890)
	)
);

INSTANTIATE_TEST_CASE_P(
	SeveralZombieAndSeveralHumans_ScoreEqualNumberOfHumansSquaredFibNumberOfDestroyedZobiesSub2x10,	// NumberOfHumans * NumberOfHumans * Fib(NumberOfDestroyedZobies + 2) * 10
	GameReferee_Score_Tests,
	Values(
		make_tuple(
			vector(5, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(3, Point(0, 0)),
			9 * 8 * 10),
		make_tuple(
			vector(10, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(10, Point(0, 0)),
			100 * 89 * 10),
		make_tuple(
			vector(6, Point(ASH_SAFE_RANGE, ASH_SAFE_RANGE)),
			vector(2, Point(0, 0)),
			4 * 13 * 10)
	)
);

TEST_P(GameReferee_Score_Tests, Case)
{
	auto [zombiesCoordinates, humansCoordinates, expectedScore] = GetParam();
	const auto gameState = CreateGameState(zombiesCoordinates, humansCoordinates);
	auto referee = CreateReferee(gameState.get());

	referee.Turn(gameState->GetAsh());

	ASSERT_EQ(expectedScore, gameState->GetScore());
}