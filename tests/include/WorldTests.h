#ifndef ROADFIGHTER_WORLDTESTS_H
#define ROADFIGHTER_WORLDTESTS_H

#include <gtest/gtest.h>
#include <GLL/World.h>
#include "TestClasses.h"

class WorldTests : public ::testing::Test {
protected:
    friend class RoadFighter::World;
    void SetUp() override{}
    void TearDown() override{}
};

#endif //ROADFIGHTER_WORLDTESTS_H
