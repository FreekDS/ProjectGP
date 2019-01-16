#include <ObserverTests.h>

using namespace RoadFighter;

TEST_F(ObserverTests, SpeedObserverConstructor)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    SpeedObserverTest obs(player, "test");
}

TEST_F(ObserverTests, SpeedObserverUpdate)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    SpeedObserverTest obs(player, "speed");
    ::testing::internal::CaptureStdout();
    obs.update();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), "speed: 0\n");
}

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
