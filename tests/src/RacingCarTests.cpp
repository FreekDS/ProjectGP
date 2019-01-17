#include <RacingCarTests.h>

using namespace RoadFighter;

TEST_F(RacingCarTests, Constructor)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    RacingCarTest r_car(player, world);
    EXPECT_EQ(r_car.getType(), EntityType::RACE_CAR);
    EXPECT_EQ(r_car.getPos(), Position(0.55, 1));
    RacingCarTest r_car2(player, world);
    EXPECT_EQ(r_car2.getPos(), Position(0.85, 0.5));
    RacingCarTest r_car3(player, world);
    EXPECT_EQ(r_car3.getPos(), Position(0.55, 0));
    RacingCarTest r_car4(player, world);
    EXPECT_EQ(r_car4.getPos(), Position(0.85, -0.5));
    RacingCarTest r_car5(player, world);
    EXPECT_EQ(r_car5.getPos(), Position(0.55, -1.0));
}

TEST_F(RacingCarTests, accelerate)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    RacingCarTest r_car(player, world);
    ASSERT_EQ(r_car.getSpeed(), 0);
    double lastSpeed;
    for (int i = 0; i<20; i++) {
        lastSpeed = r_car.getSpeed();
        r_car.accelerate();
        EXPECT_TRUE(r_car.getSpeed()>lastSpeed);
    }
}

TEST_F(RacingCarTests, canBeDestroyed)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    RacingCarTest r_car(player, world);
    EXPECT_FALSE(r_car.canBeDestroyed());
}

TEST_F(RacingCarTests, slowDown)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    RacingCarTest r_car(player, world);
    r_car.setSpeed(50);
    double lastSpeed;
    for (int i = 0; i<21; i++) {
        lastSpeed = r_car.getSpeed();
        r_car.slowDown();
        EXPECT_TRUE(r_car.getSpeed() <= lastSpeed);
    }
}
