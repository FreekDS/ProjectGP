#include <iostream>
#include <Game.h>
#include <Utilities.h>

int main(int argc, char* argv[])
{
    bool fullscreen = true;
    bool debug;
    parseProgramArgs(argc, argv, fullscreen, debug);
    try {
        RoadFighterSFML::Game game("Road Fighter", fullscreen, debug);
        game.runGame();
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

