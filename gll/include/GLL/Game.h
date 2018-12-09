#ifndef ROADFIGHTER_GAME_H
#define ROADFIGHTER_GAME_H

#include <memory>
#include "World.h"

using namespace std;

namespace RoadFighter {

    /**
     * This class represents the game
     * The game has the @see World as its member
     */
    class Game {
    protected:
        shared_ptr<World> m_world;
    public:
        /**
         * Constructor for Game
         * @param world Const reference to world of the game
         */
        explicit Game(const shared_ptr<World>& world);

        /**
         * Default constructor of Game
         * This constructor initializes the World as a nullptr
         */
        Game();

        /**
         * Pure virtual function which will start the game
         */
        virtual void runGame() = 0;

        /**
         * Default destructor of Game
         */
        virtual ~Game();
    };

} // Namespace RoadFighter

#endif //ROADFIGHTER_GAME_H
