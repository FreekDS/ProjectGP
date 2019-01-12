#include <BoxColliderTests.h>

using namespace RoadFighter;

TEST_F(BoxColliderTests, Constructor)
{
    BoxCollider col{Position(1, 1), Position()};
    EXPECT_EQ(col.getBottomRightCorner(), Position(1, 0));
    EXPECT_EQ(col.getUpperLeftCorner(), Position(0, 1));
    BoxCollider col2(Position(1, 5), Position(3, 6));
    EXPECT_EQ(col2.getBottomRightCorner(), Position(3, 5));
    EXPECT_EQ(col2.getUpperLeftCorner(), Position(1, 6));

    EXPECT_THROW({
        try {
            BoxCollider collider(Position(1.1, 1.1), Position(1.1, 1.1));
        }
        catch (std::invalid_argument& e) {
            EXPECT_STREQ(e.what(),
                    "Cannot create box collider with corners (1.100000,1.100000) and (1.100000,1.100000)");
            throw;
        }
    }, std::invalid_argument);

}

TEST_F(BoxColliderTests, Getters)
{
    BoxCollider col{Position(1, 1), Position()};
    EXPECT_EQ(col.getUpperLeftCorner(), Position(0,1));
    EXPECT_EQ(col.getBottomRightCorner(), Position(1,0));
}

TEST_F(BoxColliderTests, updateCollider)
{
    BoxCollider col(Position(1,1), Position());
    col.updateCollider(1,1);
    EXPECT_EQ(col.getUpperLeftCorner(), Position(1,2));
    EXPECT_EQ(col.getBottomRightCorner(), Position(2,1));
    col.updateCollider(-2,0);
    EXPECT_EQ(col.getUpperLeftCorner(), Position(-1,2));
    EXPECT_EQ(col.getBottomRightCorner(), Position(0,1));

}

TEST_F(BoxColliderTests, getCenter)
{
    BoxCollider col(Position(1,1), Position());
    EXPECT_EQ(col.getCenter(), Position(0.5,0.5));
    BoxCollider col2(Position(12,21), Position(-10,-5));
    EXPECT_EQ(col2.getCenter(), Position(1,8));
}

TEST_F(BoxColliderTests, equality)
{
    BoxCollider col1(Position(1,1), Position());
    BoxCollider col2(Position(2,2), Position(1,1));
    BoxCollider col3(Position(1,1), Position());
    EXPECT_TRUE(col1 == col3);
    EXPECT_FALSE(col1 == col2);
    EXPECT_FALSE(col2 == col3);
}

TEST_F(BoxColliderTests, inEquality)
{
    BoxCollider col1(Position(1,1), Position());
    BoxCollider col2(Position(2,2), Position(1,1));
    BoxCollider col3(Position(1,1), Position());
    EXPECT_FALSE(col1 != col3);
    EXPECT_TRUE(col1 != col2);
    EXPECT_TRUE(col2 != col3);
}
