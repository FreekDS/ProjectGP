#ifndef ROADFIGHTER_WORLDTESTS_H
#define ROADFIGHTER_WORLDTESTS_H

#include <gtest/gtest.h>
#include <GLL/Entity.h>

class EntityTest : public RoadFighter::Entity{
public:
    void draw() const override{}
    void update() override{}
    void updateSpriteLocation() override{}
    bool canBeDestroyed() const override
    {
        return false;
    }
    /**
     * Resests the Test Entity
     */
    void resetEntity() {
        EntityTest entity;
        *this = move(entity);
    }
    /**
     * Wrapper for protected setType function
     * @param type Type to set
     */
    void setTestType(const RoadFighter::EntityType& type){
        this->setType(type);
    }
};

class EntityTests : public ::testing::Test{
protected:

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

#endif //ROADFIGHTER_WORLDTESTS_H
