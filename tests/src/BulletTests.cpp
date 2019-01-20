#include <BulletTests.h>

using namespace RoadFighter;

/**
 * Tests the constructor of the Bullet
 */
TEST_F(BulletTests, Constructor)
{
    BulletTest bullet{10, Position(), 0.5};
    EXPECT_EQ(bullet.getShootSpeed(), 10);
    EXPECT_EQ(bullet.getType(), EntityType::BULLET);
    EXPECT_EQ(bullet.getPos(), Position(0,0.5 + bullet.getHeight()));
}

/**
 * Tests the getters and setters of the Bullet.
 */
TEST_F(BulletTests, SetterGetter)
{
    BulletTest bullet{21, Position(), 0.5};
    EXPECT_EQ(bullet.getShootSpeed(), 21);
    bullet.setShootSpeed(12);
    EXPECT_EQ(bullet.getShootSpeed(), 12);
    bullet.setShootSpeed(-15);
    EXPECT_EQ(bullet.getShootSpeed(), -15);
    bullet.setShootSpeed(0);
    EXPECT_EQ(bullet.getShootSpeed(), 0);

}

/**
 * Tests the update function of the Bullet.
 */
TEST_F(BulletTests, update)
{
    BulletTest bullet{10, Position(), 0.5};
    Position initPos = bullet.getPos();
    bullet.update();
    EXPECT_EQ(bullet.getPos(), Position(initPos.x, initPos.y + bullet.getShootSpeed()));
    bullet.setPos(initPos);
    for(unsigned int i = 0; i<100; i++) {
        bullet.update();
        EXPECT_EQ(bullet.getPos(), Position(initPos.x, initPos.y + (i+1) * bullet.getShootSpeed()));
    }
}

/**
 * Tests the canBeDestroyed function of the Bullet.
 */
TEST_F(BulletTests, canBeDestroyed)
{
    BulletTest bullet{10, Position(), 0.5};
    EXPECT_FALSE(bullet.canBeDestroyed());
    bullet.setPos(0, 2000);
    EXPECT_TRUE(bullet.canBeDestroyed());
    BulletTest bullet2{1, Position(), 0.5};
    bullet2.hit();
    EXPECT_TRUE(bullet.canBeDestroyed());
}


