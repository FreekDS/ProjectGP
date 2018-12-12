#include <iostream>
#include <Game.h>


int main(int argc, char* argv[])
{
    try {
        RoadFighterSFML::Game game("Road Fighter", true, true);
        game.runGame();
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

