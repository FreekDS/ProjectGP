#ifndef ROADFIGHTER_TRANSFORMATIONTESTS_H
#define ROADFIGHTER_TRANSFORMATIONTESTS_H

#include <gtest/gtest.h>
#include <GLL/Transformation.h>

/**
 * This function is used in the tests to reset the Transformation class.
 */
void resetTrans()
{
    auto trans = RoadFighter::Transformation::getInstance();
    trans->setScreenSize(0, 0);
    trans->setRangeX(-4, 4);
    trans->setRangeY(-3, 3);
}

/**
 * Tests for the Transformation class.
 */
class TransformationTests : public ::testing::Test {
    void SetUp() override { }

    void TearDown() override { }
};

#endif //ROADFIGHTER_TRANSFORMATIONTESTS_H
