#ifndef ROADFIGHTER_GAME_H
#define ROADFIGHTER_GAME_H

#include <memory>
#include "World.h"

using namespace std;

namespace RoadFighter {

    class Game {
    protected:
        shared_ptr<World> m_world;
    public:
        explicit Game(const shared_ptr<World>& world);

        Game();

        virtual void runGame() = 0;
    };

} // Namespace RoadFighter

#endif //ROADFIGHTER_GAME_H
