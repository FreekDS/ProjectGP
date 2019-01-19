#include <EntityTests.h>
#include <GLL/Transformation.h>

using namespace RoadFighter;

/**
 * Tests the constructor of the Entity.
 */
TEST_F(EntityTests, Constructor)
{
    // Default constructor
    EntityTest entity;
    EXPECT_EQ(entity.getType(), EntityType::UNKNOWN);
    EXPECT_EQ(entity.getPos(), Position());
    EXPECT_EQ(entity.getPos(), Position(0, 0));
    EXPECT_EQ(entity.getUpperLeftCorner(), Position());
    EXPECT_EQ(entity.getUpperLeftCorner(), Position(0, 0));
    EXPECT_EQ(entity.getBottomRightCorner(), Position());
    EXPECT_EQ(entity.getBottomRightCorner(), Position(0, 0));
    EXPECT_EQ(entity.getColliders().size(), 0);
    EXPECT_EQ(entity.getHeight(), 0);
    EXPECT_EQ(entity.getWidth(), 0);
}

/**
 * Tests the copy constructor of the Entity
 */
TEST_F(EntityTests, CopyConstructor)
{
    EntityTest entity;
    entity.setPos(0, 5);
    EntityTest entity2(entity);
    EXPECT_EQ(entity.getBottomRightCorner(), entity2.getBottomRightCorner());
    EXPECT_EQ(entity.getUpperLeftCorner(), entity2.getUpperLeftCorner());
    EXPECT_EQ(entity.getPos(), entity2.getPos());
    EXPECT_EQ(entity.getType(), entity2.getType());
    EXPECT_EQ(entity.getWidth(), entity2.getWidth());
    EXPECT_EQ(entity.getHeight(), entity2.getHeight());
    ASSERT_EQ(entity.getColliders().size(), entity2.getColliders().size());
    for (unsigned int i = 0; i<entity.getColliders().size(); i++)
        EXPECT_EQ(entity.getColliders()[i], entity2.getColliders()[i]);

}

/**
 * Tests the move constructor of the Entity.
 */
TEST_F(EntityTests, MoveConstructor)
{
    EntityTest entity;
    entity.setPos(3, 2);

    Position pos = entity.getPos();
    Position br = entity.getBottomRightCorner();
    Position ul = entity.getUpperLeftCorner();
    EntityType type = entity.getType();
    double width = entity.getWidth();
    double height = entity.getHeight();
    auto colliders = entity.getColliders();

    EntityTest entity2(std::move(entity));
    EXPECT_EQ(br, entity2.getBottomRightCorner());
    EXPECT_EQ(ul, entity2.getUpperLeftCorner());
    EXPECT_EQ(pos, entity2.getPos());
    EXPECT_EQ(type, entity2.getType());
    EXPECT_EQ(width, entity2.getWidth());
    EXPECT_EQ(height, entity2.getHeight());
    ASSERT_EQ(colliders.size(), entity2.getColliders().size());
    for (unsigned int i = 0; i<colliders.size(); i++)
        EXPECT_EQ(colliders[i], entity2.getColliders()[i]);
}

/**
 * Tests the assignment operator for the Entity.
 */
TEST_F(EntityTests, AssignmentOperator)
{
    EntityTest entity;
    entity.setPos(3, 2);
    EntityTest entity2 = entity;
    EXPECT_EQ(entity.getBottomRightCorner(), entity2.getBottomRightCorner());
    EXPECT_EQ(entity.getUpperLeftCorner(), entity2.getUpperLeftCorner());
    EXPECT_EQ(entity.getPos(), entity2.getPos());
    EXPECT_EQ(entity.getType(), entity2.getType());
    EXPECT_EQ(entity.getWidth(), entity2.getWidth());
    EXPECT_EQ(entity.getHeight(), entity2.getHeight());
    ASSERT_EQ(entity.getColliders().size(), entity2.getColliders().size());
    for (unsigned int i = 0; i<entity.getColliders().size(); i++)
        EXPECT_EQ(entity.getColliders()[i], entity2.getColliders()[i]);
}

/**
 * Tests the move assignment of the Entity.
 */
TEST_F(EntityTests, MoveAssignment)
{
    EntityTest entity;
    entity.setPos(3, 2);

    Position pos = entity.getPos();
    Position br = entity.getBottomRightCorner();
    Position ul = entity.getUpperLeftCorner();
    EntityType type = entity.getType();
    double width = entity.getWidth();
    double height = entity.getHeight();
    auto colliders = entity.getColliders();

    EntityTest entity2 = std::move(entity);
    EXPECT_EQ(br, entity2.getBottomRightCorner());
    EXPECT_EQ(ul, entity2.getUpperLeftCorner());
    EXPECT_EQ(pos, entity2.getPos());
    EXPECT_EQ(type, entity2.getType());
    EXPECT_EQ(width, entity2.getWidth());
    EXPECT_EQ(height, entity2.getHeight());
    ASSERT_EQ(colliders.size(), entity2.getColliders().size());
    for (unsigned int i = 0; i<colliders.size(); i++)
        EXPECT_EQ(colliders[i], entity2.getColliders()[i]);
}

/**
 * Tests the getters and setters of the Entity.
 */
