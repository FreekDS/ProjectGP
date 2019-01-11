#ifndef ROADFIGHTER_RANDOMTESTS_H
#define ROADFIGHTER_RANDOMTESTS_H

#include <gtest/gtest.h>
#include <GLL/Random.h>

class RandomTests : public ::testing::Test{
protected:
    friend class RoadFighter::Random;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

#endif //ROADFIGHTER_RANDOMTESTS_H
