#include "../pch.h"
#include "GameStateProxy.h"

class GameStateMock : public IGameState
{
public:
    MOCK_METHOD(bool, IsEndGame, (), (const, override));
    MOCK_METHOD(void, SetEndGame, (bool), (override));
    MOCK_METHOD(const Unit&, GetAsh, (), (const, override));
    MOCK_METHOD(const Unit&, GetHuman, (int), (const, override));
    MOCK_METHOD(const Humans&, GetHumans, (),  (const, override));
    MOCK_METHOD(bool, IsAliveHuman, (int), (const, override));
    MOCK_METHOD(const Zombie&, GetZombie, (int), (const, override));
    MOCK_METHOD(const Zombies&, GetZombies, (), (const, override));
    MOCK_METHOD(Zombies&, GetZombies, (), (override));

    MOCK_METHOD(void, Clear, (), (override));

    MOCK_METHOD(void, SetAshCoordinate, (int, int), (override));
    MOCK_METHOD(void, AddHuman, (const Unit&), (override));
    MOCK_METHOD(void, RemoveHuman, (int), (override));
    MOCK_METHOD(void, AddZombie, (const Zombie&), (override));
    MOCK_METHOD(void, RemoveZombie, (int), (override));
    MOCK_METHOD(int, GetScore, (), (const, override));
    MOCK_METHOD(void, SetScore, (int), (override));
};

using ::testing::Return;
using ::testing::ReturnRef;

TEST(GameStateProxy_Tests, IsEndGame_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, IsEndGame())
        .WillOnce(Return(false));

    const GameStateProxy proxy(mock);

    proxy.IsEndGame();
}

TEST(GameStateProxy_Tests, SetEndGame_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, SetEndGame(true))
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.SetEndGame(true);
}

TEST(GameStateProxy_Tests, GetAsh_CallSourceFunc)
{
    Unit res(0, 0, 0);
    GameStateMock mock;
    EXPECT_CALL(mock, GetAsh())
        .WillOnce(ReturnRef(res));

    const GameStateProxy proxy(mock);

    proxy.GetAsh();
}

TEST(GameStateProxy_Tests, GetHuman_CallSourceFunc)
{
    Unit res(0, 0, 0);
    GameStateMock mock;
    EXPECT_CALL(mock, GetHuman(0))
        .WillOnce(ReturnRef(res));

    const GameStateProxy proxy(mock);

    proxy.GetHuman(0);
}

TEST(GameStateProxy_Tests, GetHumans_CallSourceFunc)
{
    Humans res;
    GameStateMock mock;
    EXPECT_CALL(mock, GetHumans())
        .WillOnce(ReturnRef(res));

    const GameStateProxy proxy(mock);

    proxy.GetHumans();
}

TEST(GameStateProxy_Tests, IsAliveHuman_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, IsAliveHuman(0))
        .WillOnce(Return(false));

    const GameStateProxy proxy(mock);

    proxy.IsAliveHuman(0);
}

TEST(GameStateProxy_Tests, GetZombie_CallSourceFunc)
{
    Zombie res(0, 0, 0, 0, 0);
    GameStateMock mock;
    EXPECT_CALL(mock, GetZombie(0))
        .WillOnce(ReturnRef(res));

    const GameStateProxy proxy(mock);

    proxy.GetZombie(0);
}

TEST(GameStateProxy_Tests, GetZombiesConst_CallSourceFunc)
{
    Zombies res;
    GameStateMock mock;
    EXPECT_CALL(mock, GetZombies())
        .WillOnce(ReturnRef(res));

    const GameStateProxy proxy(mock);

    proxy.GetZombies();
}

TEST(GameStateProxy_Tests, GetZombies_CallSourceFunc)
{
    Zombies res;
    GameStateMock mock;
    EXPECT_CALL(mock, GetZombies())
        .WillOnce(ReturnRef(res));

    const GameStateProxy proxy(mock);

    proxy.GetZombies();
}

TEST(GameStateProxy_Tests, Clear_CallSourceFunc)
{
    Unit res(0, 0, 0);
    GameStateMock mock;
    EXPECT_CALL(mock, Clear())
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.Clear();
}

TEST(GameStateProxy_Tests, SetAshCoordinate_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, SetAshCoordinate(0, 0))
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.SetAshCoordinate(0, 0);
}

TEST(GameStateProxy_Tests, AddHuman_CallSourceFunc)
{
    const Unit human(0, 0, 0);
    GameStateMock mock;
    EXPECT_CALL(mock, AddHuman(testing::_))
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.AddHuman(human);
}

TEST(GameStateProxy_Tests, RemoveHuman_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, RemoveHuman(0))
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.RemoveHuman(0);
}

TEST(GameStateProxy_Tests, AddZombie_CallSourceFunc)
{
    const Zombie zombie(0, 0, 0, 0, 0);
    GameStateMock mock;
    EXPECT_CALL(mock, AddZombie(testing::_))
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.AddZombie(zombie);
}

TEST(GameStateProxy_Tests, RemoveZombie_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, RemoveZombie(0))
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.RemoveZombie(0);
}

TEST(GameStateProxy_Tests, GetScore_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, GetScore())
        .WillOnce(Return(0));

    const GameStateProxy proxy(mock);

    proxy.GetScore();
}

TEST(GameStateProxy_Tests, SetScore_CallSourceFunc)
{
    GameStateMock mock;
    EXPECT_CALL(mock, SetScore(0))
        .Times(1);

    GameStateProxy proxy(mock);

    proxy.SetScore(0);
}