#include <PositionTests.h>

using namespace RoadFighter;

TEST_F(PositionTests, Constructors)
{
    Position pos;
    EXPECT_EQ(pos.x, 0);
    EXPECT_EQ(pos.y, 0);
    Position pos2(1,2);
    EXPECT_EQ(pos2.x, 1);
    EXPECT_EQ(pos2.y, 2);
    Position pos3(0,0);
    EXPECT_EQ(pos3.x, 0);
    EXPECT_EQ(pos3.y, 0);
    Position pos4(-17, 3);
    EXPECT_EQ(pos4.x, -17);
    EXPECT_EQ(pos4.y, 3);

}

TEST_F(PositionTests, Assignment)
{
    Position pos1(12, 21);
    Position pos = pos1;
    EXPECT_EQ(pos, pos1);
}

TEST_F(PositionTests, toString)
{
    Position pos;
    EXPECT_EQ(pos.toString(), "(0.000000,0.000000)");
    pos.x = 12;
    pos.y = 21;
    EXPECT_EQ(pos.toString(), "(12.000000,21.000000)");
}

TEST_F(PositionTests, equality)
{
    Position pos1;
    Position pos2(15,21);
    Position pos3(15,21);
    Position pos4(0,0);
    EXPECT_FALSE(pos1 == pos2);
    EXPECT_TRUE(pos1 == pos4);
    EXPECT_FALSE(pos2 == pos4);
    EXPECT_TRUE(pos2 == pos3);
}

TEST_F(PositionTests, inEquality)
{
    Position pos1;
    Position pos2(15,21);
    Position pos3(15,21);
    Position pos4(0,0);
    EXPECT_TRUE(pos1 != pos2);
    EXPECT_FALSE(pos1 != pos4);
    EXPECT_TRUE(pos2 != pos4);
    EXPECT_FALSE(pos2 != pos3);
}
