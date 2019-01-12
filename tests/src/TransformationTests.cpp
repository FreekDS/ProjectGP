#include <TransformationTests.h>

using namespace RoadFighter;

TEST_F(TransformationTests, getInstance)
{
    resetTrans();
    auto trans = Transformation::getInstance();
    auto trans2 = Transformation::getInstance();
    EXPECT_EQ(trans.get(), trans2.get());
}

TEST_F(TransformationTests, GetterSetter)
{
    resetTrans();
    auto trans = Transformation::getInstance();
    range xRange{-4,4};
    range yRange{-3,3};
    range xRange2{-5,5};
    range yRange2{1,8};
    EXPECT_EQ(trans->getXRange(), xRange);
    EXPECT_EQ(trans->getYRange(), yRange);
    trans->setRangeX(-5,5);
    trans->setRangeY(1,8);
    EXPECT_EQ(trans->getXRange(), xRange2);
    EXPECT_EQ(trans->getYRange(), yRange2);
}

TEST_F(TransformationTests, getScreenCoordinate)
{
    resetTrans();
    auto trans = Transformation::getInstance();
    EXPECT_EQ(trans->getScreenCoordinate(0,0), Position());
    EXPECT_EQ(trans->getScreenCoordinate(Position()), Position());
    trans->setScreenSize(1800,600);
    trans->setScreenSize(1800,600);
    trans->setScreenSize(1800,600);
    EXPECT_EQ(trans->getScreenCoordinate(0,0), Position(900,300));
    EXPECT_EQ(trans->getScreenCoordinate(Position()), Position(900,300));
    trans->setScreenSize(1800,600);
    EXPECT_EQ(trans->getScreenCoordinate(-4,-3), Position(0,600));
    EXPECT_EQ(trans->getScreenCoordinate(-4,3), Position());
    EXPECT_EQ(trans->getScreenCoordinate(2,1), Position(1350, 200));
}

TEST_F(TransformationTests, isInGrid)
{
    resetTrans();
    auto trans = Transformation::getInstance();
    EXPECT_TRUE(trans->isInGrid(Position(0,0)));
    EXPECT_TRUE(trans->isInGrid(Position(-4,3)));
    EXPECT_TRUE(trans->isInGrid(Position(4,3)));
    EXPECT_TRUE(trans->isInGrid(Position(4,-3)));
    EXPECT_TRUE(trans->isInGrid(Position(-4,-3)));
    EXPECT_TRUE(trans->isInGrid(Position(1,-2)));
    EXPECT_FALSE(trans->isInGrid(Position(-100,200)));
    EXPECT_FALSE(trans->isInGrid(Position(100,200)));
    EXPECT_FALSE(trans->isInGrid(Position(100,-200)));
    EXPECT_FALSE(trans->isInGrid(Position(-100,-200)));
}

