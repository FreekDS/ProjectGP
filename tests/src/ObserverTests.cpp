#include <ObserverTests.h>

using namespace RoadFighter;

/**
 * Tests the Constructor of the SpeedObserver.
 */
TEST_F(ObserverTests, SpeedObserverConstructor)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    SpeedObserverTest obs(player, "test");
}

/**
 * Tests the update function of the SpeedObserver.
 */
TEST_F(ObserverTests, SpeedObserverUpdate)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    SpeedObserverTest obs(player, "speed");
    ::testing::internal::CaptureStdout();
    obs.update();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), "speed: 0\n");
}

/**
 * Tests the getter of the SpeedObserver.
 */
TEST_F(ObserverTests, SpeedObserverGetter)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    SpeedObserverTest obs(player, "speed");
    EXPECT_EQ(obs.getPlayerSpeed(), 0);
    player->setSpeed(0.7);
    EXPECT_EQ(obs.getPlayerSpeed(), 7);
    player->setSpeed(13587.12);
    EXPECT_EQ(obs.getPlayerSpeed(), 135871);
}

/**
 * Tests the Constructor of the distance observer.
 */
TEST_F(ObserverTests, DistanceObserverConstructor)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    DistanceObserverTest obs(player);
}

/**
 * Tests the getType function of the distance observer.
 */
TEST_F(ObserverTests, DistanceObserverGetter){
    shared_ptr<Player> player = make_shared<PlayerTest>();
    DistanceObserverTest obs(player);
    EXPECT_EQ(obs.getType(), ObserverType::DISTANCE);
}

/**
 * Tests the constructor of the Score Observer.
 */
TEST_F(ObserverTests, ScoreObserverConstructor)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    ScoreObserverTest obs(player, "Score: ");
    EXPECT_EQ(obs.getType(), ObserverType::SCORE);
    EXPECT_EQ(obs.getScore(), 0);
}

/**
 * Tests the updateScore function of the Score observer.
 */
TEST_F(ObserverTests, ScoreObserverUpdateScore)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    ScoreObserverTest obs(player, "Score: ");
    EXPECT_EQ(obs.getScore(), 0);
    obs.updateScore(-5);
    EXPECT_EQ(obs.getScore(), 0);
    obs.updateScore(100);
    EXPECT_EQ(obs.getScore(), 100);
    obs.updateScore(50);
    EXPECT_EQ(obs.getScore(), 150);
}

/**
 * Tests the update function of the Score observer.
 */
TEST_F(ObserverTests, ScoreObserverUpdate)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    ScoreObserverTest obs(player, "Score: ");
    EXPECT_EQ(obs.getScore(), 0);
    obs.update();
    EXPECT_EQ(obs.getScore(), 0);
    player->setDistanceCovered(800);
    obs.update();
    EXPECT_EQ(obs.getScore(), 800);
    player->setDistanceCovered(799);
    obs.update();
    EXPECT_NE(obs.getScore(), 1599);
    EXPECT_NE(obs.getScore(), 799);
    EXPECT_EQ(obs.getScore(), 800);
    player->setDistanceCovered(801);
    obs.update();
    EXPECT_EQ(obs.getScore(), 801);
}