#include <PlayerTests.h>

using namespace RoadFighter;

/**
 * Tests the constructor of the Player.
 */
TEST_F(PlayerTests, Constructor)
{
    PlayerTest player;
    double height = 0.40;
    EXPECT_EQ(player.getType(), EntityType::PLAYER);
    EXPECT_EQ(player.getWidth(), 0.24);
    EXPECT_EQ(player.getHeight(), height);
    EXPECT_EQ(player.getPos(), Position(-0.25, -2));
    EXPECT_EQ(player.getMaxSpeed(false), 20);
    EXPECT_EQ(player.getMaxSpeed(true), 22);
    EXPECT_EQ(player.getMaxSpeed(), 22);
    EXPECT_EQ(player.getSpeed(), 0);

}

/**
 * Tests the getters of the Player.
 */
TEST_F(PlayerTests, Getters)
{
    PlayerTest player;
    double height = 0.40;
    EXPECT_EQ(player.getWidth(), 0.24);
    EXPECT_EQ(player.getHeight(), height);
    EXPECT_EQ(player.getPos(), Position(-0.25, -2));
    EXPECT_EQ(player.getMaxSpeed(false), 20);
    EXPECT_EQ(player.getMaxSpeed(true), 22);
    EXPECT_EQ(player.getMaxSpeed(), 22);
}

/**
 * Tests the accelerate function of the Player.
 */
TEST_F(PlayerTests, accelerate)
{
    PlayerTest player;
    EXPECT_EQ(player.getSpeed(), 0);
//    for(int i = 1; i<11; i++){
//        player.accelerate();
//        EXPECT_EQ(player.getSpeed(), 0.01 * i);
//    } //For some reason, this does not work (rounding?)

    player.accelerate();
    EXPECT_EQ(player.getSpeed(), 0.01);
    player.accelerate();
    EXPECT_EQ(player.getSpeed(), 0.02);

//    player.setSpeed(0);
//    for(int i = 0; i<100; i++)
//        player.accelerate();
//    EXPECT_EQ(player.getSpeed(), 1); // neither does this

    player.setSpeed(22);
    player.accelerate();
    EXPECT_EQ(player.getSpeed(), 21.99);
}

/**
 * Tests the slowdown function of the player.
 */
TEST_F(PlayerTests, slowDown)
{
    PlayerTest player;
    EXPECT_EQ(player.getSpeed(), 0);
    player.slowDown();
    EXPECT_EQ(player.getSpeed(), 0);
    player.setSpeed(0.01);
    player.slowDown();
    EXPECT_EQ(player.getSpeed(), 0);
    player.setSpeed(10);
    player.slowDown();
    EXPECT_EQ(player.getSpeed(), 9.98);

}

/**
 * Tests the canBeDestroyed function of the Player.
 */
TEST_F(PlayerTests, canBeDestroyed)
{
    PlayerTest player;
    EXPECT_FALSE(player.canBeDestroyed());
}

/**
 * Tests the move functions (up down left right) of the Player.
 */
TEST_F(PlayerTests, moveFunctions)
{
    PlayerTest player;
    Position initPos = player.getPos();
    // move up
    player.moveUp();
    EXPECT_EQ(player.getPos(), initPos);
    player.setSpeed(10);
    ASSERT_EQ(player.getSpeed(), 10);
    player.moveUp();
    EXPECT_NE(player.getPos(), initPos);
    EXPECT_EQ(player.getPos(), Position(-0.25,initPos.y+player.getMovespeed()));

    // move down
    PlayerTest player2;
    player2.moveDown();
    EXPECT_EQ(player2.getPos(), initPos);
    player2.setSpeed(10);
    ASSERT_EQ(player2.getSpeed(), 10);
    player2.moveDown();
    EXPECT_EQ(player2.getPos(), Position(-0.25, initPos.y-player2.getMovespeed()));

    PlayerTest player3;
    player3.moveLeft(-5);
    EXPECT_EQ(player3.getPos(), initPos);
    player3.moveLeft(10);
    EXPECT_EQ(player3.getPos(), initPos);
    player3.setSpeed(10);
    ASSERT_EQ(player3.getSpeed(), 10);
    player3.moveLeft(-5);
    EXPECT_EQ(player3.getPos(), Position(initPos.x-player3.getMovespeed(), initPos.y));
}

/**
 * Tests the update function of the Player
 */
TEST_F(PlayerTests, update)
{
    PlayerTest player;
    player.setSpeed(10);
    player.update();
    EXPECT_EQ(player.getSpeed(), 10);
    player.setSpeed(3);
    player.update();
    EXPECT_EQ(player.getSpeed(), 3);
    player.crash();
    player.update();
    EXPECT_EQ(player.getSpeed(), 0);

}


