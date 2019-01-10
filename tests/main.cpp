#include <gtest/gtest.h>
#include <World.h>

int main(int argc, char* argv[]){
    shared_ptr<sf::RenderWindow> window = make_shared<sf::RenderWindow>(nullptr);
    RoadFighterSFML::World world("background.png", window);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
