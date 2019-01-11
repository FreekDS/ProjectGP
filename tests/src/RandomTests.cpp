#include <RandomTests.h>

using namespace RoadFighter;


TEST_F(RandomTests, GetInstance)
{
    auto rand1 = Random::getInstance();
    auto rand2 = Random::getInstance();

    EXPECT_EQ(rand1.get(), rand2.get());
    EXPECT_EQ(rand1.use_count(), rand2.use_count());
}

TEST_F(RandomTests, RandIntTest)
{
    auto rand = Random::getInstance();
    for(int i = 0; i<1000; i++) {
        int int1 = rand->randInt(0,500);
        int int2 = rand->randInt(500, 0);
        int int3 = rand->randInt(12,21);
        EXPECT_TRUE(int1 <= 500 && int1 >=0);
        EXPECT_TRUE(int2 <=500 && int2 >=0);
        EXPECT_TRUE(int3 >=12 && int3<=21);
    }
}

TEST_F(RandomTests, RandDoubleTest)
{
    auto rand = Random::getInstance();
    for(int i = 0; i<1000; i++) {
        double double1 = rand->randDouble(0.7,5.8);
        double double2 = rand->randDouble(5.8, 0.7);
        double double3 = rand->randDouble(12.12,21.12);
        EXPECT_TRUE(double1 <= 5.8 && double1 >=0.7);
        EXPECT_TRUE(double2 <=5.8 && double2 >=0.7);
        EXPECT_TRUE(double3 >=12.12 && double3<=21.21);
    }
}


