#ifndef ROADFIGHTER_BOXCOLLIDERTESTS_H
#define ROADFIGHTER_BOXCOLLIDERTESTS_H

#include <gtest/gtest.h>
#include "TestClasses.h"

class BoxColliderTests : public ::testing::Test{
protected:
    friend class RoadFighter::BoxCollider;
    void SetUp() override{}
    void TearDown() override{}
};

#endif //ROADFIGHTER_BOXCOLLIDERTESTS_H