TEST_F(EntityTests, GettersSetters)
{
    EntityTest entity;
    Position pos(1,1);
    Position pos2(2,2);

    // setPos() and getPos()
    EXPECT_EQ(entity.getPos(), Position());
    EXPECT_EQ(entity.getPos(), Position(0,0));
    entity.setPos(pos);
    EXPECT_EQ(entity.getPos(), pos);
    entity.setPos(2,2);
    EXPECT_EQ(entity.getPos(), pos2);

    entity.resetEntity();

    // getUpperLeftCorner and setUpperLeftCorner
    EXPECT_EQ(entity.getUpperLeftCorner(), Position());
    EXPECT_EQ(entity.getUpperLeftCorner(), Position(0,0));
    entity.setUpperLeftCorner(pos2);
    EXPECT_EQ(entity.getUpperLeftCorner(), pos2);

    // getBottomRightCorner and setBottomRightCorner
    EXPECT_EQ(entity.getBottomRightCorner(), Position());
    EXPECT_EQ(entity.getBottomRightCorner(), Position(0,0));
    entity.setBottomRightCorner(pos);
    EXPECT_EQ(entity.getBottomRightCorner(), pos);

    // getWidth and getHeight
    EXPECT_EQ(entity.getWidth(), 1.0);
    EXPECT_EQ(entity.getHeight(), 1.0);
    entity.resetEntity();
    EXPECT_EQ(entity.getWidth(), 0);
    EXPECT_EQ(entity.getHeight(), 0);

    // getType and setType
    EXPECT_EQ(entity.getType(), EntityType::UNKNOWN);
    entity.setTestType(EntityType::BULLET);
    EXPECT_EQ(entity.getType(), EntityType::BULLET);

    entity.resetEntity();
    
    // getColliders
    BoxCollider collider{Position(), Position(1,1)};
    BoxCollider collider2{Position(), Position(2,2)};
    EXPECT_TRUE(entity.getColliders().empty());
    entity.addCollider(collider);
    entity.addCollider(collider2);
    EXPECT_EQ(entity.getColliders().size(), 2);

}

/**
 * Tests the addCollider function of the Entity.
 */
TEST_F(EntityTests, addCollider)
{
    EntityTest entity;
    EXPECT_TRUE(entity.getColliders().empty());
    entity.addCollider(BoxCollider(Position(), Position(1,1)));
    EXPECT_FALSE(entity.getColliders().empty());
    EXPECT_EQ(entity.getColliders().size(), 1);
}

/**
 * Tests the removeCollider function of the Entity.
 */
TEST_F(EntityTests, removeCollider)
{
    EntityTest entity;
    entity.addCollider(BoxCollider(Position(), Position(1,1)));
    ASSERT_FALSE(entity.getColliders().empty());
    entity.removeCollider(0);
    EXPECT_TRUE(entity.getColliders().empty());
    EXPECT_DEATH_IF_SUPPORTED(entity.removeCollider(21), "");
}

/**
 * Tests the updatePos function of the Entity.
 */
TEST_F(EntityTests, updatePos)
{
    EntityTest entity;
    EXPECT_EQ(entity.getPos(), Position());
    EXPECT_EQ(entity.getPos(), Position());
    EXPECT_EQ(entity.getUpperLeftCorner(), Position());
    EXPECT_EQ(entity.getBottomRightCorner(), Position());

    Position pos(12,21);
    entity.updatePos(12,21);
    EXPECT_EQ(entity.getPos(), pos);
    EXPECT_EQ(entity.getPos(), pos);
    EXPECT_EQ(entity.getUpperLeftCorner(), pos);
    EXPECT_EQ(entity.getBottomRightCorner(), pos);
}

/**
 * Tests the isVisible function of the Entity.
 */
TEST_F(EntityTests, isVisible)
{
    auto trans = Transformation::getInstance();
    EntityTest entity;
    EXPECT_TRUE(entity.isVisible());
    entity.setPos(trans->getXRange().second/2, trans->getYRange().second/2);
    EXPECT_TRUE(entity.isVisible());
    entity.setPos(12156161561, 454489489);
    EXPECT_FALSE(entity.isVisible());
    entity.setPos(-15155815154, -44451544);
    EXPECT_FALSE(entity.isVisible());
    entity.setPos(-1,-1);
    EXPECT_TRUE(entity.isVisible());
}

/**
 * Tests the initializeCorners function of the Entity.
 */
TEST_F(EntityTests, initializeCorners)
{
    EntityTest entity;
    Position pos(1,1);
    entity.setPos(1,1);
    EXPECT_EQ(entity.getPos(), pos);
    EXPECT_EQ(entity.getBottomRightCorner(), pos);
    EXPECT_EQ(entity.getUpperLeftCorner(), pos);
    entity.initializeCorners(2,2);
    EXPECT_NE(entity.getPos(), pos);
    EXPECT_NE(entity.getBottomRightCorner(), pos);
    EXPECT_NE(entity.getUpperLeftCorner(), pos);

    EXPECT_EQ(entity.getPos(), Position());
    EXPECT_EQ(entity.getUpperLeftCorner(), Position(-1,1));
    EXPECT_EQ(entity.getBottomRightCorner(), Position(1,-1));
}

