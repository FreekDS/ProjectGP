#include <VehicleTests.h>

using namespace RoadFighter;

TEST_F(VehicleTests, Constructor)
{
    VehicleTest vehicle;
    EXPECT_EQ(vehicle.getMovespeed(1), 3.0);
    EXPECT_EQ(vehicle.getSpeed(), 0);
    EXPECT_FALSE(vehicle.hasCrashed());
}

TEST_F(VehicleTests, GettersSetters)
{
    VehicleTest vehicle;
    EXPECT_EQ(vehicle.getMovespeed(1), 3.0);
    EXPECT_EQ(vehicle.getSpeed(), 0);
    EXPECT_FALSE(vehicle.hasCrashed());
    EXPECT_EQ(vehicle.getType(), EntityType::VEHICLE);
    vehicle.setMoveSpeed(10);
    vehicle.setSpeed(50);
    EXPECT_EQ(vehicle.getMovespeed(1), 10.0);
    EXPECT_EQ(vehicle.getMovespeed(), 10.0/140);
    EXPECT_EQ(vehicle.getSpeed(), 50.0);

}

TEST_F(VehicleTests, isMoving)
{
    VehicleTest vehicle;
    EXPECT_FALSE(vehicle.isMoving());
    vehicle.setSpeed(0.3);
    EXPECT_FALSE(vehicle.isMoving());
    vehicle.setSpeed(-0.3);
    EXPECT_FALSE(vehicle.isMoving());
    vehicle.setSpeed(0.31);
    EXPECT_TRUE(vehicle.isMoving());

}

TEST_F(VehicleTests, crash)
{
    VehicleTest vehicle;
    EXPECT_FALSE(vehicle.hasCrashed());
    vehicle.crash();
    EXPECT_TRUE(vehicle.hasCrashed());
}

TEST_F(VehicleTests, repair)
{
    VehicleTest vehicle;
    EXPECT_FALSE(vehicle.hasCrashed());
    vehicle.crash();
    EXPECT_TRUE(vehicle.hasCrashed());
    vehicle.repair(true);
    EXPECT_FALSE(vehicle.hasCrashed());
}

TEST_F(VehicleTests, finish)
{
    VehicleTest vehicle;
    EXPECT_FALSE(vehicle.hasFinished());
    vehicle.finish();
    EXPECT_TRUE(vehicle.hasFinished());
}
