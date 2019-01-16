#include <PassingCarTests.h>
#include <TestClasses.h>
#include <GLL/Transformation.h>

using namespace RoadFighter;

TEST_F(PassingCarTests, Constructor)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    PassingCarTest p_car(player, world);
    EXPECT_FALSE(p_car.canBeDestroyed());
    EXPECT_EQ(p_car.getType(), EntityType::PASSING_CAR);
    EXPECT_TRUE(p_car.getMovespeed(1) > 3 && p_car.getMovespeed(1) < 8);
}

TEST_F(PassingCarTests, update)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    PassingCarTest p_car(player, world);
    double yPos = p_car.getPos().y;
    p_car.update();
    EXPECT_TRUE(p_car.getPos().y < yPos);
    p_car.crash();
    p_car.update();
    EXPECT_EQ(p_car.getMovespeed(1), 0);
}

TEST_F(PassingCarTests, canBeDestroyed)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    PassingCarTest p_car(player, world);
    auto trans = Transformation::getInstance();
    EXPECT_FALSE(p_car.canBeDestroyed());
    p_car.setPos(0, 2*trans->getYRange().first);
    EXPECT_FALSE(p_car.canBeDestroyed());
    p_car.setPos(0, 2*trans->getYRange().first-0.00001);
    EXPECT_TRUE(p_car.canBeDestroyed());
}

TEST_F(PassingCarTests, moveDown)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    PassingCarTest p_car(player, world);
    double yPos = p_car.getPos().y;
    p_car.moveDown();
    EXPECT_TRUE(p_car.getPos().y < yPos);
}

TEST_F(PassingCarTests, initializePosition)
{
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<World> world = make_shared<WorldTest>();
    PassingCarTest p_car(player, world);
    auto trans = Transformation::getInstance();
    p_car.initializePosition();
    EXPECT_EQ(p_car.getPos().y, trans->getYRange().second+p_car.getWidth());
    // as initializePos uses random values, we test this 1000 times
    for(int i = 0; i<1000; i++){
        p_car.initializePosition();
        ASSERT_TRUE(p_car.getPos().x > world->getLeftBoundary() + p_car.getWidth()/2);
        ASSERT_TRUE(p_car.getPos().x < world->getRightBoundary() - p_car.getWidth()/2);
    }

}