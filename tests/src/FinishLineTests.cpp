#include <FinishLineTests.h>

using namespace RoadFighter;

/**
 * Test for constructor of finish line.
 */
TEST_F(FinishLineTests, Constructor)
{
    auto world = make_shared<WorldTest>();
    FinishLine line{world};
    EXPECT_EQ(line.getType(), EntityType::FINISH);
    EXPECT_EQ(line.getPos(), Position(0.3, 2.8));
}

/**
 * Test for the canBeDestroyed function of the FinishLine.
 */
TEST_F(FinishLineTests, canBeDestroyed)
{
    auto world = make_shared<WorldTest>();
    FinishLine line{world};
    EXPECT_FALSE(line.canBeDestroyed());
}


